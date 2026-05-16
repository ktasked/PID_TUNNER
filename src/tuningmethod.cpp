#include "tuningmethod.h"
#include <QtMath>
#include <QDebug>

TuningMethod::TuningMethod(QObject *parent)
    : QObject(parent)
{
}

TuningMethod::TuningResult TuningMethod::tuneFromData(const QVector<double>& inputs,
                                                       const QVector<double>& outputs,
                                                       double sampleTime)
{
    // Базовая реализация - требует переопределения
    TuningResult result;
    result.isValid = false;
    result.recommendations = "Method does not support data-based tuning";
    return result;
}

bool TuningMethod::isApplicable(const ProcessModel::ModelParameters& params) const
{
    // Базовая проверка - параметры должны быть положительными
    return params.gain > 0 && 
           params.timeConstant1 > 0 && 
           params.deadTime >= 0;
}

double TuningMethod::calculateGainMargin(double K, double T, double L) const
{
    // Упрощенный расчет запаса по усилению для FOPDT модели
    if (T <= 0 || L < 0)
        return 0.0;
    
    // Критическая частота
    double omega_c = M_PI / (2 * L + 0.1);
    
    // Запас по усилению
    double gainMargin = 1.0 / (K * qSqrt(1 + qPow(omega_c * T, 2)));
    
    return gainMargin;
}

double TuningMethod::calculatePhaseMargin(double K, double T, double L) const
{
    // Упрощенный расчет запаса по фазе для FOPDT модели
    if (T <= 0 || L < 0)
        return 0.0;
    
    // Частота единичного усиления
    double omega_g = 1.0 / T;
    
    // Запас по фазе (в градусах)
    double phaseMargin = 90.0 - qAtan(omega_g * T) * 180.0 / M_PI - omega_g * L * 180.0 / M_PI;
    
    return qMax(0.0, phaseMargin);
}

void TuningMethod::validateResult(TuningResult& result) const
{
    // Проверка и валидация результатов настройки
    
    // Коэффициенты должны быть неотрицательными
    result.kp = qMax(0.0, result.kp);
    result.ki = qMax(0.0, result.ki);
    result.kd = qMax(0.0, result.kd);
    
    // Ti и Td должны быть положительными если используются
    if (result.Ti <= 0 && !qFuzzyIsNull(result.ki)) {
        result.Ti = result.kp / result.ki;
    }
    
    if (result.Td <= 0 && !qFuzzyIsNull(result.kd)) {
        result.Td = result.kd / result.kp;
    }
    
    // Фильтр производной должен быть разумным
    if (result.filterTimeConstant < 0) {
        result.filterTimeConstant = 0.1 * result.Td;
    }
    
    // Вес уставки в диапазоне [0, 1]
    result.setpointWeight = qBound(0.0, result.setpointWeight, 1.0);
    
    // Проверка на разумность коэффициентов
    if (result.kp > 1000 || result.ki > 1000 || result.kd > 1000) {
        result.recommendations += "\nWarning: Very high gains detected. Check process parameters.";
    }
    
    // Оценка робастности
    result.robustnessMargin = calculatePhaseMargin(result.kp, result.Ti, result.Td);
    result.isValid = true;
}

QVariantMap TuningMethod::exportResult(const TuningResult& result) const
{
    QVariantMap data;
    data["kp"] = result.kp;
    data["ki"] = result.ki;
    data["kd"] = result.kd;
    data["Ti"] = result.Ti;
    data["Td"] = result.Td;
    data["filterTimeConstant"] = result.filterTimeConstant;
    data["setpointWeight"] = result.setpointWeight;
    data["expectedOvershoot"] = result.expectedOvershoot;
    data["expectedSettlingTime"] = result.expectedSettlingTime;
    data["robustnessMargin"] = result.robustnessMargin;
    data["recommendations"] = result.recommendations;
    data["isValid"] = result.isValid;
    return data;
}

TuningMethod::TuningResult TuningMethod::importResult(const QVariantMap& data) const
{
    TuningResult result;
    if (data.contains("kp")) result.kp = data["kp"].toDouble();
    if (data.contains("ki")) result.ki = data["ki"].toDouble();
    if (data.contains("kd")) result.kd = data["kd"].toDouble();
    if (data.contains("Ti")) result.Ti = data["Ti"].toDouble();
    if (data.contains("Td")) result.Td = data["Td"].toDouble();
    if (data.contains("filterTimeConstant")) result.filterTimeConstant = data["filterTimeConstant"].toDouble();
    if (data.contains("setpointWeight")) result.setpointWeight = data["setpointWeight"].toDouble();
    if (data.contains("expectedOvershoot")) result.expectedOvershoot = data["expectedOvershoot"].toDouble();
    if (data.contains("expectedSettlingTime")) result.expectedSettlingTime = data["expectedSettlingTime"].toDouble();
    if (data.contains("robustnessMargin")) result.robustnessMargin = data["robustnessMargin"].toDouble();
    if (data.contains("recommendations")) result.recommendations = data["recommendations"].toString();
    if (data.contains("isValid")) result.isValid = data["isValid"].toBool();
    return result;
}
