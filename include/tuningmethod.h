#ifndef TUNINGMETHOD_H
#define TUNINGMETHOD_H

#include <QObject>
#include <QVariantMap>
#include "processmodel.h"

/**
 * @brief Базовый класс для методов настройки ПИД-регуляторов
 * 
 * Абстрактный класс, определяющий интерфейс для всех методов настройки.
 * Поддерживает различные подходы к настройке ПИД.
 * 
 * @note Патентоспособные особенности:
 * - Гибридные методы настройки
 * - Адаптивный выбор метода на основе характеристик процесса
 */
class TuningMethod : public QObject
{
    Q_OBJECT
    
public:
    enum class MethodType {
        ZieglerNichols,
        CohenCoon,
        InternalModelControl,
        TyreusLuyben,
        IMCwithFilter,
        OptimizationBased,
        Adaptive,
        Custom
    };
    
    struct TuningResult {
        double kp = 0.0;
        double ki = 0.0;
        double kd = 0.0;
        double Ti = 0.0;  // Время интегрирования
        double Td = 0.0;  // Время дифференцирования
        
        // Дополнительные параметры
        double filterTimeConstant = 0.0;
        double setpointWeight = 1.0;  // Вес уставки для пропорциональной составляющей
        
        // Метрики качества
        double expectedOvershoot = 0.0;
        double expectedSettlingTime = 0.0;
        double robustnessMargin = 0.0;
        
        // Рекомендации
        QString recommendations;
        bool isValid = false;
    };
    
    explicit TuningMethod(QObject *parent = nullptr);
    virtual ~TuningMethod() = default;
    
    // Основной метод настройки
    virtual TuningResult tune(const ProcessModel::ModelParameters& params) = 0;
    
    // Настройка по экспериментальным данным
    virtual TuningResult tuneFromData(const QVector<double>& inputs,
                                      const QVector<double>& outputs,
                                      double sampleTime);
    
    // Получение информации о методе
    virtual QString methodName() const = 0;
    virtual QString methodDescription() const = 0;
    virtual MethodType methodType() const = 0;
    
    // Проверка применимости метода
    virtual bool isApplicable(const ProcessModel::ModelParameters& params) const;
    
    // Экспорт/импорт результатов
    QVariantMap exportResult(const TuningResult& result) const;
    TuningResult importResult(const QVariantMap& data) const;
    
protected:
    // Вспомогательные методы
    double calculateGainMargin(double K, double T, double L) const;
    double calculatePhaseMargin(double K, double T, double L) const;
    void validateResult(TuningResult& result) const;
};

#endif // TUNINGMETHOD_H
