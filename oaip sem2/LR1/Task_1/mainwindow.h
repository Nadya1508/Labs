#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QSettings>
#include "car.h"
#include "movable_rectangle.h"
#include "inputdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onAnimationTimer();
    void updateStatus();
    
    // Слоты для управления прямоугольником
    void onCreateRectangle();
    void onCreateCar();
    
    // Дополнительные методы для прямоугольника
    void onMoveRectangle();
    void onChangeRectangleColor();
    void onSaveRectangle();
    void onLoadRectangle();
    
    // Слоты для управления автомобилем
    void onToggleLeftDoor();
    void onToggleRightDoor();
    void onToggleHeadlights();
    void onOpenAllDoors();
    void onCloseAllDoors();
    void onStartEngine();
    void onStopEngine();
    void onParkCar();
    void onChangeCarColor();
    void onChangeWheelColor();
    void onSaveCar();
    void onLoadCar();
    
    // Слоты для управления движением
    void onMoveLeft();
    void onMoveRight();
    void onMoveUp();
    void onMoveDown();
    void onStopMovement();
    void onResetPosition();
    
    // Слоты для обработки ошибок
    void onErrorOccurred(const QString &message);
    
    // Слоты меню
    void onAbout();
    void onHelp();
    
    // Дополнительные слоты
    void onEngineStateChanged(bool running);
    void onCarStateChanged(CarState newState);

private:
    MovableRectangle *m_currentObject;  // Текущий объект (прямоугольник или автомобиль)
    Car *m_car;                         // Указатель на автомобиль (если создан)
    QTimer *m_animationTimer;
    QLabel *m_canvas;
    QLabel *m_statusLabel;
    
    // UI элементы
    QPushButton *createButton(const QString &text, const QString &tooltip = "");
    
    void setupUI();
    void setupMenu();
    void setupToolbar();
    void setupControlPanel();
    void setupConnections();
    void saveSettings();
    void loadSettings();
    
    // Вспомогательные методы
    void showMessage(const QString &message, bool isError = false);
    void updateObjectInfo();  // Обновление информации об объекте
    void forceUpdate();       // Принудительное обновление интерфейса
};

#endif // MAINWINDOW_H