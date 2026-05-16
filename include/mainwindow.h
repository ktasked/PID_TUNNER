#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Forward declarations для QtCharts - в пространстве имен QtCharts
namespace QtCharts {
    class QChart;
    class QChartView;
    class QLineSeries;
    class QValueAxis;
}

class PIDController;  // Forward declaration
class ProcessModel;   // Forward declaration
class TuningMethod;   // Forward declaration

/**
 * @brief Главное окно приложения автоматической настройки ПИД-регулятора
 * 
 * Предоставляет полный интерфейс для:
 * - Ввода параметров процесса
 * - Выбора метода настройки
 * - Симуляции и визуализации
 * - Экспорта результатов
 * 
 * @note Патентоспособные особенности UI:
 * - Интеллектуальная система рекомендаций
 * - Адаптивная визуализация данных
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    // Обработчики кнопок
    void on_btnTune_clicked();
    void on_btnSimulate_clicked();
    void on_btnReset_clicked();
    void on_btnExport_clicked();
    void on_btnImport_clicked();
    void on_btnApplySettings_clicked();
    
    // Обработчики изменений
    void onProcessValueChanged(double value);
    void onSetpointChanged(double value);
    void onControllerOutputChanged(double output);
    
    // Таймер симуляции
    void onSimulationTimer();
    
    // Переключение вкладок и методов
    void onMethodComboBox_currentIndexChanged(int index);
    void onProcessTypeComboBox_currentIndexChanged(int index);
    
private:
    // Инициализация
    void setupUI();
    void setupCharts();
    void setupConnections();
    void loadDefaultSettings();
    
    // Обновление интерфейса
    void updatePIDDisplay();
    void updateProcessParams();
    void updateRecommendations();
    void updateStatus();
    
    // Валидация
    bool validateInputs();
    
    // Сохранение/загрузка
    void saveConfiguration();
    void loadConfiguration();
    
    Ui::MainWindow *ui;
    
    // Основные компоненты
    std::unique_ptr<PIDController> m_pidController;
    std::unique_ptr<ProcessModel> m_processModel;
    
    // Компоненты графиков
    QtCharts::QChart *m_processChart;
    QtCharts::QChart *m_controlChart;
    QtCharts::QChartView *m_processChartView;
    QtCharts::QChartView *m_controlChartView;
    QtCharts::QLineSeries *m_processValueSeries;
    QtCharts::QLineSeries *m_setpointSeries;
    QtCharts::QLineSeries *m_controllerOutputSeries;
    QtCharts::QValueAxis *m_axisX;
    QtCharts::QValueAxis *m_axisY;
    
    // Данные для графиков
    QVector<QPointF> m_processData;
    QVector<QPointF> m_setpointData;
    QVector<QPointF> m_outputData;
    
    // Таймер симуляции
    QTimer *m_simulationTimer;
    int m_simulationStep;
    bool m_isSimulating;
    
    // Настройки
    struct AppSettings {
        double setpoint = 50.0;
        double sampleTime = 0.1;
        int simulationSteps = 500;
        bool realTimeMode = false;
        QString lastExportPath;
    } m_settings;
};

#endif // MAINWINDOW_H
