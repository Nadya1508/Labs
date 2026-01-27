#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Настройки приложения
    app.setApplicationName("CarApp");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("MyCompany");
    
    // Создание и отображение главного окна
    MainWindow window;
    window.show();
    
    return app.exec();
}