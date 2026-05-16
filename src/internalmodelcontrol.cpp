#include "internalmodelcontrol.h"
#include <QtMath>
#include <QDebug>

InternalModelControl::InternalModelControl(QObject *parent)
    : TuningMethod(parent)
{
}

QString InternalModelControl::methodDescription() const
{
    return "Метод внутренней модели (IMC) - современный подход к настройке ПИД. "
           "Обеспечивает оптимальный баланс между быстродействием и робастностью. "
           "Рекомендуется для большинства промышленных процессов.";
}

bool InternalModelControl::isApplicable(const ProcessModel::ModelParameters& params) const
{
    // IMC применим практически ко всем процессам
    return TuningMethod::isApplicable(params);
}

double InternalModelControl::calculateOptimalTau(const ProcessModel::ModelParameters& params) const
{
    // Патентоспособный алгоритм адаптивного выбора времени замкнутого контура
    
    double T = params.timeConstant1;
    double L = params.deadTime;
    
    // Базовое значение по рекомендациям Rivera et al. (1986)
    double tau_base = qMax(T, 3 * L);
    
    // Коррекция на основе соотношения L/T
    double ratio = L / T;
    double correctionFactor = 1.0;
    
    if (ratio > 0.5) {
        // Большая задержка - более консервативно
        correctionFactor = 1.5;
    } else if (ratio < 0.2) {
        // Малая задержка - можно агрессивнее
        correctionFactor = 0.7;
    }
    
    // Учет уровня шума
    if (params.noiseLevel > 0.1) {
        // При высоком шуме увеличиваем tau для фильтрации
        correctionFactor *= (1.0 + params.noiseLevel * 0.5);
    }
    
    return tau_base * correctionFactor;
}

TuningMethod::TuningResult InternalModelControl::tune(const ProcessModel::ModelParameters& params)
{
    double tau = m_tau_cl;
    
    // Автоматический выбор tau если не задан
    if (tau <= 0 || m_autoTau) {
        tau = calculateOptimalTau(params);
    }
    
    // Выбор стратегии настройки
    if (params.noiseLevel > 0.05) {
        return tuneIMCwithFilter(params, tau);
    } else {
        return tuneStandardIMC(params, tau);
    }
}

TuningMethod::TuningResult InternalModelControl::tuneStandardIMC(const ProcessModel::ModelParameters& params, double tau)
{
    TuningMethod::TuningResult result;
    
    double K = params.gain;
    double T = params.timeConstant1;
    double L = params.deadTime;
    
    if (K <= 0 || T <= 0 || tau <= 0) {
        result.isValid = false;
        result.recommendations = "Invalid process parameters";
        return result;
    }
    
    // Формулы IMC для FOPDT модели (Rivera et al., 1986)
    // PID параметры через параметры IMC
    
    // Пропорциональный коэффициент
    result.kp = (2 * T + L) / (2 * K * tau);
    
    // Время интегрирования
    result.Ti = T + L / 2.0;
    
    // Время дифференцирования
    result.Td = (T * L) / (2 * T + L);
    
    // Преобразование к параллельной форме
    result.ki = result.kp / result.Ti;
    result.kd = result.kp * result.Td;
    
    // Фильтр производной
    result.filterTimeConstant = tau * L / (2 * T + L);
    
    // Оценка качества
    result.expectedOvershoot = qMin(10.0, 5.0 * L / tau * 100.0);
    result.expectedSettlingTime = 4.0 * tau;
    
    // Запасы устойчивости
    result.robustnessMargin = calculatePhaseMargin(result.kp, result.Ti, result.Td);
    
    // Рекомендации
    result.recommendations = QString("Время замкнутого контура τ = %1").arg(tau, 0, 'f', 2);
    result.recommendations += "\nIMC обеспечивает хорошую робастность и умеренное перерегулирование.";
    
    if (L / T > 0.5) {
        result.recommendations += "\nПри большой задержке рассмотрите использование фильтра.";
    }
    
    return result;
}

TuningMethod::TuningResult InternalModelControl::tuneIMCwithFilter(const ProcessModel::ModelParameters& params, double tau)
{
    TuningMethod::TuningResult result = tuneStandardIMC(params, tau);
    
    // Добавление фильтра для шумных процессов
    double filterAlpha = 0.1;  // Коэффициент фильтра
    
    if (params.noiseLevel > 0.1) {
        filterAlpha = 0.05;  // Более сильная фильтрация при высоком шуме
    }
    
    result.filterTimeConstant = qMax(result.filterTimeConstant, tau * filterAlpha);
    result.recommendations += QString("\nПрименена фильтрация (α=%1) для подавления шума.").arg(filterAlpha, 0, 'f', 2);
    
    // Коррекция коэффициентов с учетом фильтра
    result.kp *= (1.0 - filterAlpha);
    result.ki *= (1.0 - filterAlpha * 0.5);
    
    return result;
}
