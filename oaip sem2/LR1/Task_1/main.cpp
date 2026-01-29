#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("CarApp");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("MyCompany");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}