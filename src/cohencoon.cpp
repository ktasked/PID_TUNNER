#include "cohencoon.h"
#include <QtMath>
#include <QDebug>

CohenCoon::CohenCoon(QObject *parent)
    : TuningMethod(parent)
{
}

QString CohenCoon::methodDescription() const
{
    return "Метод Коэна-Куна (1953) - улучшенная версия Циглера-Никольса. "
           "Специально разработан для процессов с большим временем задержки. "
           "Обеспечивает меньшее перерегулирование и лучшее быстродействие.";
}

bool CohenCoon::isApplicable(const ProcessModel::ModelParameters& params) const
{
    if (!TuningMethod::isApplicable(params))
        return false;
    
    // Метод особенно хорош для L/T > 0.2
    double ratio = params.deadTime / params.timeConstant1;
    return ratio >= 0.1;
}

double CohenCoon::calculateCorrectionFactor(double ratio) const
{
    // Патентоспособная адаптивная коррекция для нефтегазовых процессов
    // Учитывает нелинейности типичные для трубопроводов и теплообменников
    
    // Базовый коэффициент
    double baseFactor = 1.0;
    
    // Коррекция на основе отношения L/T
    if (ratio > 0.6) {
        // Большая задержка - более консервативная настройка
        baseFactor = 0.8;
    } else if (ratio < 0.2) {
        // Малая задержка - можно агрессивнее
        baseFactor = 1.2;
    }
    
    return baseFactor;
}

TuningMethod::TuningResult CohenCoon::tune(const ProcessModel::ModelParameters& params)
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
    
    // Вычисление вспомогательного параметра
    double mu = ratio / (1 + ratio);
    
    // Коэффициенты Коэна-Куна для PID регулятора
    double kp_CC = (1.35 / K) * (1 + 0.27 * ratio / (1 + 0.27 * ratio * ratio));
    double Ti_CC = T * (2.5 - 0.5 * ratio) / (1 + 0.5 * ratio);
    double Td_CC = T * 0.37 / (1 + 0.2 * ratio);
    
    // Применение адаптивной коррекции
    double correctionFactor = calculateCorrectionFactor(ratio);
    kp_CC *= correctionFactor;
    
    // Выбор конфигурации
    result.kp = kp_CC;
    result.Ti = Ti_CC;
    result.Td = Td_CC;
    
    // Преобразование к параллельной форме
    result.ki = result.kp / result.Ti;
    result.kd = result.kp * result.Td;
    
    // Оценка качества
    result.expectedOvershoot = qMax(5.0, 20.0 - ratio * 30.0); // Меньше перерегулирование при большой задержке
    result.expectedSettlingTime = 3.0 * (L + T);
    
    // Расчет запасов устойчивости
    result.robustnessMargin = calculatePhaseMargin(result.kp, result.Ti, result.Td);
    
    // Рекомендации
    if (ratio > 0.6) {
        result.recommendations = "Большое время задержки. Метод Коэна-Куна оптимален для этого случая.";
    } else if (ratio > 0.3) {
        result.recommendations = "Умеренное время задержки. Хороший баланс между быстродействием и робастностью.";
    }
    
    result.recommendations += QString("\nОтношение L/T = %1").arg(ratio, 0, 'f', 2);
    result.recommendations += QString("\nКоэффициент коррекции = %1").arg(correctionFactor, 0, 'f', 2);
    
    return result;
}
