#include <QApplication>
#include "mainwindow.h"
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Настройка приложения
    QApplication::setApplicationName("PID AutoTuner");
    QApplication::setApplicationVersion(APP_VERSION);
    QApplication::setOrganizationName("OilGasAutomation");
    
    // Установка современного стиля
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    
    // Настройка палитры
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(245, 245, 245));
    palette.setColor(QPalette::WindowText, QColor(44, 62, 80));
    palette.setColor(QPalette::Base, QColor(255, 255, 255));
    palette.setColor(QPalette::AlternateBase, QColor(236, 240, 241));
    palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 255));
    palette.setColor(QPalette::ToolTipText, QColor(44, 62, 80));
    palette.setColor(QPalette::Text, QColor(44, 62, 80));
    palette.setColor(QPalette::Button, QColor(52, 152, 219));
    palette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    palette.setColor(QPalette::BrightText, Qt::white);
    palette.setColor(QPalette::Link, QColor(52, 152, 219));
    palette.setColor(QPalette::Highlight, QColor(52, 152, 219));
    palette.setColor(QPalette::HighlightedText, Qt::white);
    
    QApplication::setPalette(palette);
    
    // Создание и показ главного окна
    MainWindow w;
    w.show();
    
    qDebug() << "PID AutoTuner запущен. Версия:" << APP_VERSION;
    
    return a.exec();
}
