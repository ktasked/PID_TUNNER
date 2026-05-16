#include "zeiglernichols.h"
#include <QtMath>
#include <QDebug>

ZieglerNichols::ZieglerNichols(Variant variant, QObject *parent)
    : TuningMethod(parent)
    , m_variant(variant)
{
}

QString ZieglerNichols::methodDescription() const
{
    return "Классический метод Циглера-Никольса (1942). "
           "Обеспечивает быстрое время отклика с перерегулированием около 25%. "
           "Рекомендуется для процессов с малым временем задержки.";
}

bool ZieglerNichols::isApplicable(const ProcessModel::ModelParameters& params) const
{
    if (!TuningMethod::isApplicable(params))
        return false;
    
    // Для метода разгона требуется L/T < 1
    if (m_variant == Variant::ProcessReactionCurve) {
        double ratio = params.deadTime / params.timeConstant1;
        return ratio < 1.0;
    }
    
    // Для метода предельных колебаний нужны Ku и Pu
    if (m_variant == Variant::UltimateGain) {
        return m_Ku > 0 && m_Pu > 0;
    }
    
    return true;
}

TuningMethod::TuningResult ZieglerNichols::tune(const ProcessModel::ModelParameters& params)
{
    TuningMethod::TuningResult result;
    
    switch (m_variant) {
    case Variant::ProcessReactionCurve:
        result = tuneByReactionCurve(params);
        break;
    case Variant::UltimateGain:
        result = tuneByUltimateGain();
        break;
    }
    
    validateResult(result);
    return result;
}

TuningMethod::TuningResult ZieglerNichols::tuneByReactionCurve(const ProcessModel::ModelParameters& params)
{
    TuningMethod::TuningResult result;
    
    double K = params.gain;
    double T = params.timeConstant1;
    double L = params.deadTime;
    
    if (T <= 0 || L < 0) {
        result.isValid = false;
        result.recommendations = "Invalid process parameters";
        return result;
    }
    
    // Отношение задержки к постоянной времени
    double ratio = L / T;
    
    // Таблица коэффициентов Циглера-Никольса для метода разгона
    // P-регулятор
    double kp_P = T / (K * L);
    
    // PI-регулятор
    double kp_PI = 0.9 * T / (K * L);
    double Ti_PI = 3.33 * L;
    
    // PID-регулятор (классическая форма)
    double kp_PID = 1.2 * T / (K * L);
    double Ti_PID = 2.0 * L;
    double Td_PID = 0.5 * L;
    
    // Выбор PID конфигурации
    result.kp = kp_PID;
    result.Ti = Ti_PID;
    result.Td = Td_PID;
    
    // Преобразование к параллельной форме
    result.ki = result.kp / result.Ti;
    result.kd = result.kp * result.Td;
    
    // Оценка качества
    result.expectedOvershoot = 25.0; // Ожидаемое перерегулирование ~25%
    result.expectedSettlingTime = 4.0 * (L + T);
    
    // Рекомендации
    if (ratio > 0.6) {
        result.recommendations = "Высокое отношение L/T. Рассмотрите метод Cohen-Coon или IMC.";
    } else if (ratio < 0.1) {
        result.recommendations = "Малое время задержки. Можно использовать более агрессивную настройку.";
    }
    
    result.recommendations += QString("\nОтношение L/T = %1").arg(ratio, 0, 'f', 2);
    
    return result;
}

TuningResult ZieglerNichols::tuneByUltimateGain()
{
    TuningResult result;
    
    if (m_Ku <= 0 || m_Pu <= 0) {
        result.isValid = false;
        result.recommendations = "Необходимо установить Ku и Pu";
        return result;
    }
    
    // Таблица коэффициентов для метода предельных колебаний
    // P-регулятор
    double kp_P = 0.5 * m_Ku;
    
    // PI-регулятор
    double kp_PI = 0.45 * m_Ku;
    double Ti_PI = m_Pu / 1.2;
    
    // PID-регулятор
    double kp_PID = 0.6 * m_Ku;
    double Ti_PID = m_Pu / 2.0;
    double Td_PID = m_Pu / 8.0;
    
    // Выбор PID конфигурации
    result.kp = kp_PID;
    result.Ti = Ti_PID;
    result.Td = Td_PID;
    
    // Преобразование к параллельной форме
    result.ki = result.kp / result.Ti;
    result.kd = result.kp * result.Td;
    
    // Оценка качества
    result.expectedOvershoot = 25.0;
    result.expectedSettlingTime = 2.0 * m_Pu;
    
    result.recommendations = QString("Ku=%1, Pu=%2").arg(m_Ku).arg(m_Pu);
    
    return result;
}
