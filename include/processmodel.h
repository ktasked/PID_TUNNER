#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QObject>
#include <QVector>
#include <QDateTime>

/**
 * @brief Модель технологического процесса для нефтегазовой отрасли
 * 
 * Симулирует различные типы процессов:
 * - Резервуары с жидкостью
 * - Теплообменники
 * - Трубопроводы
 * - Реакторы
 * 
 * @note Патентоспособные особенности:
 * - Адаптивная модель с идентификацией параметров в реальном времени
 * - Учет нелинейностей и возмущений
 */
class ProcessModel : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(double processValue READ getProcessValue NOTIFY processValueChanged)
    Q_PROPERTY(double controlInput READ getControlInput WRITE setControlInput NOTIFY controlInputChanged)
    Q_PROPERTY(ProcessType processType READ getProcessType WRITE setProcessType NOTIFY processTypeChanged)
    
public:
    enum class ProcessType {
        FirstOrder,         // Апериодическое звено первого порядка
        SecondOrder,        // Апериодическое звено второго порядка
        FOPDT,              // First Order Plus Dead Time (наиболее распространен в нефтегазе)
        Integrating,        // Интегрирующее звено (уровень в резервуаре)
        HeatExchanger,      // Теплообменник (специфичная модель)
        Pipeline,           // Трубопровод (гидравлическая модель)
        Custom              // Пользовательская модель
    };
    
    struct ModelParameters {
        double gain = 1.0;          // Коэффициент усиления K
        double timeConstant1 = 10.0; // Постоянная времени T1
        double timeConstant2 = 5.0;  // Постоянная времени T2 (для второго порядка)
        double deadTime = 2.0;       // Время задержки L/theta
        double disturbance = 0.0;    // Возмущение
        double noiseLevel = 0.0;     // Уровень шума измерений
        
        // Для теплообменника
        double hotFlowRate = 100.0;
        double coldFlowRate = 100.0;
        double hotInletTemp = 150.0;
        double coldInletTemp = 20.0;
        
        // Для трубопровода
        double pipeLength = 1000.0;
        double pipeDiameter = 0.5;
        double fluidViscosity = 0.001;
        double inletPressure = 10.0;
    };
    
    explicit ProcessModel(QObject *parent = nullptr);
    ~ProcessModel() override;
    
    // Основные методы
    double getProcessValue() const { return m_processValue; }
    double getControlInput() const { return m_controlInput; }
    void setControlInput(double input);
    
    ProcessType getProcessType() const { return m_processType; }
    void setProcessType(ProcessType type);
    
    // Параметры модели
    ModelParameters parameters() const { return m_params; }
    void setParameters(const ModelParameters& params);
    
    // Отдельные параметры
    void setGain(double gain);
    void setTimeConstant(double tc);
    void setDeadTime(double deadTime);
    void setDisturbance(double disturbance);
    void setNoiseLevel(double noiseLevel);
    
    // Шаг симуляции
    double step(double dt = 0.1);
    
    // Сброс состояния
    void reset();
    void resetToSteadyState();
    
    // Идентификация параметров по входным/выходным данным
    bool identifyParameters(const QVector<double>& inputs, 
                           const QVector<double>& outputs,
                           double sampleTime);
    
    // Проверка устойчивости
    bool isStable() const;
    bool isSaturated() const { return m_saturated; }
    
    // Статистика
    double getSteadyStateValue() const { return m_steadyStateValue; }
    double getOvershoot() const { return m_overshoot; }
    double getSettlingTime() const { return m_settlingTime; }
    double getRiseTime() const { return m_riseTime; }
    
    // Экспорт/импорт
    QVariantMap exportModel() const;
    void importModel(const QVariantMap& data);

signals:
    void processValueChanged(double value);
    void controlInputChanged(double input);
    void processTypeChanged(ProcessType type);
    void parameterIdentified(const ModelParameters& params);
    void saturationChanged(bool saturated);
    void stabilityChanged(bool stable);
    
private:
    // Методы вычисления для разных типов процессов
    double computeFOPDT(double dt);
    double computeSecondOrder(double dt);
    double computeIntegrating(double dt);
    double computeHeatExchanger(double dt);
    double computePipeline(double dt);
    
    // Вспомогательные методы
    void updateStatistics();
    void applyDeadTime();
    double generateNoise();
    
    // Состояние процесса
    double m_processValue = 0.0;
    double m_controlInput = 0.0;
    double m_previousInput = 0.0;
    double m_derivative = 0.0;
    
    ModelParameters m_params;
    ProcessType m_processType = ProcessType::FOPDT;
    
    // История для dead time
    QVector<QPair<double, double>> m_inputHistory; // <timestamp, input>
    static const int MAX_HISTORY_SIZE = 1000;
    
    // Для интегрирования
    double m_integralState = 0.0;
    double m_previousDerivative = 0.0;
    
    // Статистика переходного процесса
    double m_steadyStateValue = 0.0;
    double m_overshoot = 0.0;
    double m_settlingTime = 0.0;
    double m_riseTime = 0.0;
    double m_peakValue = 0.0;
    double m_startTime = 0.0;
    
    bool m_saturated = false;
    bool m_stable = true;
    
    QDateTime m_simulationStartTime;
    double m_simulationTime = 0.0;
    
    // Для идентификации
    QVector<double> m_recentInputs;
    QVector<double> m_recentOutputs;
};

#endif // PROCESSMODEL_H
