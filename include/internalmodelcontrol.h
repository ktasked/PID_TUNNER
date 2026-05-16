#ifndef INTERNALMODELCONTROL_H
#define INTERNALMODELCONTROL_H

#include "tuningmethod.h"

/**
 * @brief Метод настройки на основе внутренней модели (IMC)
 * 
 * Современный метод настройки, основанный на принципе внутренней модели.
 * Обеспечивает оптимальный баланс между производительностью и робастностью.
 * 
 * @note Патентоспособные особенности:
 * - Адаптивный выбор времени замкнутого контура
 * - Интеграция с фильтрацией шума для нефтегазовых применений
 */
class InternalModelControl : public TuningMethod
{
    Q_OBJECT
    
public:
    explicit InternalModelControl(QObject *parent = nullptr);
    
    TuningResult tune(const ProcessModel::ModelParameters& params) override;
    
    QString methodName() const override { return "Internal Model Control (IMC)"; }
    QString methodDescription() const override;
    MethodType methodType() const override { return MethodType::InternalModelControl; }
    
    bool isApplicable(const ProcessModel::ModelParameters& params) const override;
    
    // Настройка параметров IMC
    void setClosedLoopTimeConstant(double tau) { m_tau_cl = tau; }
    double closedLoopTimeConstant() const { return m_tau_cl; }
    
    void setAutoTuningTau(bool autoTau) { m_autoTau = autoTau; }
    bool autoTuningTau() const { return m_autoTau; }

private:
    double calculateOptimalTau(const ProcessModel::ModelParameters& params) const;
    TuningResult tuneStandardIMC(const ProcessModel::ModelParameters& params, double tau);
    TuningResult tuneIMCwithFilter(const ProcessModel::ModelParameters& params, double tau);
    
    double m_tau_cl = 0.0;  // Время замкнутого контура (0 = автовыбор)
    bool m_autoTau = true;  // Автоматический выбор tau
};

#endif // INTERNALMODELCONTROL_H
