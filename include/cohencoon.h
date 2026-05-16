#ifndef COHENCOON_H
#define COHENCOON_H

#include "tuningmethod.h"

/**
 * @brief Метод настройки ПИД Коэна-Куна
 * 
 * Улучшенный метод для процессов с большим временем задержки.
 * Разработан в 1953 году как модификация метода Циглера-Никольса.
 * 
 * @note Патентоспособные модификации:
 * - Адаптивная коррекция для нелинейных процессов нефтегазовой отрасли
 */
class CohenCoon : public TuningMethod
{
    Q_OBJECT
    
public:
    explicit CohenCoon(QObject *parent = nullptr);
    
    TuningResult tune(const ProcessModel::ModelParameters& params) override;
    
    QString methodName() const override { return "Cohen-Coon"; }
    QString methodDescription() const override;
    MethodType methodType() const override { return MethodType::CohenCoon; }
    
    bool isApplicable(const ProcessModel::ModelParameters& params) const override;

private:
    double calculateCorrectionFactor(double ratio) const;
};

#endif // COHENCOON_H
