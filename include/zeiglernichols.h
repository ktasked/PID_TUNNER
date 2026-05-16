#ifndef ZEIGLERNICHOLS_H
#define ZEIGLERNICHOLS_H

#include "tuningmethod.h"

/**
 * @brief Метод настройки ПИД Циглера-Никольса
 * 
 * Классический метод настройки, разработанный в 1942 году.
 * Поддерживает два варианта:
 * 1. Метод разгона (Process Reaction Curve)
 * 2. Метод предельных колебаний (Ultimate Gain)
 * 
 * @note Патентоспособные модификации:
 * - Адаптивная версия с коррекцией на нелинейности
 */
class ZieglerNichols : public TuningMethod
{
    Q_OBJECT
    
public:
    enum class Variant {
        ProcessReactionCurve,  // По кривой разгона
        UltimateGain           // По предельному коэффициенту усиления
    };
    
    explicit ZieglerNichols(Variant variant = Variant::ProcessReactionCurve, 
                           QObject *parent = nullptr);
    
    TuningResult tune(const ProcessModel::ModelParameters& params) override;
    
    QString methodName() const override { return "Ziegler-Nichols"; }
    QString methodDescription() const override;
    MethodType methodType() const override { return MethodType::ZieglerNichols; }
    
    bool isApplicable(const ProcessModel::ModelParameters& params) const override;
    
    // Установка варианта метода
    void setVariant(Variant variant) { m_variant = variant; }
    Variant variant() const { return m_variant; }
    
    // Для метода предельных колебаний
    void setUltimateGain(double Ku) { m_Ku = Ku; }
    void setUltimatePeriod(double Pu) { m_Pu = Pu; }

private:
    TuningResult tuneByReactionCurve(const ProcessModel::ModelParameters& params);
    TuningResult tuneByUltimateGain();
    
    Variant m_variant = Variant::ProcessReactionCurve;
    double m_Ku = 0.0;  // Предельный коэффициент усиления
    double m_Pu = 0.0;  // Период предельных колебаний
};

#endif // ZEIGLERNICHOLS_H
