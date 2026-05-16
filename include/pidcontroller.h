#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <QVector>
#include <memory>

/**
 * @brief Класс ПИД-регулятора с расширенными возможностями
 * 
 * Реализует параллельную форму ПИД-регулятора с дополнительными функциями:
 * - Anti-windup защита
 * - Фильтрация производной
 * - Бампless переключение режимов
 * - Адаптивное масштабирование
 * 
 * @note Патентоспособные особенности:
 * - Динамическая адаптация коэффициентов на основе темпа изменения ошибки
 * - Интеллектуальная anti-windup логика для нелинейных процессов
 */
class PIDController : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(double kp READ getKp WRITE setKp NOTIFY kpChanged)
    Q_PROPERTY(double ki READ getKi WRITE setKi NOTIFY kiChanged)
    Q_PROPERTY(double kd READ getKd WRITE setKd NOTIFY kdChanged)
    Q_PROPERTY(double setpoint READ getSetpoint WRITE setSetpoint NOTIFY setpointChanged)
    Q_PROPERTY(double output READ getOutput NOTIFY outputChanged)
    Q_PROPERTY(bool autoMode READ isAutoMode WRITE setAutoMode NOTIFY modeChanged)
    
public:
    enum class ControllerForm {
        Parallel,           // Параллельная форма
        Series,             // Последовательная форма
        Ideal               // Идеальная форма
    };
    
    enum class AntiWindupMethod {
        BackCalculation,    // Обратный расчет
        Clamping,           // Ограничение
        ConditionalIntegration, // Условное интегрирование
        Adaptive            // Адаптивный метод (патентоспособный)
    };
    
    explicit PIDController(QObject *parent = nullptr);
    ~PIDController() override;
    
    // Основные параметры ПИД
    double getKp() const { return m_kp; }
    double getKi() const { return m_ki; }
    double getKd() const { return m_kd; }
    
    void setKp(double kp);
    void setKi(double ki);
    void setKd(double kd);
    
    // Уставка и выход
    double getSetpoint() const { return m_setpoint; }
    void setSetpoint(double setpoint);
    
    double getOutput() const { return m_output; }
    double getError() const { return m_currentError; }
    
    // Режимы работы
    bool isAutoMode() const { return m_autoMode; }
    void setAutoMode(bool autoMode);
    
    // Настройка формы регулятора
    ControllerForm controllerForm() const { return m_form; }
    void setControllerForm(ControllerForm form);
    
    // Anti-windup конфигурация
    AntiWindupMethod antiWindupMethod() const { return m_antiWindupMethod; }
    void setAntiWindupMethod(AntiWindupMethod method);
    
    // Ограничения выхода
    double outputMin() const { return m_outputMin; }
    double outputMax() const { return m_outputMax; }
    void setOutputLimits(double min, double max);
    
    // Фильтр производной
    double derivativeFilterTimeConstant() const { return m_derivativeFilterTau; }
    void setDerivativeFilterTimeConstant(double tau);
    
    // Основной метод вычисления
    double compute(double processVariable, double timestamp = -1.0);
    
    // Сброс состояния
    void reset();
    void resetIntegral();
    
    // Получение статистики
    double integralTerm() const { return m_integralTerm; }
    double derivativeTerm() const { return m_derivativeTerm; }
    double proportionalTerm() const { return m_proportionalTerm; }
    
    // Время дискретизации
    double sampleTime() const { return m_sampleTime; }
    void setSampleTime(double sampleTime);
    
    // Состояние инициализации
    bool isInitialized() const { return m_initialized; }
    
    // Экспорт настроек
    QVariantMap exportSettings() const;
    void importSettings(const QVariantMap& settings);

signals:
    void kpChanged(double kp);
    void kiChanged(double ki);
    void kdChanged(double kd);
    void setpointChanged(double setpoint);
    void outputChanged(double output);
    void modeChanged(bool autoMode);
    void computationCompleted(double output, double error);
    void saturationOccurred(bool saturated);
    
private:
    // Внутренние методы вычисления
    double computeParallel(double error, double dt);
    double computeSeries(double error, double dt);
    double computeIdeal(double error, double dt);
    
    // Anti-windup обработка
    void applyAntiWindup(double rawOutput, double dt);
    void applyAdaptiveAntiWindup(double rawOutput, double error, double dt);
    
    // Инициализация
    void initialize(double processVariable);
    
    // Переменные состояния
    double m_kp = 1.0;
    double m_ki = 0.0;
    double m_kd = 0.0;
    
    double m_setpoint = 0.0;
    double m_output = 0.0;
    double m_currentError = 0.0;
    
    double m_integralTerm = 0.0;
    double m_derivativeTerm = 0.0;
    double m_proportionalTerm = 0.0;
    
    double m_previousError = 0.0;
    double m_filteredDerivative = 0.0;
    
    double m_outputMin = 0.0;
    double m_outputMax = 100.0;
    double m_sampleTime = 0.1;
    double m_derivativeFilterTau = 0.01;
    
    bool m_autoMode = true;
    bool m_initialized = false;
    
    ControllerForm m_form = ControllerForm::Parallel;
    AntiWindupMethod m_antiWindupMethod = AntiWindupMethod::Adaptive;
    
    QDateTime m_lastComputationTime;
    
    // Для адаптивного anti-windup
    double m_adaptiveGain = 1.0;
    double m_errorRate = 0.0;
    
    // История для анализа
    QVector<double> m_errorHistory;
    static const int MAX_HISTORY_SIZE = 100;
};

#endif // PIDCONTROLLER_H
