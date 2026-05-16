#include "processmodel.h"
#include <QtMath>
#include <QRandomGenerator>
#include <QDebug>
#include <QVariantMap>

ProcessModel::ProcessModel(QObject *parent)
    : QObject(parent)
    , m_simulationStartTime(QDateTime::currentDateTime())
{
    reset();
}

ProcessModel::~ProcessModel()
{
}

void ProcessModel::setControlInput(double input)
{
    // Ограничение входного сигнала
    double limitedInput = qBound(0.0, input, 100.0);
    bool wasSaturated = m_saturated;
    m_saturated = (input != limitedInput);
    
    if (m_saturated != wasSaturated) {
        emit saturationChanged(m_saturated);
    }
    
    m_controlInput = limitedInput;
    emit controlInputChanged(m_controlInput);
}

void ProcessModel::setProcessType(ProcessType type)
{
    if (m_processType == type)
        return;
    
    m_processType = type;
    emit processTypeChanged(type);
    reset();
}

void ProcessModel::setParameters(const ModelParameters& params)
{
    m_params = params;
    reset();
}

void ProcessModel::setGain(double gain)
{
    m_params.gain = gain;
    reset();
}

void ProcessModel::setTimeConstant(double tc)
{
    m_params.timeConstant1 = tc;
    reset();
}

void ProcessModel::setDeadTime(double deadTime)
{
    m_params.deadTime = deadTime;
    reset();
}

void ProcessModel::setDisturbance(double disturbance)
{
    m_params.disturbance = disturbance;
}

void ProcessModel::setNoiseLevel(double noiseLevel)
{
    m_params.noiseLevel = qMax(0.0, noiseLevel);
}

double ProcessModel::step(double dt)
{
    if (dt <= 0)
        dt = 0.1;
    
    m_simulationTime += dt;
    
    // Применение времени задержки
    double delayedInput = m_controlInput;
    if (m_params.deadTime > 0) {
        // Добавляем текущий вход в историю
        m_inputHistory.append(qMakePair(m_simulationTime, m_controlInput));
        if (m_inputHistory.size() > MAX_HISTORY_SIZE) {
            m_inputHistory.removeFirst();
        }
        
        // Находим вход с учетом задержки
        double targetTime = m_simulationTime - m_params.deadTime;
        if (!m_inputHistory.isEmpty() && targetTime >= m_inputHistory.first().first) {
            for (int i = m_inputHistory.size() - 1; i >= 0; --i) {
                if (m_inputHistory[i].first <= targetTime) {
                    delayedInput = m_inputHistory[i].second;
                    break;
                }
            }
        } else {
            delayedInput = 0; // До окончания dead time выход нулевой
        }
    }
    
    // Вычисление следующего значения в зависимости от типа процесса
    double newValue = m_processValue;
    
    switch (m_processType) {
    case ProcessType::FOPDT:
    case ProcessType::FirstOrder:
        newValue = computeFOPDT(dt);
        break;
    case ProcessType::SecondOrder:
        newValue = computeSecondOrder(dt);
        break;
    case ProcessType::Integrating:
        newValue = computeIntegrating(dt);
        break;
    case ProcessType::HeatExchanger:
        newValue = computeHeatExchanger(dt);
        break;
    case ProcessType::Pipeline:
        newValue = computePipeline(dt);
        break;
    case ProcessType::Custom:
        // Пользовательская логика может быть добавлена здесь
        newValue = computeFOPDT(dt);
        break;
    }
    
    // Добавление возмущения
    newValue += m_params.disturbance;
    
    // Добавление шума измерений
    if (m_params.noiseLevel > 0) {
        newValue += generateNoise();
    }
    
    // Обновление состояния
    m_previousInput = delayedInput;
    m_processValue = newValue;
    
    // Обновление статистики
    updateStatistics();
    
    emit processValueChanged(m_processValue);
    
    return m_processValue;
}

double ProcessModel::computeFOPDT(double dt)
{
    // First Order Plus Dead Time: T*dy/dt + y = K*u
    // Дискретизация методом Эйлера
    
    double K = m_params.gain;
    double T = m_params.timeConstant1;
    
    if (T <= 0) T = 0.1; // Защита от деления на ноль
    
    double dydt = (K * m_controlInput - m_processValue) / T;
    
    // Метод трапеций для лучшей точности
    double newDerivative = dydt;
    double avgDerivative = (m_derivative + newDerivative) / 2.0;
    
    double newValue = m_processValue + avgDerivative * dt;
    m_derivative = newDerivative;
    
    return newValue;
}

double ProcessModel::computeSecondOrder(double dt)
{
    // Second Order: T1*T2*d²y/dt² + (T1+T2)*dy/dt + y = K*u
    
    double K = m_params.gain;
    double T1 = m_params.timeConstant1;
    double T2 = m_params.timeConstant2;
    
    if (T1 <= 0) T1 = 1.0;
    if (T2 <= 0) T2 = 1.0;
    
    // Преобразуем в систему уравнений первого порядка
    // x1 = y, x2 = dy/dt
    // dx1/dt = x2
    // dx2/dt = (K*u - x1 - (T1+T2)*x2) / (T1*T2)
    
    double dx1dt = m_derivative;
    double dx2dt = (K * m_controlInput - m_processValue - (T1 + T2) * m_derivative) / (T1 * T2);
    
    // Интегрирование методом Рунге-Кутты 2-го порядка
    double k1_x1 = dx1dt * dt;
    double k1_x2 = dx2dt * dt;
    
    double mid_x1 = m_processValue + k1_x1 / 2.0;
    double mid_x2 = m_derivative + k1_x2 / 2.0;
    
    double mid_dx2dt = (K * m_controlInput - mid_x1 - (T1 + T2) * mid_x2) / (T1 * T2);
    
    double k2_x1 = mid_x2 * dt;
    double k2_x2 = mid_dx2dt * dt;
    
    double newValue = m_processValue + (k1_x1 + k2_x1) / 2.0;
    m_derivative = m_derivative + (k1_x2 + k2_x2) / 2.0;
    
    return newValue;
}

double ProcessModel::computeIntegrating(double dt)
{
    // Интегрирующее звено: dy/dt = K*u
    
    double K = m_params.gain;
    m_integralState += K * m_controlInput * dt;
    
    return m_integralState;
}

double ProcessModel::computeHeatExchanger(double dt)
{
    // Упрощенная модель теплообменника
    // dT/dt = (Q_in - Q_out) / (m*Cp)
    
    double hotFlow = m_params.hotFlowRate;
    double coldFlow = m_params.coldFlowRate;
    double hotInlet = m_params.hotInletTemp;
    double coldInlet = m_params.coldInletTemp;
    
    // Теплопередача пропорциональна разности температур и потоку
    double heatTransferCoeff = 0.01;
    double thermalMass = 100.0;
    
    double heatIn = hotFlow * heatTransferCoeff * (hotInlet - m_processValue);
    double heatOut = coldFlow * heatTransferCoeff * (m_processValue - coldInlet);
    
    double dTdt = (heatIn - heatOut) / thermalMass;
    
    // Добавляем влияние управляющего воздействия (например, положение клапана)
    dTdt += m_controlInput * 0.1;
    
    return m_processValue + dTdt * dt;
}

double ProcessModel::computePipeline(double dt)
{
    // Гидравлическая модель трубопровода
    // Упрощенное уравнение Дарси-Вейсбаха
    
    double length = m_params.pipeLength;
    double diameter = m_params.pipeDiameter;
    double viscosity = m_params.fluidViscosity;
    double inletPressure = m_params.inletPressure;
    
    // Расход пропорционален перепаду давления
    double flowCoefficient = M_PI * qPow(diameter, 4) / (128 * viscosity * length);
    double pressureDrop = m_processValue; // Выходное давление
    
    double dPdt = flowCoefficient * (inletPressure - pressureDrop) - m_controlInput * 0.01;
    
    return m_processValue + dPdt * dt;
}

void ProcessModel::updateStatistics()
{
    static double previousValue = 0;
    static bool firstStep = true;
    static double stepCount = 0;
    
    if (firstStep) {
        m_startTime = m_simulationTime;
        m_steadyStateValue = m_processValue;
        firstStep = false;
    }
    
    stepCount++;
    
    // Обновление установившегося значения (скользящее среднее)
    double alpha = 0.01;
    m_steadyStateValue = (1 - alpha) * m_steadyStateValue + alpha * m_processValue;
    
    // Поиск пика для вычисления перерегулирования
    if (m_processValue > m_peakValue) {
        m_peakValue = m_processValue;
    }
    
    // Вычисление перерегулирования
    if (!qFuzzyIsNull(m_steadyStateValue)) {
        m_overshoot = (m_peakValue - m_steadyStateValue) / qAbs(m_steadyStateValue) * 100.0;
    }
    
    // Время нарастания (от 10% до 90%)
    double targetValue = m_steadyStateValue;
    if (m_riseTime <= 0 && m_processValue >= 0.9 * targetValue) {
        m_riseTime = m_simulationTime - m_startTime;
    }
    
    // Время успокоения (вхождение в полосу 2%)
    if (m_settlingTime <= 0) {
        double tolerance = 0.02 * qAbs(targetValue);
        if (qAbs(m_processValue - targetValue) <= tolerance) {
            m_stableCounter++;
            if (m_stableCounter > 10) { // 10 последовательных шагов в полосе
                m_settlingTime = m_simulationTime - m_startTime;
            }
        } else {
            m_stableCounter = 0;
        }
    }
    
    // Проверка устойчивости
    double error = m_processValue - previousValue;
    if (qAbs(error) > 10.0) { // Резкое изменение - возможная неустойчивость
        m_stable = false;
        emit stabilityChanged(false);
    }
    
    previousValue = m_processValue;
}

void ProcessModel::applyDeadTime()
{
    // Реализовано в методе step()
}

double ProcessModel::generateNoise()
{
    // Генерация гауссовского шума
    double mean = 0.0;
    double stddev = m_params.noiseLevel;
    
    // Box-Muller transform
    double u1 = QRandomGenerator::global()->generateDouble();
    double u2 = QRandomGenerator::global()->generateDouble();
    
    double z0 = qSqrt(-2.0 * qLn(u1 + 1e-10)) * qCos(2 * M_PI * u2);
    
    return mean + z0 * stddev;
}

void ProcessModel::reset()
{
    m_processValue = 0.0;
    m_controlInput = 0.0;
    m_previousInput = 0.0;
    m_derivative = 0.0;
    m_integralState = 0.0;
    m_previousDerivative = 0.0;
    m_inputHistory.clear();
    
    m_steadyStateValue = 0.0;
    m_overshoot = 0.0;
    m_settlingTime = 0.0;
    m_riseTime = 0.0;
    m_peakValue = 0.0;
    
    m_saturated = false;
    m_stable = true;
    
    m_simulationTime = 0.0;
    m_simulationStartTime = QDateTime::currentDateTime();
    
    m_recentInputs.clear();
    m_recentOutputs.clear();
}

void ProcessModel::resetToSteadyState()
{
    // Установка процесса в установившееся состояние для текущего входа
    m_processValue = m_params.gain * m_controlInput;
    m_derivative = 0.0;
    m_integralState = m_processValue;
}

bool ProcessModel::identifyParameters(const QVector<double>& inputs,
                                      const QVector<double>& outputs,
                                      double sampleTime)
{
    if (inputs.size() != outputs.size() || inputs.size() < 10) {
        return false;
    }
    
    // Простая идентификация по методу площадей для FOPDT модели
    // Это упрощенная реализация; в реальной системе можно использовать
    // рекурсивный МНК или другие продвинутые методы
    
    int n = inputs.size();
    
    // Нахождение скачка входа
    int stepIndex = -1;
    for (int i = 1; i < n; ++i) {
        if (qAbs(inputs[i] - inputs[0]) > 0.1 * qAbs(inputs[i])) {
            stepIndex = i;
            break;
        }
    }
    
    if (stepIndex < 0) {
        return false; // Нет явного скачка
    }
    
    // Оценка коэффициента усиления
    double inputChange = inputs[n-1] - inputs[stepIndex];
    double outputChange = outputs[n-1] - outputs[stepIndex];
    
    if (qAbs(inputChange) < 1e-6) {
        return false;
    }
    
    m_params.gain = outputChange / inputChange;
    
    // Оценка постоянной времени (метод 63.2%)
    double targetValue = outputs[stepIndex] + 0.632 * outputChange;
    int t63Index = stepIndex;
    
    for (int i = stepIndex; i < n; ++i) {
        if (outputs[i] >= targetValue) {
            t63Index = i;
            break;
        }
    }
    
    m_params.timeConstant1 = (t63Index - stepIndex) * sampleTime;
    
    // Оценка времени задержки (метод касательной)
    // Упрощенно: находим время когда выход начинает реагировать
    int deadTimeIndex = stepIndex;
    double threshold = 0.05 * outputChange;
    
    for (int i = stepIndex; i < n; ++i) {
        if (qAbs(outputs[i] - outputs[stepIndex]) > threshold) {
            deadTimeIndex = i;
            break;
        }
    }
    
    m_params.deadTime = (deadTimeIndex - stepIndex) * sampleTime;
    
    emit parameterIdentified(m_params);
    
    return true;
}

bool ProcessModel::isStable() const
{
    return m_stable;
}

QVariantMap ProcessModel::exportModel() const
{
    QVariantMap data;
    data["processType"] = static_cast<int>(m_processType);
    data["gain"] = m_params.gain;
    data["timeConstant1"] = m_params.timeConstant1;
    data["timeConstant2"] = m_params.timeConstant2;
    data["deadTime"] = m_params.deadTime;
    data["disturbance"] = m_params.disturbance;
    data["noiseLevel"] = m_params.noiseLevel;
    data["hotFlowRate"] = m_params.hotFlowRate;
    data["coldFlowRate"] = m_params.coldFlowRate;
    data["hotInletTemp"] = m_params.hotInletTemp;
    data["coldInletTemp"] = m_params.coldInletTemp;
    data["pipeLength"] = m_params.pipeLength;
    data["pipeDiameter"] = m_params.pipeDiameter;
    data["fluidViscosity"] = m_params.fluidViscosity;
    data["inletPressure"] = m_params.inletPressure;
    return data;
}

void ProcessModel::importModel(const QVariantMap& data)
{
    if (data.contains("processType")) {
        m_processType = static_cast<ProcessType>(data["processType"].toInt());
    }
    if (data.contains("gain")) m_params.gain = data["gain"].toDouble();
    if (data.contains("timeConstant1")) m_params.timeConstant1 = data["timeConstant1"].toDouble();
    if (data.contains("timeConstant2")) m_params.timeConstant2 = data["timeConstant2"].toDouble();
    if (data.contains("deadTime")) m_params.deadTime = data["deadTime"].toDouble();
    if (data.contains("disturbance")) m_params.disturbance = data["disturbance"].toDouble();
    if (data.contains("noiseLevel")) m_params.noiseLevel = data["noiseLevel"].toDouble();
    if (data.contains("hotFlowRate")) m_params.hotFlowRate = data["hotFlowRate"].toDouble();
    if (data.contains("coldFlowRate")) m_params.coldFlowRate = data["coldFlowRate"].toDouble();
    if (data.contains("hotInletTemp")) m_params.hotInletTemp = data["hotInletTemp"].toDouble();
    if (data.contains("coldInletTemp")) m_params.coldInletTemp = data["coldInletTemp"].toDouble();
    if (data.contains("pipeLength")) m_params.pipeLength = data["pipeLength"].toDouble();
    if (data.contains("pipeDiameter")) m_params.pipeDiameter = data["pipeDiameter"].toDouble();
    if (data.contains("fluidViscosity")) m_params.fluidViscosity = data["fluidViscosity"].toDouble();
    if (data.contains("inletPressure")) m_params.inletPressure = data["inletPressure"].toDouble();
}
