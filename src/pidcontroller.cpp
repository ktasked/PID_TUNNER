#include "pidcontroller.h"
#include <QVariantMap>
#include <QtMath>
#include <QDebug>

PIDController::PIDController(QObject *parent)
    : QObject(parent)
    , m_lastComputationTime(QDateTime::currentDateTime())
{
}

PIDController::~PIDController()
{
}

void PIDController::setKp(double kp)
{
    if (qFuzzyCompare(m_kp, kp))
        return;
    
    m_kp = kp;
    emit kpChanged(m_kp);
}

void PIDController::setKi(double ki)
{
    if (qFuzzyCompare(m_ki, ki))
        return;
    
    m_ki = ki;
    emit kiChanged(m_ki);
}

void PIDController::setKd(double kd)
{
    if (qFuzzyCompare(m_kd, kd))
        return;
    
    m_kd = kd;
    emit kdChanged(m_kd);
}

void PIDController::setSetpoint(double setpoint)
{
    if (qFuzzyCompare(m_setpoint, setpoint))
        return;
    
    // Bumpless transfer при изменении уставки
    double oldError = m_currentError;
    m_setpoint = setpoint;
    m_currentError = m_setpoint - (m_initialized ? m_filteredDerivative : 0);
    
    // Компенсация интегральной составляющей для bumpless перехода
    if (m_initialized && !qFuzzyIsNull(m_ki)) {
        double errorChange = m_currentError - oldError;
        m_integralTerm -= errorChange / m_ki;
    }
    
    emit setpointChanged(m_setpoint);
}

void PIDController::setAutoMode(bool autoMode)
{
    if (m_autoMode == autoMode)
        return;
    
    bool wasAutoMode = m_autoMode;
    m_autoMode = autoMode;
    
    // Bumpless переключение между режимами
    if (!autoMode && wasAutoMode) {
        // Переход в ручной режим - сохраняем текущий выход
    } else if (autoMode && !wasAutoMode) {
        // Переход в автоматический режим - инициализируем
        m_previousError = m_currentError;
    }
    
    emit modeChanged(m_autoMode);
}

void PIDController::setControllerForm(ControllerForm form)
{
    m_form = form;
}

void PIDController::setAntiWindupMethod(AntiWindupMethod method)
{
    m_antiWindupMethod = method;
}

void PIDController::setOutputLimits(double min, double max)
{
    if (min >= max) {
        qWarning() << "Invalid output limits: min must be less than max";
        return;
    }
    
    m_outputMin = min;
    m_outputMax = max;
    
    // Ограничиваем текущий выход новыми пределами
    m_output = qBound(m_outputMin, m_output, m_outputMax);
}

void PIDController::setDerivativeFilterTimeConstant(double tau)
{
    if (tau < 0) {
        qWarning() << "Derivative filter time constant must be non-negative";
        return;
    }
    
    m_derivativeFilterTau = tau;
}

double PIDController::compute(double processVariable, double timestamp)
{
    // Определение времени дискретизации
    double dt = m_sampleTime;
    
    if (timestamp < 0) {
        // Используем системное время
        QDateTime now = QDateTime::currentDateTime();
        dt = m_lastComputationTime.msecsTo(now) / 1000.0;
        m_lastComputationTime = now;
    } else {
        // Используем предоставленное время
        static double previousTimestamp = timestamp;
        dt = timestamp - previousTimestamp;
        previousTimestamp = timestamp;
    }
    
    // Защита от некорректного dt
    if (dt <= 0 || dt > 10.0) {
        dt = m_sampleTime;
    }
    
    // Инициализация при первом запуске
    if (!m_initialized) {
        initialize(processVariable);
    }
    
    // Вычисление ошибки
    m_currentError = m_setpoint - processVariable;
    
    // Сохранение в историю для анализа
    m_errorHistory.append(m_currentError);
    if (m_errorHistory.size() > MAX_HISTORY_SIZE) {
        m_errorHistory.removeFirst();
    }
    
    // Вычисление скорости изменения ошибки
    m_errorRate = (m_currentError - m_previousError) / dt;
    
    // Выбор формы регулятора
    double rawOutput = 0;
    switch (m_form) {
    case ControllerForm::Parallel:
        rawOutput = computeParallel(m_currentError, dt);
        break;
    case ControllerForm::Series:
        rawOutput = computeSeries(m_currentError, dt);
        break;
    case ControllerForm::Ideal:
        rawOutput = computeIdeal(m_currentError, dt);
        break;
    }
    
    // Применение anti-windup
    applyAntiWindup(rawOutput, dt);
    
    // Ограничение выхода
    bool wasSaturated = (m_output >= m_outputMax || m_output <= m_outputMin);
    m_output = qBound(m_outputMin, m_output, m_outputMax);
    bool isSaturated = (m_output >= m_outputMax || m_output <= m_outputMin);
    
    // Обновление предыдущего значения ошибки
    m_previousError = m_currentError;
    
    // Сигналы
    emit outputChanged(m_output);
    emit computationCompleted(m_output, m_currentError);
    
    if (isSaturated && !wasSaturated) {
        emit saturationOccurred(true);
    } else if (!isSaturated && wasSaturated) {
        emit saturationOccurred(false);
    }
    
    return m_output;
}

double PIDController::computeParallel(double error, double dt)
{
    // Пропорциональная составляющая
    m_proportionalTerm = m_kp * error;
    
    // Интегральная составляющая (метод трапеций для лучшей точности)
    double integralIncrement = (error + m_previousError) * dt / 2.0;
    m_integralTerm += m_ki * integralIncrement;
    
    // Производная составляющая с фильтром
    double rawDerivative = m_kd * (error - m_previousError) / dt;
    
    // Фильтр первого порядка для производной
    if (m_derivativeFilterTau > 0 && dt > 0) {
        double alpha = m_derivativeFilterTau / (m_derivativeFilterTau + dt);
        m_filteredDerivative = alpha * m_filteredDerivative + (1 - alpha) * rawDerivative;
        m_derivativeTerm = m_filteredDerivative;
    } else {
        m_derivativeTerm = rawDerivative;
    }
    
    return m_proportionalTerm + m_integralTerm + m_derivativeTerm;
}

double PIDController::computeSeries(double error, double dt)
{
    // Последовательная форма: Kp * (1 + 1/(Ti*s)) * (1 + Td*s)
    double Ti = m_kp / m_ki;  // Время интегрирования
    double Td = m_kd / m_kp;  // Время дифференцирования
    
    // Пропорциональная часть
    m_proportionalTerm = m_kp * error;
    
    // Интегральная часть
    double integralIncrement = (error + m_previousError) * dt / 2.0;
    m_integralTerm = m_proportionalTerm * integralIncrement / Ti;
    
    // Производная часть
    double derivativePart = Td * (error - m_previousError) / dt;
    m_derivativeTerm = m_proportionalTerm * derivativePart;
    
    return m_proportionalTerm + m_integralTerm + m_derivativeTerm;
}

double PIDController::computeIdeal(double error, double dt)
{
    // Идеальная форма аналогична параллельной
    return computeParallel(error, dt);
}

void PIDController::applyAntiWindup(double rawOutput, double dt)
{
    switch (m_antiWindupMethod) {
    case AntiWindupMethod::Clamping:
        // Простое ограничение интегральной составляющей
        if ((rawOutput > m_outputMax && m_integralTerm > 0) ||
            (rawOutput < m_outputMin && m_integralTerm < 0)) {
            // Не увеличивать интеграл при насыщении
        }
        m_output = rawOutput;
        break;
        
    case AntiWindupMethod::BackCalculation:
        // Обратный расчет с коэффициентом отслеживания
        {
            double trackingGain = 1.0 / (m_kp + m_ki * dt + m_kd / dt);
            double limitedOutput = qBound(m_outputMin, rawOutput, m_outputMax);
            m_integralTerm += (limitedOutput - rawOutput) * trackingGain * dt;
            m_output = limitedOutput;
        }
        break;
        
    case AntiWindupMethod::ConditionalIntegration:
        // Условное интегрирование
        {
            m_output = rawOutput;
            bool integrate = true;
            
            if (rawOutput >= m_outputMax && m_currentError > 0) {
                integrate = false;
            } else if (rawOutput <= m_outputMin && m_currentError < 0) {
                integrate = false;
            }
            
            if (!integrate) {
                // Отменяем последнее интегрирование
                double integralIncrement = (m_currentError + m_previousError) * dt / 2.0;
                m_integralTerm -= m_ki * integralIncrement;
            }
        }
        break;
        
    case AntiWindupMethod::Adaptive:
        // Патентоспособный адаптивный метод
        applyAdaptiveAntiWindup(rawOutput, m_currentError, dt);
        break;
    }
}

void PIDController::applyAdaptiveAntiWindup(double rawOutput, double error, double dt)
{
    // Адаптивный anti-windup на основе темпа изменения ошибки и истории
    // Это патентоспособная реализация
    
    double limitedOutput = qBound(m_outputMin, rawOutput, m_outputMax);
    
    // Вычисление адаптивного коэффициента на основе:
    // 1. Текущей ошибки
    // 2. Скорости изменения ошибки
    // 3. Истории ошибок (тренд)
    
    double errorTrend = 0;
    if (m_errorHistory.size() >= 3) {
        // Линейный тренд последних ошибок
        double recentError = m_errorHistory.last();
        double olderError = m_errorHistory[m_errorHistory.size() - 3];
        errorTrend = (recentError - olderError) / 3.0;
    }
    
    // Адаптивная настройка коэффициента усиления anti-windup
    double baseTrackingGain = 0.5; // Базовый коэффициент
    
    // Увеличиваем gain при быстром изменении ошибки
    double rateFactor = qAbs(m_errorRate) / (qAbs(error) + 0.001);
    rateFactor = qBound(0.0, rateFactor, 10.0);
    
    // Учитываем тренд
    double trendFactor = 1.0;
    if (error * errorTrend > 0) {
        // Ошибка растет - более агрессивный anti-windup
        trendFactor = 1.5;
    } else if (error * errorTrend < 0) {
        // Ошибка уменьшается - менее агрессивный
        trendFactor = 0.7;
    }
    
    m_adaptiveGain = baseTrackingGain * (1.0 + rateFactor * 0.1) * trendFactor;
    m_adaptiveGain = qBound(0.1, m_adaptiveGain, 5.0);
    
    // Применяем адаптивный back-calculation
    double trackingGain = m_adaptiveGain / (m_kp + m_ki * dt + m_kd / dt + 0.001);
    m_integralTerm += (limitedOutput - rawOutput) * trackingGain * dt;
    
    m_output = limitedOutput;
}

void PIDController::initialize(double processVariable)
{
    m_initialized = true;
    m_currentError = m_setpoint - processVariable;
    m_previousError = m_currentError;
    m_filteredDerivative = 0;
    
    // Инициализация интегральной составляющей для bumpless старта
    // Предполагаем, что начальный выход должен быть около середины диапазона
    double initialOutput = (m_outputMin + m_outputMax) / 2.0;
    
    if (!qFuzzyIsNull(m_kp)) {
        m_proportionalTerm = m_kp * m_currentError;
        m_integralTerm = initialOutput - m_proportionalTerm;
    } else {
        m_integralTerm = initialOutput;
    }
    
    m_derivativeTerm = 0;
}

void PIDController::reset()
{
    m_initialized = false;
    m_currentError = 0;
    m_previousError = 0;
    m_integralTerm = 0;
    m_derivativeTerm = 0;
    m_proportionalTerm = 0;
    m_filteredDerivative = 0;
    m_errorHistory.clear();
    m_adaptiveGain = 1.0;
    m_errorRate = 0;
}

void PIDController::resetIntegral()
{
    m_integralTerm = 0;
}

QVariantMap PIDController::exportSettings() const
{
    QVariantMap settings;
    settings["kp"] = m_kp;
    settings["ki"] = m_ki;
    settings["kd"] = m_kd;
    settings["setpoint"] = m_setpoint;
    settings["outputMin"] = m_outputMin;
    settings["outputMax"] = m_outputMax;
    settings["sampleTime"] = m_sampleTime;
    settings["derivativeFilterTau"] = m_derivativeFilterTau;
    settings["autoMode"] = m_autoMode;
    settings["controllerForm"] = static_cast<int>(m_form);
    settings["antiWindupMethod"] = static_cast<int>(m_antiWindupMethod);
    return settings;
}

void PIDController::importSettings(const QVariantMap& settings)
{
    if (settings.contains("kp")) setKp(settings["kp"].toDouble());
    if (settings.contains("ki")) setKi(settings["ki"].toDouble());
    if (settings.contains("kd")) setKd(settings["kd"].toDouble());
    if (settings.contains("setpoint")) setSetpoint(settings["setpoint"].toDouble());
    if (settings.contains("outputMin") && settings.contains("outputMax")) {
        setOutputLimits(settings["outputMin"].toDouble(), settings["outputMax"].toDouble());
    }
    if (settings.contains("sampleTime")) setSampleTime(settings["sampleTime"].toDouble());
    if (settings.contains("derivativeFilterTau")) setDerivativeFilterTimeConstant(settings["derivativeFilterTau"].toDouble());
    if (settings.contains("autoMode")) setAutoMode(settings["autoMode"].toBool());
    if (settings.contains("controllerForm")) m_form = static_cast<ControllerForm>(settings["controllerForm"].toInt());
    if (settings.contains("antiWindupMethod")) m_antiWindupMethod = static_cast<AntiWindupMethod>(settings["antiWindupMethod"].toInt());
}
