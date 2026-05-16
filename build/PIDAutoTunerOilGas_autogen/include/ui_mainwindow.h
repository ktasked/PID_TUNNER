/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblTitle;
    QTabWidget *tabWidget;
    QWidget *tabProcess;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *lblProcessType;
    QComboBox *cmbProcessType;
    QLabel *lblGain;
    QDoubleSpinBox *spinGain;
    QLabel *lblTimeConstant;
    QDoubleSpinBox *spinTimeConstant;
    QLabel *lblDeadTime;
    QDoubleSpinBox *spinDeadTime;
    QLabel *lblDisturbance;
    QDoubleSpinBox *spinDisturbance;
    QLabel *lblNoise;
    QDoubleSpinBox *spinNoise;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *lblSetpoint;
    QDoubleSpinBox *spinSetpoint;
    QLabel *lblSampleTime;
    QDoubleSpinBox *spinSampleTime;
    QLabel *lblSimSteps;
    QSpinBox *spinSimSteps;
    QLabel *lblOutputMin;
    QDoubleSpinBox *spinOutputMin;
    QLabel *lblOutputMax;
    QDoubleSpinBox *spinOutputMax;
    QWidget *tabTuning;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblMethod;
    QComboBox *cmbMethod;
    QTextBrowser *txtMethodDescription;
    QSpacerItem *verticalSpacer;
    QPushButton *btnTune;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_3;
    QLabel *lblKp;
    QLineEdit *editKp;
    QLabel *lblKi;
    QLineEdit *editKi;
    QLabel *lblKd;
    QLineEdit *editKd;
    QLabel *lblTi;
    QLineEdit *editTi;
    QLabel *lblTd;
    QLineEdit *editTd;
    QLabel *lblOvershoot;
    QLineEdit *editOvershoot;
    QLabel *lblSettlingTime;
    QLineEdit *editSettlingTime;
    QTextEdit *txtRecommendations;
    QPushButton *btnApplySettings;
    QWidget *tabSimulation;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnSimulate;
    QPushButton *btnReset;
    QLabel *lblStatus;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *processChartView;
    QGraphicsView *controlChartView;
    QWidget *tabExport;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnExport;
    QPushButton *btnExportJSON;
    QPushButton *btnExportReport;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnImport;
    QPushButton *btnImportData;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 900);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"QMainWindow {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 8px;\n"
"    margin-top: 12px;\n"
"    padding-top: 10px;\n"
"    background-color: white;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    left: 15px;\n"
"    padding: 0 8px;\n"
"    color: #2c3e50;\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"    min-width: 100px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1abc9c;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #bdc3c7;\n"
"}\n"
"\n"
"QLineEdit, QDoubleSpinBox, QSpinBox {\n"
"    border: 2px solid #bdc3c7;\n"
"    border-r"
                        "adius: 4px;\n"
"    padding: 5px;\n"
"    background-color: white;\n"
"}\n"
"\n"
"QLineEdit:focus, QDoubleSpinBox:focus, QSpinBox:focus {\n"
"    border-color: #3498db;\n"
"}\n"
"\n"
"QComboBox {\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"    background-color: white;\n"
"    min-width: 150px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 20px;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #ecf0f1;\n"
"    color: #2c3e50;\n"
"    padding: 8px 16px;\n"
"    border: 2px solid #bdc3c7;\n"
"    border-bottom: none;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: white;\n"
"    border-color: #3498db;\n"
"    border-bottom: 2px solid white;\n"
"}\n"
"\n"
"QProgressBar {\n"
"    border: 2px solid #bdc3"
                        "c7;\n"
"    border-radius: 4px;\n"
"    text-align: center;\n"
"    background-color: #ecf0f1;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #3498db;\n"
"}\n"
"\n"
"QTextEdit {\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    font-family: 'Consolas', monospace;\n"
"}\n"
"   "));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        lblTitle = new QLabel(centralwidget);
        lblTitle->setObjectName("lblTitle");
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        lblTitle->setFont(font);
        lblTitle->setAlignment(Qt::AlignCenter);
        lblTitle->setStyleSheet(QString::fromUtf8("color: #2c3e50; background-color: #3498db; padding: 10px; border-radius: 8px;"));

        verticalLayout->addWidget(lblTitle);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabProcess = new QWidget();
        tabProcess->setObjectName("tabProcess");
        horizontalLayout_2 = new QHBoxLayout(tabProcess);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        groupBox = new QGroupBox(tabProcess);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        lblProcessType = new QLabel(groupBox);
        lblProcessType->setObjectName("lblProcessType");

        formLayout->setWidget(0, QFormLayout::LabelRole, lblProcessType);

        cmbProcessType = new QComboBox(groupBox);
        cmbProcessType->addItem(QString());
        cmbProcessType->addItem(QString());
        cmbProcessType->addItem(QString());
        cmbProcessType->addItem(QString());
        cmbProcessType->addItem(QString());
        cmbProcessType->addItem(QString());
        cmbProcessType->setObjectName("cmbProcessType");

        formLayout->setWidget(0, QFormLayout::FieldRole, cmbProcessType);

        lblGain = new QLabel(groupBox);
        lblGain->setObjectName("lblGain");

        formLayout->setWidget(1, QFormLayout::LabelRole, lblGain);

        spinGain = new QDoubleSpinBox(groupBox);
        spinGain->setObjectName("spinGain");
        spinGain->setDecimals(3);
        spinGain->setMinimum(0.001000000000000);
        spinGain->setMaximum(1000.000000000000000);
        spinGain->setValue(1.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinGain);

        lblTimeConstant = new QLabel(groupBox);
        lblTimeConstant->setObjectName("lblTimeConstant");

        formLayout->setWidget(2, QFormLayout::LabelRole, lblTimeConstant);

        spinTimeConstant = new QDoubleSpinBox(groupBox);
        spinTimeConstant->setObjectName("spinTimeConstant");
        spinTimeConstant->setDecimals(2);
        spinTimeConstant->setMinimum(0.010000000000000);
        spinTimeConstant->setMaximum(1000.000000000000000);
        spinTimeConstant->setValue(10.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinTimeConstant);

        lblDeadTime = new QLabel(groupBox);
        lblDeadTime->setObjectName("lblDeadTime");

        formLayout->setWidget(3, QFormLayout::LabelRole, lblDeadTime);

        spinDeadTime = new QDoubleSpinBox(groupBox);
        spinDeadTime->setObjectName("spinDeadTime");
        spinDeadTime->setDecimals(2);
        spinDeadTime->setMinimum(0.000000000000000);
        spinDeadTime->setMaximum(500.000000000000000);
        spinDeadTime->setValue(2.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, spinDeadTime);

        lblDisturbance = new QLabel(groupBox);
        lblDisturbance->setObjectName("lblDisturbance");

        formLayout->setWidget(4, QFormLayout::LabelRole, lblDisturbance);

        spinDisturbance = new QDoubleSpinBox(groupBox);
        spinDisturbance->setObjectName("spinDisturbance");
        spinDisturbance->setDecimals(2);
        spinDisturbance->setMinimum(-100.000000000000000);
        spinDisturbance->setMaximum(100.000000000000000);
        spinDisturbance->setValue(0.000000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, spinDisturbance);

        lblNoise = new QLabel(groupBox);
        lblNoise->setObjectName("lblNoise");

        formLayout->setWidget(5, QFormLayout::LabelRole, lblNoise);

        spinNoise = new QDoubleSpinBox(groupBox);
        spinNoise->setObjectName("spinNoise");
        spinNoise->setDecimals(3);
        spinNoise->setMinimum(0.000000000000000);
        spinNoise->setMaximum(10.000000000000000);
        spinNoise->setSingleStep(0.010000000000000);
        spinNoise->setValue(0.000000000000000);

        formLayout->setWidget(5, QFormLayout::FieldRole, spinNoise);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tabProcess);
        groupBox_2->setObjectName("groupBox_2");
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName("formLayout_2");
        lblSetpoint = new QLabel(groupBox_2);
        lblSetpoint->setObjectName("lblSetpoint");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lblSetpoint);

        spinSetpoint = new QDoubleSpinBox(groupBox_2);
        spinSetpoint->setObjectName("spinSetpoint");
        spinSetpoint->setDecimals(2);
        spinSetpoint->setMinimum(-1000.000000000000000);
        spinSetpoint->setMaximum(1000.000000000000000);
        spinSetpoint->setValue(50.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinSetpoint);

        lblSampleTime = new QLabel(groupBox_2);
        lblSampleTime->setObjectName("lblSampleTime");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lblSampleTime);

        spinSampleTime = new QDoubleSpinBox(groupBox_2);
        spinSampleTime->setObjectName("spinSampleTime");
        spinSampleTime->setDecimals(3);
        spinSampleTime->setMinimum(0.001000000000000);
        spinSampleTime->setMaximum(10.000000000000000);
        spinSampleTime->setSingleStep(0.010000000000000);
        spinSampleTime->setValue(0.100000000000000);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, spinSampleTime);

        lblSimSteps = new QLabel(groupBox_2);
        lblSimSteps->setObjectName("lblSimSteps");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, lblSimSteps);

        spinSimSteps = new QSpinBox(groupBox_2);
        spinSimSteps->setObjectName("spinSimSteps");
        spinSimSteps->setMinimum(100);
        spinSimSteps->setMaximum(10000);
        spinSimSteps->setValue(500);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, spinSimSteps);

        lblOutputMin = new QLabel(groupBox_2);
        lblOutputMin->setObjectName("lblOutputMin");

        formLayout_2->setWidget(3, QFormLayout::LabelRole, lblOutputMin);

        spinOutputMin = new QDoubleSpinBox(groupBox_2);
        spinOutputMin->setObjectName("spinOutputMin");
        spinOutputMin->setMinimum(-100.000000000000000);
        spinOutputMin->setMaximum(100.000000000000000);
        spinOutputMin->setValue(0.000000000000000);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, spinOutputMin);

        lblOutputMax = new QLabel(groupBox_2);
        lblOutputMax->setObjectName("lblOutputMax");

        formLayout_2->setWidget(4, QFormLayout::LabelRole, lblOutputMax);

        spinOutputMax = new QDoubleSpinBox(groupBox_2);
        spinOutputMax->setObjectName("spinOutputMax");
        spinOutputMax->setMinimum(-100.000000000000000);
        spinOutputMax->setMaximum(200.000000000000000);
        spinOutputMax->setValue(100.000000000000000);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, spinOutputMax);


        horizontalLayout_2->addWidget(groupBox_2);

        tabWidget->addTab(tabProcess, QString());
        tabTuning = new QWidget();
        tabTuning->setObjectName("tabTuning");
        horizontalLayout_3 = new QHBoxLayout(tabTuning);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox_3 = new QGroupBox(tabTuning);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        lblMethod = new QLabel(groupBox_3);
        lblMethod->setObjectName("lblMethod");

        verticalLayout_2->addWidget(lblMethod);

        cmbMethod = new QComboBox(groupBox_3);
        cmbMethod->addItem(QString());
        cmbMethod->addItem(QString());
        cmbMethod->addItem(QString());
        cmbMethod->setObjectName("cmbMethod");

        verticalLayout_2->addWidget(cmbMethod);

        txtMethodDescription = new QTextBrowser(groupBox_3);
        txtMethodDescription->setObjectName("txtMethodDescription");
        txtMethodDescription->setMaximumSize(QSize(16777215, 100));

        verticalLayout_2->addWidget(txtMethodDescription);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        btnTune = new QPushButton(groupBox_3);
        btnTune->setObjectName("btnTune");

        verticalLayout_2->addWidget(btnTune);


        horizontalLayout_3->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tabTuning);
        groupBox_4->setObjectName("groupBox_4");
        formLayout_3 = new QFormLayout(groupBox_4);
        formLayout_3->setObjectName("formLayout_3");
        lblKp = new QLabel(groupBox_4);
        lblKp->setObjectName("lblKp");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, lblKp);

        editKp = new QLineEdit(groupBox_4);
        editKp->setObjectName("editKp");
        editKp->setReadOnly(true);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, editKp);

        lblKi = new QLabel(groupBox_4);
        lblKi->setObjectName("lblKi");

        formLayout_3->setWidget(1, QFormLayout::LabelRole, lblKi);

        editKi = new QLineEdit(groupBox_4);
        editKi->setObjectName("editKi");
        editKi->setReadOnly(true);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, editKi);

        lblKd = new QLabel(groupBox_4);
        lblKd->setObjectName("lblKd");

        formLayout_3->setWidget(2, QFormLayout::LabelRole, lblKd);

        editKd = new QLineEdit(groupBox_4);
        editKd->setObjectName("editKd");
        editKd->setReadOnly(true);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, editKd);

        lblTi = new QLabel(groupBox_4);
        lblTi->setObjectName("lblTi");

        formLayout_3->setWidget(3, QFormLayout::LabelRole, lblTi);

        editTi = new QLineEdit(groupBox_4);
        editTi->setObjectName("editTi");
        editTi->setReadOnly(true);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, editTi);

        lblTd = new QLabel(groupBox_4);
        lblTd->setObjectName("lblTd");

        formLayout_3->setWidget(4, QFormLayout::LabelRole, lblTd);

        editTd = new QLineEdit(groupBox_4);
        editTd->setObjectName("editTd");
        editTd->setReadOnly(true);

        formLayout_3->setWidget(4, QFormLayout::FieldRole, editTd);

        lblOvershoot = new QLabel(groupBox_4);
        lblOvershoot->setObjectName("lblOvershoot");

        formLayout_3->setWidget(5, QFormLayout::LabelRole, lblOvershoot);

        editOvershoot = new QLineEdit(groupBox_4);
        editOvershoot->setObjectName("editOvershoot");
        editOvershoot->setReadOnly(true);

        formLayout_3->setWidget(5, QFormLayout::FieldRole, editOvershoot);

        lblSettlingTime = new QLabel(groupBox_4);
        lblSettlingTime->setObjectName("lblSettlingTime");

        formLayout_3->setWidget(6, QFormLayout::LabelRole, lblSettlingTime);

        editSettlingTime = new QLineEdit(groupBox_4);
        editSettlingTime->setObjectName("editSettlingTime");
        editSettlingTime->setReadOnly(true);

        formLayout_3->setWidget(6, QFormLayout::FieldRole, editSettlingTime);

        txtRecommendations = new QTextEdit(groupBox_4);
        txtRecommendations->setObjectName("txtRecommendations");
        txtRecommendations->setMaximumSize(QSize(16777215, 100));

        formLayout_3->setWidget(7, QFormLayout::SpanningRole, txtRecommendations);

        btnApplySettings = new QPushButton(groupBox_4);
        btnApplySettings->setObjectName("btnApplySettings");

        formLayout_3->setWidget(8, QFormLayout::SpanningRole, btnApplySettings);


        horizontalLayout_3->addWidget(groupBox_4);

        tabWidget->addTab(tabTuning, QString());
        tabSimulation = new QWidget();
        tabSimulation->setObjectName("tabSimulation");
        verticalLayout_3 = new QVBoxLayout(tabSimulation);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        btnSimulate = new QPushButton(tabSimulation);
        btnSimulate->setObjectName("btnSimulate");

        horizontalLayout_4->addWidget(btnSimulate);

        btnReset = new QPushButton(tabSimulation);
        btnReset->setObjectName("btnReset");

        horizontalLayout_4->addWidget(btnReset);

        lblStatus = new QLabel(tabSimulation);
        lblStatus->setObjectName("lblStatus");

        horizontalLayout_4->addWidget(lblStatus);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_4);

        processChartView = new QGraphicsView(tabSimulation);
        processChartView->setObjectName("processChartView");

        verticalLayout_3->addWidget(processChartView);

        controlChartView = new QGraphicsView(tabSimulation);
        controlChartView->setObjectName("controlChartView");

        verticalLayout_3->addWidget(controlChartView);

        tabWidget->addTab(tabSimulation, QString());
        tabExport = new QWidget();
        tabExport->setObjectName("tabExport");
        verticalLayout_4 = new QVBoxLayout(tabExport);
        verticalLayout_4->setObjectName("verticalLayout_4");
        groupBox_5 = new QGroupBox(tabExport);
        groupBox_5->setObjectName("groupBox_5");
        horizontalLayout_5 = new QHBoxLayout(groupBox_5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        btnExport = new QPushButton(groupBox_5);
        btnExport->setObjectName("btnExport");

        horizontalLayout_5->addWidget(btnExport);

        btnExportJSON = new QPushButton(groupBox_5);
        btnExportJSON->setObjectName("btnExportJSON");

        horizontalLayout_5->addWidget(btnExportJSON);

        btnExportReport = new QPushButton(groupBox_5);
        btnExportReport->setObjectName("btnExportReport");

        horizontalLayout_5->addWidget(btnExportReport);


        verticalLayout_4->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(tabExport);
        groupBox_6->setObjectName("groupBox_6");
        horizontalLayout_6 = new QHBoxLayout(groupBox_6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        btnImport = new QPushButton(groupBox_6);
        btnImport->setObjectName("btnImport");

        horizontalLayout_6->addWidget(btnImport);

        btnImportData = new QPushButton(groupBox_6);
        btnImportData->setObjectName("btnImportData");

        horizontalLayout_6->addWidget(btnImportData);


        verticalLayout_4->addWidget(groupBox_6);

        tabWidget->addTab(tabExport, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1400, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PID AutoTuner - \320\235\320\265\321\204\321\202\320\265\320\263\320\260\320\267\320\276\320\262\320\276\320\265 \320\277\321\200\320\270\320\274\320\265\320\275\320\265\320\275\320\270\320\265", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271 \320\277\321\200\320\276\320\265\320\272\321\202", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214...", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        lblTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\233\242\357\270\217 \320\241\320\270\321\201\321\202\320\265\320\274\320\260 \320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\271 \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\237\320\230\320\224-\320\240\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200\320\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262 \320\234\320\276\320\264\320\265\320\273\320\270", nullptr));
        lblProcessType->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\260:", nullptr));
        cmbProcessType->setItemText(0, QCoreApplication::translate("MainWindow", "FOPDT (\320\237\320\265\321\200\320\262\321\213\320\271 \320\277\320\276\321\200\321\217\320\264\320\276\320\272 + \320\267\320\260\320\264\320\265\321\200\320\266\320\272\320\260)", nullptr));
        cmbProcessType->setItemText(1, QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\262\321\213\320\271 \320\277\320\276\321\200\321\217\320\264\320\276\320\272", nullptr));
        cmbProcessType->setItemText(2, QCoreApplication::translate("MainWindow", "\320\222\321\202\320\276\321\200\320\276\320\271 \320\277\320\276\321\200\321\217\320\264\320\276\320\272", nullptr));
        cmbProcessType->setItemText(3, QCoreApplication::translate("MainWindow", "\320\230\320\275\321\202\320\265\320\263\321\200\320\270\321\200\321\203\321\216\321\211\320\265\320\265 \320\267\320\262\320\265\320\275\320\276", nullptr));
        cmbProcessType->setItemText(4, QCoreApplication::translate("MainWindow", "\320\242\320\265\320\277\320\273\320\276\320\276\320\261\320\274\320\265\320\275\320\275\320\270\320\272", nullptr));
        cmbProcessType->setItemText(5, QCoreApplication::translate("MainWindow", "\320\242\321\200\321\203\320\261\320\276\320\277\321\200\320\276\320\262\320\276\320\264", nullptr));

        lblGain->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\215\321\204\321\204. \321\203\321\201\320\270\320\273\320\265\320\275\320\270\321\217 (K):", nullptr));
        lblTimeConstant->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\320\276\321\217\320\275\320\275\320\260\321\217 \320\262\321\200\320\265\320\274\320\265\320\275\320\270 (T):", nullptr));
        lblDeadTime->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\267\320\260\320\264\320\265\321\200\320\266\320\272\320\270 (L):", nullptr));
        lblDisturbance->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\267\320\274\321\203\321\211\320\265\320\275\320\270\320\265:", nullptr));
        lblNoise->setText(QCoreApplication::translate("MainWindow", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214 \321\210\321\203\320\274\320\260:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\241\320\270\320\274\321\203\320\273\321\217\321\206\320\270\320\270", nullptr));
        lblSetpoint->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\262\320\272\320\260:", nullptr));
        lblSampleTime->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\264\320\270\321\201\320\272\321\200\320\265\321\202\320\270\320\267\320\260\321\206\320\270\320\270:", nullptr));
        lblSimSteps->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263\320\276\320\262 \321\201\320\270\320\274\321\203\320\273\321\217\321\206\320\270\320\270:", nullptr));
        lblOutputMin->setText(QCoreApplication::translate("MainWindow", "\320\234\320\270\320\275. \320\262\321\213\321\205\320\276\320\264:", nullptr));
        lblOutputMax->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\320\272\321\201. \320\262\321\213\321\205\320\276\320\264:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabProcess), QCoreApplication::translate("MainWindow", "\360\237\223\212 \320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\237\321\200\320\276\321\206\320\265\321\201\321\201\320\260", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\202\320\276\320\264 \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        lblMethod->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\274\320\265\321\202\320\276\320\264:", nullptr));
        cmbMethod->setItemText(0, QCoreApplication::translate("MainWindow", "Ziegler-Nichols (\320\246\320\270\320\263\320\273\320\265\321\200-\320\235\320\270\320\272\320\276\320\273\321\214\321\201)", nullptr));
        cmbMethod->setItemText(1, QCoreApplication::translate("MainWindow", "Cohen-Coon (\320\232\320\276\321\215\320\275-\320\232\321\203\320\275)", nullptr));
        cmbMethod->setItemText(2, QCoreApplication::translate("MainWindow", "IMC (\320\222\320\275\321\203\321\202\321\200\320\265\320\275\320\275\321\217\321\217 \320\234\320\276\320\264\320\265\320\273\321\214)", nullptr));

        btnTune->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247 \320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\321\203", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        lblKp->setText(QCoreApplication::translate("MainWindow", "Kp:", nullptr));
        lblKi->setText(QCoreApplication::translate("MainWindow", "Ki:", nullptr));
        lblKd->setText(QCoreApplication::translate("MainWindow", "Kd:", nullptr));
        lblTi->setText(QCoreApplication::translate("MainWindow", "Ti:", nullptr));
        lblTd->setText(QCoreApplication::translate("MainWindow", "Td:", nullptr));
        lblOvershoot->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\200\320\265\320\263\321\203\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265:", nullptr));
        lblSettlingTime->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \321\203\321\201\320\277\320\276\320\272\320\276\320\265\320\275\320\270\321\217:", nullptr));
        txtRecommendations->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\272\320\276\320\274\320\265\320\275\320\264\320\260\321\206\320\270\320\270 \320\277\320\276\321\217\320\262\321\217\321\202\321\201\321\217 \320\267\320\264\320\265\321\201\321\214...", nullptr));
        btnApplySettings->setText(QCoreApplication::translate("MainWindow", "\342\234\205 \320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTuning), QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\237\320\230\320\224", nullptr));
        btnSimulate->setText(QCoreApplication::translate("MainWindow", "\342\226\266\357\270\217 \320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \320\241\320\270\320\274\321\203\320\273\321\217\321\206\320\270\321\216", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 \320\241\320\261\321\200\320\276\321\201", nullptr));
        lblStatus->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201: \320\223\320\276\321\202\320\276\320\262", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSimulation), QCoreApplication::translate("MainWindow", "\360\237\223\210 \320\241\320\270\320\274\321\203\320\273\321\217\321\206\320\270\321\217 \320\270 \320\223\321\200\320\260\321\204\320\270\320\272\320\270", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\224\320\260\320\275\320\275\321\213\321\205", nullptr));
        btnExport->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244 \320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 CSV", nullptr));
        btnExportJSON->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244 \320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 JSON", nullptr));
        btnExportReport->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 \320\236\321\202\321\207\320\265\321\202 PDF", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202 \320\224\320\260\320\275\320\275\321\213\321\205", nullptr));
        btnImport->setText(QCoreApplication::translate("MainWindow", "\360\237\223\245 \320\230\320\274\320\277\320\276\321\200\321\202 \320\232\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270", nullptr));
        btnImportData->setText(QCoreApplication::translate("MainWindow", "\360\237\223\245 \320\230\320\274\320\277\320\276\321\200\321\202 \320\224\320\260\320\275\320\275\321\213\321\205", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabExport), QCoreApplication::translate("MainWindow", "\360\237\222\276 \320\255\320\272\321\201\320\277\320\276\321\200\321\202/\320\230\320\274\320\277\320\276\321\200\321\202", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
