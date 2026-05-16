#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pidcontroller.h"
#include "processmodel.h"
#include "zeiglernichols.h"
#include "cohencoon.h"
#include "internalmodelcontrol.h"

#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pidController(std::make_unique<PIDController>())
    , m_processModel(std::make_unique<ProcessModel>())
    , m_simulationTimer(new QTimer(this))
    , m_simulationStep(0)
    , m_isSimulating(false)
{
    ui->setupUi(this);
    
    setupUI();
    setupCharts();
    setupConnections();
    loadDefaultSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Инициализация графиков
    m_processChart = new QChartView(ui->processChartView);
    m_controlChart = new QChartView(ui->controlChartView);
    
    ui->processChartView->setScene(m_processChart->scene());
    ui->controlChartView->setScene(m_controlChart->scene());
    
    // Обновление описания метода
    onMethodComboBox_currentIndexChanged(ui->cmbMethod->currentIndex());
}

void MainWindow::setupCharts()
{
    // График процесса
    QChart* processChart = new QChart();
    processChart->setTitle("Процесс и Уставка");
    processChart->setAnimationOptions(QChart::SeriesAnimations);
    
    m_setpointSeries = new QLineSeries();
    m_setpointSeries->setName("Уставка");
    m_setpointSeries->setColor(Qt::red);
    
    m_processValueSeries = new QLineSeries();
    m_processValueSeries->setName("Процесс");
    m_processValueSeries->setColor(Qt::blue);
    
    processChart->addSeries(m_setpointSeries);
    processChart->addSeries(m_processValueSeries);
    
    m_axisX = new QValueAxis();
    m_axisX->setTitleText("Время (с)");
    m_axisX->setRange(0, 50);
    
    m_axisY = new QValueAxis();
    m_axisY->setTitleText("Значение");
    m_axisY->setRange(0, 100);
    
    processChart->addAxis(m_axisX, Qt::AlignBottom);
    processChart->addAxis(m_axisY, Qt::AlignLeft);
    
    m_setpointSeries->attachAxis(m_axisX);
    m_setpointSeries->attachAxis(m_axisY);
    m_processValueSeries->attachAxis(m_axisX);
    m_processValueSeries->attachAxis(m_axisY);
    
    processChart->legend()->setVisible(true);
    processChart->legend()->setAlignment(Qt::AlignBottom);
    
    m_processChart->setChart(processChart);
    ui->processChartView->setChart(processChart);
    
    // График управления
    QChart* controlChart = new QChart();
    controlChart->setTitle("Управляющее Воздействие");
    controlChart->setAnimationOptions(QChart::SeriesAnimations);
    
    m_controllerOutputSeries = new QLineSeries();
    m_controllerOutputSeries->setName("Выход ПИД");
    m_controllerOutputSeries->setColor(Qt::green);
    
    controlChart->addSeries(m_controllerOutputSeries);
    
    QValueAxis* axisX2 = new QValueAxis();
    axisX2->setTitleText("Время (с)");
    axisX2->setRange(0, 50);
    
    QValueAxis* axisY2 = new QValueAxis();
    axisY2->setTitleText("Выход (%)");
    axisY2->setRange(0, 100);
    
    controlChart->addAxis(axisX2, Qt::AlignBottom);
    controlChart->addAxis(axisY2, Qt::AlignLeft);
    
    m_controllerOutputSeries->attachAxis(axisX2);
    m_controllerOutputSeries->attachAxis(axisY2);
    
    controlChart->legend()->setVisible(true);
    controlChart->legend()->setAlignment(Qt::AlignBottom);
    
    m_controlChart->setChart(controlChart);
    ui->controlChartView->setChart(controlChart);
}

void MainWindow::setupConnections()
{
    // Соединения кнопок
    connect(ui->btnTune, &QPushButton::clicked, this, &MainWindow::on_btnTune_clicked);
    connect(ui->btnSimulate, &QPushButton::clicked, this, &MainWindow::on_btnSimulate_clicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::on_btnReset_clicked);
    connect(ui->btnExport, &QPushButton::clicked, this, &MainWindow::on_btnExport_clicked);
    connect(ui->btnImport, &QPushButton::clicked, this, &MainWindow::on_btnImport_clicked);
    connect(ui->btnApplySettings, &QPushButton::clicked, this, &MainWindow::on_btnApplySettings_clicked);
    
    // Таймер симуляции
    connect(m_simulationTimer, &QTimer::timeout, this, &MainWindow::onSimulationTimer);
    
    // Переключение методов
    connect(ui->cmbMethod, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &MainWindow::onMethodComboBox_currentIndexChanged);
    
    // Переключение типа процесса
    connect(ui->cmbProcessType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onProcessTypeComboBox_currentIndexChanged);
    
    // Применение настроек в реальном времени
    connect(ui->spinSetpoint, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [this](double value) {
        if (m_pidController) {
            m_pidController->setSetpoint(value);
        }
    });
    
    connect(ui->spinGain, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [this]() { updateProcessParams(); });
    connect(ui->spinTimeConstant, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [this]() { updateProcessParams(); });
    connect(ui->spinDeadTime, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, [this]() { updateProcessParams(); });
}

void MainWindow::loadDefaultSettings()
{
    // Установка значений по умолчанию
    m_settings.setpoint = 50.0;
    m_settings.sampleTime = 0.1;
    m_settings.simulationSteps = 500;
    
    ui->spinSetpoint->setValue(m_settings.setpoint);
    ui->spinSampleTime->setValue(m_settings.sampleTime);
    ui->spinSimSteps->setValue(m_settings.simulationSteps);
    
    // Настройка PID контроллера
    m_pidController->setSetpoint(m_settings.setpoint);
    m_pidController->setOutputLimits(
        ui->spinOutputMin->value(),
        ui->spinOutputMax->value()
    );
    m_pidController->setSampleTime(m_settings.sampleTime);
}

void MainWindow::on_btnTune_clicked()
{
    // Получение параметров процесса
    ProcessModel::ModelParameters params;
    params.gain = ui->spinGain->value();
    params.timeConstant1 = ui->spinTimeConstant->value();
    params.deadTime = ui->spinDeadTime->value();
    params.disturbance = ui->spinDisturbance->value();
    params.noiseLevel = ui->spinNoise->value();
    
    // Выбор метода настройки
    TuningMethod* method = nullptr;
    int methodIndex = ui->cmbMethod->currentIndex();
    
    switch (methodIndex) {
    case 0: // Ziegler-Nichols
        method = new ZieglerNichols(ZieglerNichols::Variant::ProcessReactionCurve);
        break;
    case 1: // Cohen-Coon
        method = new CohenCoon();
        break;
    case 2: // IMC
        method = new InternalModelControl();
        break;
    }
    
    if (!method) {
        QMessageBox::warning(this, "Ошибка", "Выберите метод настройки");
        return;
    }
    
    // Проверка применимости
    if (!method->isApplicable(params)) {
        QMessageBox::warning(this, "Предупреждение", 
            "Выбранный метод может быть неприменим для текущих параметров процесса.");
    }
    
    // Выполнение настройки
    TuningMethod::TuningResult result = method->tune(params);
    
    if (result.isValid) {
        // Отображение результатов
        ui->editKp->setText(QString::number(result.kp, 'f', 4));
        ui->editKi->setText(QString::number(result.ki, 'f', 4));
        ui->editKd->setText(QString::number(result.kd, 'f', 4));
        ui->editTi->setText(QString::number(result.Ti, 'f', 2));
        ui->editTd->setText(QString::number(result.Td, 'f', 2));
        ui->editOvershoot->setText(QString::number(result.expectedOvershoot, 'f', 1) + " %");
        ui->editSettlingTime->setText(QString::number(result.expectedSettlingTime, 'f', 2) + " с");
        ui->txtRecommendations->setText(result.recommendations);
        
        QMessageBox::information(this, "Настройка завершена", 
            "Параметры ПИД-регулятора успешно рассчитаны!");
    } else {
        QMessageBox::warning(this, "Ошибка настройки", 
            "Не удалось рассчитать параметры: " + result.recommendations);
    }
    
    delete method;
}

void MainWindow::on_btnSimulate_clicked()
{
    if (m_isSimulating) {
        // Остановка симуляции
        m_simulationTimer->stop();
        m_isSimulating = false;
        ui->btnSimulate->setText("▶️ Запустить Симуляцию");
        ui->lblStatus->setText("Статус: Остановлено");
        return;
    }
    
    // Проверка наличия настроенных параметров
    if (ui->editKp->text().isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", 
            "Сначала выполните настройку ПИД-регулятора!");
        return;
    }
    
    // Применение настроек
    on_btnApplySettings_clicked();
    
    // Сброс данных
    m_processData.clear();
    m_setpointData.clear();
    m_outputData.clear();
    m_simulationStep = 0;
    
    // Сброс моделей
    m_processModel->reset();
    m_pidController->reset();
    
    // Настройка симуляции
    m_settings.simulationSteps = ui->spinSimSteps->value();
    m_settings.sampleTime = ui->spinSampleTime->value();
    m_pidController->setSampleTime(m_settings.sampleTime);
    
    // Запуск таймера
    m_simulationTimer->start(static_cast<int>(m_settings.sampleTime * 1000));
    m_isSimulating = true;
    
    ui->btnSimulate->setText("⏹️ Остановить");
    ui->lblStatus->setText("Статус: Симуляция запущена...");
}

void MainWindow::onSimulationTimer()
{
    if (!m_isSimulating || m_simulationStep >= m_settings.simulationSteps) {
        m_simulationTimer->stop();
        m_isSimulating = false;
        ui->btnSimulate->setText("▶️ Запустить Симуляцию");
        ui->lblStatus->setText("Статус: Симуляция завершена");
        return;
    }
    
    double currentTime = m_simulationStep * m_settings.sampleTime;
    
    // Шаг процесса
    double processValue = m_processModel->step(m_settings.sampleTime);
    
    // Шаг ПИД-регулятора
    double output = m_pidController->compute(processValue, currentTime);
    
    // Установка выхода ПИД на вход процесса
    m_processModel->setControlInput(output);
    
    // Сохранение данных
    m_processData.append(QPointF(currentTime, processValue));
    m_setpointData.append(QPointF(currentTime, m_pidController->getSetpoint()));
    m_outputData.append(QPointF(currentTime, output));
    
    // Обновление графиков
    m_processValueSeries->replace(m_processData);
    m_setpointSeries->replace(m_setpointData);
    m_controllerOutputSeries->replace(m_outputData);
    
    // Прокрутка осей
    double maxTime = currentTime;
    double minTime = qMax(0.0, maxTime - 50.0);
    m_axisX->setRange(minTime, maxTime);
    
    // Обновление статуса
    ui->lblStatus->setText(QString("Статус: Шаг %1 / %2").arg(m_simulationStep).arg(m_settings.simulationSteps));
    
    m_simulationStep++;
}

void MainWindow::on_btnReset_clicked()
{
    m_simulationTimer->stop();
    m_isSimulating = false;
    
    m_processData.clear();
    m_setpointData.clear();
    m_outputData.clear();
    m_simulationStep = 0;
    
    m_processModel->reset();
    m_pidController->reset();
    
    m_processValueSeries->clear();
    m_setpointSeries->clear();
    m_controllerOutputSeries->clear();
    
    ui->lblStatus->setText("Статус: Готов");
    ui->btnSimulate->setText("▶️ Запустить Симуляцию");
}

void MainWindow::on_btnApplySettings_clicked()
{
    // Применение настроек из UI к PID контроллеру
    bool ok = true;
    
    double kp = ui->editKp->text().toDouble(&ok);
    if (ok) m_pidController->setKp(kp);
    
    double ki = ui->editKi->text().toDouble(&ok);
    if (ok) m_pidController->setKi(ki);
    
    double kd = ui->editKd->text().toDouble(&ok);
    if (ok) m_pidController->setKd(kd);
    
    m_pidController->setOutputLimits(
        ui->spinOutputMin->value(),
        ui->spinOutputMax->value()
    );
    
    m_pidController->setSetpoint(ui->spinSetpoint->value());
    
    ui->lblStatus->setText("Статус: Настройки применены");
}

void MainWindow::on_btnExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Экспорт данных CSV", "", "CSV Files (*.csv);;All Files (*)");
    
    if (fileName.isEmpty())
        return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }
    
    QTextStream out(&file);
    out << "Time,Setpoint,ProcessValue,ControllerOutput\n";
    
    for (int i = 0; i < m_processData.size(); ++i) {
        double time = m_processData[i].x();
        double setpoint = (i < m_setpointData.size()) ? m_setpointData[i].y() : 0;
        double process = m_processData[i].y();
        double output = (i < m_outputData.size()) ? m_outputData[i].y() : 0;
        
        out << QString("%1,%2,%3,%4\n")
            .arg(time, 0, 'f', 3)
            .arg(setpoint, 0, 'f', 4)
            .arg(process, 0, 'f', 4)
            .arg(output, 0, 'f', 4);
    }
    
    file.close();
    QMessageBox::information(this, "Экспорт", "Данные успешно экспортированы!");
}

void MainWindow::on_btnImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Импорт конфигурации", "", "JSON Files (*.json);;All Files (*)");
    
    if (fileName.isEmpty())
        return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
        return;
    }
    
    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    
    if (doc.isNull()) {
        QMessageBox::critical(this, "Ошибка", "Неверный формат JSON");
        return;
    }
    
    QJsonObject obj = doc.object();
    
    // Загрузка параметров
    if (obj.contains("gain")) ui->spinGain->setValue(obj["gain"].toDouble());
    if (obj.contains("timeConstant")) ui->spinTimeConstant->setValue(obj["timeConstant"].toDouble());
    if (obj.contains("deadTime")) ui->spinDeadTime->setValue(obj["deadTime"].toDouble());
    if (obj.contains("kp")) ui->editKp->setText(QString::number(obj["kp"].toDouble(), 'f', 4));
    if (obj.contains("ki")) ui->editKi->setText(QString::number(obj["ki"].toDouble(), 'f', 4));
    if (obj.contains("kd")) ui->editKd->setText(QString::number(obj["kd"].toDouble(), 'f', 4));
    
    updateProcessParams();
    
    QMessageBox::information(this, "Импорт", "Конфигурация успешно загружена!");
}

void MainWindow::onMethodComboBox_currentIndexChanged(int index)
{
    QString description;
    switch (index) {
    case 0:
        description = "Ziegler-Nichols: Классический метод (1942). Быстрый отклик, ~25% перерегулирование.";
        break;
    case 1:
        description = "Cohen-Coon: Улучшен для процессов с большой задержкой. Меньшее перерегулирование.";
        break;
    case 2:
        description = "IMC: Современный метод. Оптимальный баланс быстродействия и робастности.";
        break;
    }
    ui->txtMethodDescription->setText(description);
}

void MainWindow::onProcessTypeComboBox_currentIndexChanged(int index)
{
    ProcessModel::ProcessType type;
    switch (index) {
    case 0: type = ProcessModel::ProcessType::FOPDT; break;
    case 1: type = ProcessModel::ProcessType::FirstOrder; break;
    case 2: type = ProcessModel::ProcessType::SecondOrder; break;
    case 3: type = ProcessModel::ProcessType::Integrating; break;
    case 4: type = ProcessModel::ProcessType::HeatExchanger; break;
    case 5: type = ProcessModel::ProcessType::Pipeline; break;
    default: type = ProcessModel::ProcessType::FOPDT;
    }
    
    m_processModel->setProcessType(type);
}

void MainWindow::updatePIDDisplay()
{
    ui->editKp->setText(QString::number(m_pidController->getKp(), 'f', 4));
    ui->editKi->setText(QString::number(m_pidController->getKi(), 'f', 4));
    ui->editKd->setText(QString::number(m_pidController->getKd(), 'f', 4));
}

void MainWindow::updateProcessParams()
{
    ProcessModel::ModelParameters params;
    params.gain = ui->spinGain->value();
    params.timeConstant1 = ui->spinTimeConstant->value();
    params.deadTime = ui->spinDeadTime->value();
    params.disturbance = ui->spinDisturbance->value();
    params.noiseLevel = ui->spinNoise->value();
    
    m_processModel->setParameters(params);
}

void MainWindow::updateRecommendations()
{
    // Интеллектуальная система рекомендаций
    double ratio = ui->spinDeadTime->value() / ui->spinTimeConstant->value();
    
    QString recommendations;
    
    if (ratio > 0.6) {
        recommendations = "⚠️ Большое время задержки. Рекомендуется метод Cohen-Coon или IMC.\n";
    } else if (ratio < 0.1) {
        recommendations = "✅ Малое время задержки. Подойдет любой метод настройки.\n";
    } else {
        recommendations = "✅ Умеренное время задержки. Все методы применимы.\n";
    }
    
    if (ui->spinNoise->value() > 0.1) {
        recommendations += "⚠️ Высокий уровень шума. Рекомендуется фильтрация производной.\n";
    }
    
    ui->txtRecommendations->setText(recommendations);
}

void MainWindow::updateStatus()
{
    // Обновление статусной строки
    static QString lastStatus;
    QString currentStatus = ui->lblStatus->text();
    
    if (currentStatus != lastStatus) {
        statusBar()->showMessage(currentStatus, 5000);
        lastStatus = currentStatus;
    }
}

bool MainWindow::validateInputs()
{
    if (ui->spinGain->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Коэффициент усиления должен быть положительным");
        return false;
    }
    
    if (ui->spinTimeConstant->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Постоянная времени должна быть положительной");
        return false;
    }
    
    if (ui->spinDeadTime->value() < 0) {
        QMessageBox::warning(this, "Ошибка", "Время задержки не может быть отрицательным");
        return false;
    }
    
    return true;
}

void MainWindow::saveConfiguration()
{
    // Сохранение конфигурации в файл
    QJsonObject config;
    config["gain"] = ui->spinGain->value();
    config["timeConstant"] = ui->spinTimeConstant->value();
    config["deadTime"] = ui->spinDeadTime->value();
    config["kp"] = ui->editKp->text().toDouble();
    config["ki"] = ui->editKi->text().toDouble();
    config["kd"] = ui->editKd->text().toDouble();
    config["setpoint"] = ui->spinSetpoint->value();
    
    QJsonDocument doc(config);
    
    QString fileName = QFileDialog::getSaveFileName(this,
        "Сохранить конфигурацию", "", "JSON Files (*.json)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
        }
    }
}

void MainWindow::loadConfiguration()
{
    // Загрузка конфигурации (вызывается из on_btnImport_clicked)
}
