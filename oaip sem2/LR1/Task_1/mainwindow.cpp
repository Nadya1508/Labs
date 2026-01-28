#include "mainwindow.h"
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QDateTime>
#include <QStyleFactory>
#include <QRandomGenerator>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_currentObject(nullptr)
    , m_car(nullptr)
    , m_animationTimer(new QTimer(this))
{
    setupUI();
    setupMenu();
    setupToolbar();
    setupControlPanel();
    setupConnections();
    
    m_animationTimer->setInterval(50);
    connect(m_animationTimer, &QTimer::timeout, this, &MainWindow::onAnimationTimer);
    m_animationTimer->start();
    
    setWindowTitle("OOP Demo: Movable Rectangle and Car with Opening Doors");
    resize(1200, 800);
    
    showMessage("Application started. Create a rectangle or car.");
    
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    if (m_currentObject) {
        delete m_currentObject;
    }
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    m_canvas = new QLabel(this);
    m_canvas->setMinimumSize(800, 500);
    m_canvas->setStyleSheet("background-color: white; border: 2px solid #cccccc; border-radius: 5px;");
    m_canvas->setAlignment(Qt::AlignCenter);
    m_canvas->setText("<center><b>OOP Laboratory Work</b><br>"
                      "Program with procedures and records<br><br>"
                      "Use 'Create Rectangle' or 'Create Car' button<br>"
                      "or menu File → Create</center>");
    
    m_statusLabel = new QLabel(this);
    m_statusLabel->setStyleSheet("background-color: #f0f0f0; padding: 8px; border-top: 1px solid #cccccc; font-family: monospace;");
    m_statusLabel->setText("Status: Ready");
    m_statusLabel->setMinimumHeight(30);
    
    mainLayout->addWidget(m_canvas, 1);
    mainLayout->addWidget(m_statusLabel);
    
    setCentralWidget(centralWidget);
}

void MainWindow::setupMenu()
{
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    QAction *createRectAction = new QAction("Create &Rectangle", this);
    createRectAction->setShortcut(QKeySequence("Ctrl+R"));
    createRectAction->setStatusTip("Create a new movable rectangle");
    fileMenu->addAction(createRectAction);
    connect(createRectAction, &QAction::triggered, this, &MainWindow::onCreateRectangle);
    
    QAction *createCarAction = new QAction("Create &Car", this);
    createCarAction->setShortcut(QKeySequence("Ctrl+A"));
    createCarAction->setStatusTip("Create a new car (inherits from rectangle)");
    fileMenu->addAction(createCarAction);
    connect(createCarAction, &QAction::triggered, this, &MainWindow::onCreateCar);
    
    fileMenu->addSeparator();
    
    QAction *saveRectAction = new QAction("Save &Rectangle", this);
    fileMenu->addAction(saveRectAction);
    connect(saveRectAction, &QAction::triggered, this, &MainWindow::onSaveRectangle);
    
    QAction *loadRectAction = new QAction("Load Rect&angle", this);
    fileMenu->addAction(loadRectAction);
    connect(loadRectAction, &QAction::triggered, this, &MainWindow::onLoadRectangle);
    
    fileMenu->addSeparator();
    
    QAction *saveCarAction = new QAction("Save &Car", this);
    saveCarAction->setShortcut(QKeySequence("Ctrl+S"));
    fileMenu->addAction(saveCarAction);
    connect(saveCarAction, &QAction::triggered, this, &MainWindow::onSaveCar);
    
    QAction *loadCarAction = new QAction("&Load Car", this);
    loadCarAction->setShortcut(QKeySequence("Ctrl+O"));
    fileMenu->addAction(loadCarAction);
    connect(loadCarAction, &QAction::triggered, this, &MainWindow::onLoadCar);
    
    fileMenu->addSeparator();
    
    QAction *exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    
    // Edit menu
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    
    QAction *changeRectColorAction = new QAction("Change Rectangle &Color", this);
    editMenu->addAction(changeRectColorAction);
    connect(changeRectColorAction, &QAction::triggered, this, &MainWindow::onChangeRectangleColor);
    
    QAction *changeCarColorAction = new QAction("Change Car &Body Color", this);
    editMenu->addAction(changeCarColorAction);
    connect(changeCarColorAction, &QAction::triggered, this, &MainWindow::onChangeCarColor);
    
    QAction *changeWheelColorAction = new QAction("Change &Wheel Color", this);
    editMenu->addAction(changeWheelColorAction);
    connect(changeWheelColorAction, &QAction::triggered, this, &MainWindow::onChangeWheelColor);
    
    // Control menu
    QMenu *controlMenu = menuBar()->addMenu("&Control");
    
    QAction *moveLeftAction = new QAction("Move &Left", this);
    moveLeftAction->setShortcut(QKeySequence("Left"));
    controlMenu->addAction(moveLeftAction);
    connect(moveLeftAction, &QAction::triggered, this, &MainWindow::onMoveLeft);
    
    QAction *moveRightAction = new QAction("Move &Right", this);
    moveRightAction->setShortcut(QKeySequence("Right"));
    controlMenu->addAction(moveRightAction);
    connect(moveRightAction, &QAction::triggered, this, &MainWindow::onMoveRight);
    
    QAction *moveUpAction = new QAction("Move &Up", this);
    moveUpAction->setShortcut(QKeySequence("Up"));
    controlMenu->addAction(moveUpAction);
    connect(moveUpAction, &QAction::triggered, this, &MainWindow::onMoveUp);
    
    QAction *moveDownAction = new QAction("Move &Down", this);
    moveDownAction->setShortcut(QKeySequence("Down"));
    controlMenu->addAction(moveDownAction);
    connect(moveDownAction, &QAction::triggered, this, &MainWindow::onMoveDown);
    
    controlMenu->addSeparator();
    
    QAction *stopAction = new QAction("&Stop Movement", this);
    stopAction->setShortcut(QKeySequence("Space"));
    controlMenu->addAction(stopAction);
    connect(stopAction, &QAction::triggered, this, &MainWindow::onStopMovement);
    
    QAction *resetAction = new QAction("&Reset Position", this);
    resetAction->setShortcut(QKeySequence("Ctrl+R"));
    controlMenu->addAction(resetAction);
    connect(resetAction, &QAction::triggered, this, &MainWindow::onResetPosition);
    
    // Car menu
    QMenu *carMenu = menuBar()->addMenu("&Car");
    
    QAction *leftDoorAction = new QAction("Left &Door", this);
    leftDoorAction->setShortcut(QKeySequence("L"));
    carMenu->addAction(leftDoorAction);
    connect(leftDoorAction, &QAction::triggered, this, &MainWindow::onToggleLeftDoor);
    
    QAction *rightDoorAction = new QAction("Right &Door", this);
    rightDoorAction->setShortcut(QKeySequence("P"));
    carMenu->addAction(rightDoorAction);
    connect(rightDoorAction, &QAction::triggered, this, &MainWindow::onToggleRightDoor);
    
    QAction *headlightsAction = new QAction("&Headlights", this);
    headlightsAction->setShortcut(QKeySequence("H"));
    carMenu->addAction(headlightsAction);
    connect(headlightsAction, &QAction::triggered, this, &MainWindow::onToggleHeadlights);
    
    carMenu->addSeparator();
    
    QAction *openAllDoorsAction = new QAction("Open &All Doors", this);
    carMenu->addAction(openAllDoorsAction);
    connect(openAllDoorsAction, &QAction::triggered, this, &MainWindow::onOpenAllDoors);
    
    QAction *closeAllDoorsAction = new QAction("&Close All Doors", this);
    carMenu->addAction(closeAllDoorsAction);
    connect(closeAllDoorsAction, &QAction::triggered, this, &MainWindow::onCloseAllDoors);
    
    carMenu->addSeparator();
    
    QAction *startEngineAction = new QAction("Start &Engine", this);
    startEngineAction->setShortcut(QKeySequence("Ctrl+E"));
    carMenu->addAction(startEngineAction);
    connect(startEngineAction, &QAction::triggered, this, &MainWindow::onStartEngine);
    
    QAction *stopEngineAction = new QAction("Stop E&ngine", this);
    carMenu->addAction(stopEngineAction);
    connect(stopEngineAction, &QAction::triggered, this, &MainWindow::onStopEngine);
    
    QAction *parkAction = new QAction("&Park", this);
    parkAction->setShortcut(QKeySequence("Ctrl+P"));
    carMenu->addAction(parkAction);
    connect(parkAction, &QAction::triggered, this, &MainWindow::onParkCar);
    
    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    
    QAction *aboutAction = new QAction("&About", this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    
    QAction *helpAction = new QAction("&Help", this);
    helpAction->setShortcut(QKeySequence("F1"));
    helpMenu->addAction(helpAction);
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelp);
}

void MainWindow::setupToolbar()
{
    QToolBar *toolbar = addToolBar("Main Toolbar");
    toolbar->setMovable(false);
    toolbar->setIconSize(QSize(24, 24));
    
    // Добавляем кнопки на тулбар
    QAction *createRectAction = toolbar->addAction("Create Rectangle");
    connect(createRectAction, &QAction::triggered, this, &MainWindow::onCreateRectangle);
    
    QAction *createCarAction = toolbar->addAction("Create Car");
    connect(createCarAction, &QAction::triggered, this, &MainWindow::onCreateCar);
    
    toolbar->addSeparator();
    
    QAction *moveLeftAction = toolbar->addAction("Move Left");
    connect(moveLeftAction, &QAction::triggered, this, &MainWindow::onMoveLeft);
    
    QAction *moveRightAction = toolbar->addAction("Move Right");
    connect(moveRightAction, &QAction::triggered, this, &MainWindow::onMoveRight);
    
    QAction *stopAction = toolbar->addAction("Stop");
    connect(stopAction, &QAction::triggered, this, &MainWindow::onStopMovement);
    
    toolbar->addSeparator();
    
    QAction *leftDoorAction = toolbar->addAction("Left Door");
    connect(leftDoorAction, &QAction::triggered, this, &MainWindow::onToggleLeftDoor);
    
    QAction *rightDoorAction = toolbar->addAction("Right Door");
    connect(rightDoorAction, &QAction::triggered, this, &MainWindow::onToggleRightDoor);
    
    QAction *headlightsAction = toolbar->addAction("Headlights");
    connect(headlightsAction, &QAction::triggered, this, &MainWindow::onToggleHeadlights);
}

void MainWindow::setupControlPanel()
{
    QDockWidget *dock = new QDockWidget("Control Panel", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    
    QWidget *dockWidget = new QWidget(dock);
    QVBoxLayout *dockLayout = new QVBoxLayout(dockWidget);
    
    // Object Creation Group
    QGroupBox *creationGroup = new QGroupBox("Object Creation", dockWidget);
    creationGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QGridLayout *creationLayout = new QGridLayout(creationGroup);
    
    QPushButton *btnCreateRect = new QPushButton("Create Rectangle", creationGroup);
    btnCreateRect->setToolTip("Create a movable rectangle (parent class)");
    QPushButton *btnCreateCar = new QPushButton("Create Car", creationGroup);
    btnCreateCar->setToolTip("Create a car (child class inherits from rectangle)");
    
    creationLayout->addWidget(btnCreateRect, 0, 0);
    creationLayout->addWidget(btnCreateCar, 0, 1);
    
    // Rectangle Control Group
    QGroupBox *rectGroup = new QGroupBox("Rectangle Control", dockWidget);
    rectGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QGridLayout *rectLayout = new QGridLayout(rectGroup);
    
    QPushButton *btnMoveRect = new QPushButton("Move", rectGroup);
    QPushButton *btnChangeRectColor = new QPushButton("Change Color", rectGroup);
    QPushButton *btnSaveRect = new QPushButton("Save", rectGroup);
    QPushButton *btnLoadRect = new QPushButton("Load", rectGroup);
    
    rectLayout->addWidget(btnMoveRect, 0, 0);
    rectLayout->addWidget(btnChangeRectColor, 0, 1);
    rectLayout->addWidget(btnSaveRect, 1, 0);
    rectLayout->addWidget(btnLoadRect, 1, 1);
    
    // Car Control Group
    QGroupBox *carGroup = new QGroupBox("Car Control", dockWidget);
    carGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QGridLayout *carLayout = new QGridLayout(carGroup);
    
    QPushButton *btnLeftDoor = new QPushButton("Left Door", carGroup);
    QPushButton *btnRightDoor = new QPushButton("Right Door", carGroup);
    QPushButton *btnHeadlights = new QPushButton("Headlights", carGroup);
    QPushButton *btnOpenAll = new QPushButton("Open All", carGroup);
    QPushButton *btnCloseAll = new QPushButton("Close All", carGroup);
    QPushButton *btnStartEngine = new QPushButton("Start Engine", carGroup);
    QPushButton *btnStopEngine = new QPushButton("Stop Engine", carGroup);
    QPushButton *btnPark = new QPushButton("Park", carGroup);
    QPushButton *btnBodyColor = new QPushButton("Body Color", carGroup);
    QPushButton *btnWheelColor = new QPushButton("Wheel Color", carGroup);
    QPushButton *btnSaveCar = new QPushButton("Save Car", carGroup);
    QPushButton *btnLoadCar = new QPushButton("Load Car", carGroup);
    
    carLayout->addWidget(btnLeftDoor, 0, 0);
    carLayout->addWidget(btnRightDoor, 0, 1);
    carLayout->addWidget(btnHeadlights, 1, 0);
    carLayout->addWidget(btnOpenAll, 1, 1);
    carLayout->addWidget(btnCloseAll, 2, 0);
    carLayout->addWidget(btnStartEngine, 2, 1);
    carLayout->addWidget(btnStopEngine, 3, 0);
    carLayout->addWidget(btnPark, 3, 1);
    carLayout->addWidget(btnBodyColor, 4, 0);
    carLayout->addWidget(btnWheelColor, 4, 1);
    carLayout->addWidget(btnSaveCar, 5, 0);
    carLayout->addWidget(btnLoadCar, 5, 1);
    
    // Movement Control Group
    QGroupBox *moveGroup = new QGroupBox("Movement Control", dockWidget);
    moveGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
    QGridLayout *moveLayout = new QGridLayout(moveGroup);
    
    QPushButton *btnLeft = new QPushButton("← Left", moveGroup);
    QPushButton *btnRight = new QPushButton("Right →", moveGroup);
    QPushButton *btnUp = new QPushButton("↑ Up", moveGroup);
    QPushButton *btnDown = new QPushButton("↓ Down", moveGroup);
    QPushButton *btnStop = new QPushButton("⏹ Stop", moveGroup);
    QPushButton *btnReset = new QPushButton("⟲ Reset", moveGroup);
    
    moveLayout->addWidget(btnLeft, 0, 0);
    moveLayout->addWidget(btnRight, 0, 1);
    moveLayout->addWidget(btnUp, 1, 0);
    moveLayout->addWidget(btnDown, 1, 1);
    moveLayout->addWidget(btnStop, 2, 0);
    moveLayout->addWidget(btnReset, 2, 1);
    
    dockLayout->addWidget(creationGroup);
    dockLayout->addWidget(rectGroup);
    dockLayout->addWidget(carGroup);
    dockLayout->addWidget(moveGroup);
    dockLayout->addStretch();
    
    dockWidget->setLayout(dockLayout);
    dock->setWidget(dockWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    
    // Connect signals
    connect(btnCreateRect, &QPushButton::clicked, this, &MainWindow::onCreateRectangle);
    connect(btnCreateCar, &QPushButton::clicked, this, &MainWindow::onCreateCar);
    connect(btnMoveRect, &QPushButton::clicked, this, &MainWindow::onMoveRectangle);
    connect(btnChangeRectColor, &QPushButton::clicked, this, &MainWindow::onChangeRectangleColor);
    connect(btnSaveRect, &QPushButton::clicked, this, &MainWindow::onSaveRectangle);
    connect(btnLoadRect, &QPushButton::clicked, this, &MainWindow::onLoadRectangle);
    
    connect(btnLeftDoor, &QPushButton::clicked, this, &MainWindow::onToggleLeftDoor);
    connect(btnRightDoor, &QPushButton::clicked, this, &MainWindow::onToggleRightDoor);
    connect(btnHeadlights, &QPushButton::clicked, this, &MainWindow::onToggleHeadlights);
    connect(btnOpenAll, &QPushButton::clicked, this, &MainWindow::onOpenAllDoors);
    connect(btnCloseAll, &QPushButton::clicked, this, &MainWindow::onCloseAllDoors);
    connect(btnStartEngine, &QPushButton::clicked, this, &MainWindow::onStartEngine);
    connect(btnStopEngine, &QPushButton::clicked, this, &MainWindow::onStopEngine);
    connect(btnPark, &QPushButton::clicked, this, &MainWindow::onParkCar);
    connect(btnBodyColor, &QPushButton::clicked, this, &MainWindow::onChangeCarColor);
    connect(btnWheelColor, &QPushButton::clicked, this, &MainWindow::onChangeWheelColor);
    connect(btnSaveCar, &QPushButton::clicked, this, &MainWindow::onSaveCar);
    connect(btnLoadCar, &QPushButton::clicked, this, &MainWindow::onLoadCar);
    
    connect(btnLeft, &QPushButton::clicked, this, &MainWindow::onMoveLeft);
    connect(btnRight, &QPushButton::clicked, this, &MainWindow::onMoveRight);
    connect(btnUp, &QPushButton::clicked, this, &MainWindow::onMoveUp);
    connect(btnDown, &QPushButton::clicked, this, &MainWindow::onMoveDown);
    connect(btnStop, &QPushButton::clicked, this, &MainWindow::onStopMovement);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::onResetPosition);
}

void MainWindow::setupConnections()
{
    // Connections are set up when objects are created
}

void MainWindow::onAnimationTimer()
{
    if (m_currentObject) {
        if (m_car) {
            m_car->updateAnimation();
        }
        m_currentObject->move();
    }
    update();
    updateStatus();
}

void MainWindow::updateStatus()
{
    if (!m_currentObject) {
        m_statusLabel->setText("Status: No active object. Use 'Create Rectangle' or 'Create Car'.");
        return;
    }
    
    QString status;
    if (m_car) {
        QString stateStr;
        switch(m_car->getCarState()) {
            case CAR_STOPPED: stateStr = "Stopped"; break;
            case CAR_MOVING: stateStr = "Moving"; break;
            case CAR_PARKED: stateStr = "Parked"; break;
        }
        
        status = QString("Car | Pos: (%1, %2) | Size: %3x%4 | Speed: (%5, %6) | "
                        "Doors: %7%8 | Lights: %9 | State: %10")
            .arg(m_car->getPosition().x())
            .arg(m_car->getPosition().y())
            .arg(m_car->getWidth())
            .arg(m_car->getHeight())
            .arg(m_car->getSpeedX(), 0, 'f', 1)
            .arg(m_car->getSpeedY(), 0, 'f', 1)
            .arg(m_car->isLeftDoorOpen() ? "L-" : "L+")
            .arg(m_car->isRightDoorOpen() ? "R-" : "R+")
            .arg(m_car->areHeadlightsOn() ? "ON" : "OFF")
            .arg(stateStr);
    } else {
        status = QString("Rectangle | Pos: (%1, %2) | Size: %3x%4 | "
                        "Speed: (%5, %6) | Color: %7")
            .arg(m_currentObject->getPosition().x())
            .arg(m_currentObject->getPosition().y())
            .arg(m_currentObject->getWidth())
            .arg(m_currentObject->getHeight())
            .arg(m_currentObject->getSpeedX(), 0, 'f', 1)
            .arg(m_currentObject->getSpeedY(), 0, 'f', 1)
            .arg(m_currentObject->getColor().name());
    }
    
    m_statusLabel->setText("Status: " + status);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    if (!m_currentObject) {
        QPixmap pixmap(m_canvas->size());
        pixmap.fill(QColor(240, 240, 240));
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::darkGray, 1));
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        
        QString message = "OOP Laboratory Work\n"
                         "Program with Procedures and Records\n\n"
                         "Instructions:\n"
                         "1. Create Rectangle - demonstrates parent class\n"
                         "2. Create Car - demonstrates inheritance\n"
                         "3. Use controls to interact with objects\n\n"
                         "Press F1 for help";
        
        painter.drawText(pixmap.rect().adjusted(20, 20, -20, -20), 
                        Qt::AlignCenter | Qt::TextWordWrap, message);
        
        m_canvas->setPixmap(pixmap);
        return;
    }
    
    QPixmap pixmap(m_canvas->size());
    pixmap.fill(Qt::white);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw sky
    QLinearGradient skyGradient(0, 0, 0, pixmap.height()/2);
    skyGradient.setColorAt(0, QColor(135, 206, 250));
    skyGradient.setColorAt(1, QColor(240, 248, 255));
    painter.fillRect(0, 0, pixmap.width(), pixmap.height()/2, skyGradient);
    
    // Draw ground
    painter.fillRect(0, pixmap.height()/2, pixmap.width(), pixmap.height()/2, 
                    QColor(34, 139, 34));
    
    // Draw road
    painter.fillRect(0, pixmap.height()/2 - 25, pixmap.width(), 50, 
                    QColor(105, 105, 105));
    
    // Draw road markings
    painter.setPen(QPen(Qt::yellow, 3));
    for (int i = 0; i < pixmap.width(); i += 40) {
        painter.drawLine(i, pixmap.height()/2, i + 20, pixmap.height()/2);
    }
    
    // Draw object
    m_currentObject->draw(painter);
    
    m_canvas->setPixmap(pixmap);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        onMoveLeft();
        break;
    case Qt::Key_Right:
        onMoveRight();
        break;
    case Qt::Key_Up:
        onMoveUp();
        break;
    case Qt::Key_Down:
        onMoveDown();
        break;
    case Qt::Key_Space:
        onStopMovement();
        break;
    case Qt::Key_R:
        if (event->modifiers() & Qt::ControlModifier) {
            onResetPosition();
        } else {
            onCreateRectangle();
        }
        break;
    case Qt::Key_A:
        if (event->modifiers() & Qt::ControlModifier) {
            onCreateCar();
        }
        break;
    case Qt::Key_L:
        onToggleLeftDoor();
        break;
    case Qt::Key_P:
        onToggleRightDoor();
        break;
    case Qt::Key_H:
        onToggleHeadlights();
        break;
    case Qt::Key_E:
        if (event->modifiers() & Qt::ControlModifier) {
            onStartEngine();
        }
        break;
    case Qt::Key_F1:
        onHelp();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    
    if (m_currentObject) {
        int result = QMessageBox::question(this, "Save Changes",
                                          "Do you want to save the current object before exiting?",
                                          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (result == QMessageBox::Save) {
            if (m_car) {
                onSaveCar();
            } else {
                onSaveRectangle();
            }
        } else if (result == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }
    
    QMainWindow::closeEvent(event);
}

void MainWindow::onCreateRectangle()
{
    try {
        int x, y, width, height;
        QColor color;
        
        if (InputDialog::getRectangleParameters(this, x, y, width, height, color)) {
            if (m_currentObject) {
                disconnect(m_currentObject, nullptr, this, nullptr);
                delete m_currentObject;
                m_currentObject = nullptr;
                m_car = nullptr;
            }
            
            m_currentObject = new MovableRectangle(QPoint(x, y), width, height, color, this);
            m_car = nullptr;
            
            connect(m_currentObject, &MovableRectangle::errorOccurred, 
                   this, &MainWindow::onErrorOccurred);
            connect(m_currentObject, &MovableRectangle::stateChanged,
                   this, &MainWindow::updateStatus);
            
            showMessage(QString("Created rectangle: X=%1, Y=%2, W=%3, H=%4, Color=%5")
                       .arg(x).arg(y).arg(width).arg(height).arg(color.name()));
            
            updateStatus();
            forceUpdate();
        }
    } catch (const std::exception &e) {
        onErrorOccurred(QString("Create rectangle error: %1").arg(e.what()));
    }
}

void MainWindow::onCreateCar()
{
    try {
        int x, y, width, height;
        QColor color;
        
        if (InputDialog::getRectangleParameters(this, x, y, width, height, color)) {
            if (m_currentObject) {
                disconnect(m_currentObject, nullptr, this, nullptr);
                delete m_currentObject;
                m_currentObject = nullptr;
                m_car = nullptr;
            }
            
            m_car = new Car(QPoint(x, y), width, height, color, this);
            m_currentObject = m_car;
            
            // Соединяем сигналы
            connect(m_car, &Car::errorOccurred, 
                   this, &MainWindow::onErrorOccurred);
            connect(m_car, &Car::stateChanged,
                   this, &MainWindow::updateStatus);
            connect(m_car, &Car::carStateChanged,
                   this, &MainWindow::onCarStateChanged);
            connect(m_car, &Car::doorStateChanged,
                   this, &MainWindow::updateStatus);
            connect(m_car, &Car::headlightsStateChanged,
                   this, &MainWindow::updateStatus);
            connect(m_car, &Car::engineStateChanged,
                   this, &MainWindow::onEngineStateChanged);
            
            showMessage(QString("Created car: X=%1, Y=%2, W=%3, H=%4, Color=%5")
                       .arg(x).arg(y).arg(width).arg(height).arg(color.name()));
            
            updateStatus();
            forceUpdate();
        }
    } catch (const std::exception &e) {
        onErrorOccurred(QString("Create car error: %1").arg(e.what()));
    }
}

void MainWindow::onMoveRectangle()
{
    if (!m_currentObject || m_car) {
        showMessage("Create a rectangle first or switch to rectangle mode!", true);
        return;
    }
    
    float dx = (QRandomGenerator::global()->bounded(5)) - 2;
    float dy = (QRandomGenerator::global()->bounded(5)) - 2;
    
    m_currentObject->setSpeed(dx, dy);
    showMessage(QString("Rectangle moving: speed=(%1, %2)").arg(dx).arg(dy));
    forceUpdate();
}

void MainWindow::onChangeRectangleColor()
{
    if (!m_currentObject || m_car) {
        showMessage("Create a rectangle first or switch to rectangle mode!", true);
        return;
    }
    
    QColor color = QColorDialog::getColor(m_currentObject->getColor(), this, 
                                         "Choose Rectangle Color");
    if (color.isValid()) {
        m_currentObject->setColor(color);
        showMessage(QString("Rectangle color changed to: %1").arg(color.name()));
        forceUpdate();
    }
}

void MainWindow::onSaveRectangle()
{
    if (!m_currentObject || m_car) {
        showMessage("Create a rectangle first or switch to rectangle mode!", true);
        return;
    }
    
    QString filename = QFileDialog::getSaveFileName(this, "Save Rectangle", 
                                                   "", "Rectangle Files (*.rect)");
    if (!filename.isEmpty()) {
        if (m_currentObject->saveToFile(filename)) {
            showMessage(QString("Rectangle saved to: %1").arg(filename));
        }
    }
}

void MainWindow::onLoadRectangle()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load Rectangle", 
                                                   "", "Rectangle Files (*.rect)");
    if (!filename.isEmpty()) {
        if (m_currentObject) {
            disconnect(m_currentObject, nullptr, this, nullptr);
            delete m_currentObject;
            m_currentObject = nullptr;
            m_car = nullptr;
        }
        
        m_currentObject = new MovableRectangle(this);
        
        if (m_currentObject->loadFromFile(filename)) {
            connect(m_currentObject, &MovableRectangle::errorOccurred, 
                   this, &MainWindow::onErrorOccurred);
            connect(m_currentObject, &MovableRectangle::stateChanged,
                   this, &MainWindow::updateStatus);
            
            showMessage(QString("Rectangle loaded from: %1").arg(filename));
            updateStatus();
            forceUpdate();
        } else {
            delete m_currentObject;
            m_currentObject = nullptr;
            showMessage("Failed to load rectangle!", true);
        }
    }
}

void MainWindow::onToggleLeftDoor()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    m_car->toggleLeftDoor();
    showMessage(QString("Left door: %1").arg(m_car->isLeftDoorOpen() ? "opened" : "closed"));
    forceUpdate();
}

void MainWindow::onToggleRightDoor()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    m_car->toggleRightDoor();
    showMessage(QString("Right door: %1").arg(m_car->isRightDoorOpen() ? "opened" : "closed"));
    forceUpdate();
}

void MainWindow::onToggleHeadlights()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    m_car->toggleHeadlights();
    showMessage(QString("Headlights: %1").arg(m_car->areHeadlightsOn() ? "on" : "off"));
    forceUpdate();
}

void MainWindow::onOpenAllDoors()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    m_car->openAllDoors();
    showMessage("All doors opened");
    forceUpdate();
}

void MainWindow::onCloseAllDoors()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    m_car->closeAllDoors();
    showMessage("All doors closed");
    forceUpdate();
}

void MainWindow::onStartEngine()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    qDebug() << "=== START ENGINE BUTTON CLICKED ===";
    qDebug() << "Before startEngine() call:";
    qDebug() << "  Car pointer:" << m_car;
    qDebug() << "  Current state:" << m_car->getCarState();
    qDebug() << "  Current speed:" << m_car->getSpeedX() << "," << m_car->getSpeedY();
    
    // Вызываем метод startEngine
    m_car->startEngine();
    
    qDebug() << "After startEngine() call:";
    qDebug() << "  New state:" << m_car->getCarState();
    qDebug() << "  New speed:" << m_car->getSpeedX() << "," << m_car->getSpeedY();
    
    if (m_car->getCarState() == CAR_MOVING) {
        showMessage("Engine started! Car is now moving.");
    } else {
        showMessage("Engine started but car is not moving. Check car state.", true);
    }
    
    forceUpdate();
}

void MainWindow::onStopEngine()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    qDebug() << "=== STOP ENGINE BUTTON CLICKED ===";
    
    m_car->stopEngine();
    showMessage("Engine stopped");
    forceUpdate();
}

void MainWindow::onParkCar()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    qDebug() << "=== PARK BUTTON CLICKED ===";
    
    m_car->park();
    showMessage("Car parked");
    forceUpdate();
}

void MainWindow::onChangeCarColor()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    QColor color = QColorDialog::getColor(m_car->getBodyColor(), this, 
                                         "Choose Car Body Color");
    if (color.isValid()) {
        m_car->setBodyColor(color);
        showMessage(QString("Car body color changed to: %1").arg(color.name()));
        forceUpdate();
    }
}

void MainWindow::onChangeWheelColor()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    QColor color = QColorDialog::getColor(m_car->getWheelColor(), this, 
                                         "Choose Wheel Color");
    if (color.isValid()) {
        m_car->setWheelColor(color);
        showMessage(QString("Wheel color changed to: %1").arg(color.name()));
        forceUpdate();
    }
}

void MainWindow::onSaveCar()
{
    if (!m_car) {
        showMessage("Create a car first!", true);
        return;
    }
    
    QString filename = QFileDialog::getSaveFileName(this, "Save Car", 
                                                   "", "Car Files (*.car)");
    if (!filename.isEmpty()) {
        if (m_car->saveToFile(filename)) {
            showMessage(QString("Car saved to: %1").arg(filename));
        }
    }
}

void MainWindow::onLoadCar()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load Car", 
                                                   "", "Car Files (*.car)");
    if (!filename.isEmpty()) {
        if (m_currentObject) {
            disconnect(m_currentObject, nullptr, this, nullptr);
            delete m_currentObject;
            m_currentObject = nullptr;
            m_car = nullptr;
        }
        
        m_car = new Car(this);
        
        if (m_car->loadFromFile(filename)) {
            m_currentObject = m_car;
            
            // Соединяем сигналы
            connect(m_car, &Car::errorOccurred, 
                   this, &MainWindow::onErrorOccurred);
            connect(m_car, &Car::stateChanged,
                   this, &MainWindow::updateStatus);
            connect(m_car, &Car::carStateChanged,
                   this, &MainWindow::onCarStateChanged);
            connect(m_car, &Car::doorStateChanged,
                   this, &MainWindow::updateStatus);
            connect(m_car, &Car::headlightsStateChanged,
                   this, &MainWindow::updateStatus);
            connect(m_car, &Car::engineStateChanged,
                   this, &MainWindow::onEngineStateChanged);
            
            showMessage(QString("Car loaded from: %1").arg(filename));
            updateStatus();
            forceUpdate();
        } else {
            delete m_car;
            m_car = nullptr;
            m_currentObject = nullptr;
            showMessage("Failed to load car!", true);
        }
    }
}

void MainWindow::onMoveLeft()
{
    if (!m_currentObject) {
        showMessage("Create an object first!", true);
        return;
    }
    
    if (m_car) {
        // Для автомобиля проверяем состояние
        if (m_car->getCarState() == CAR_STOPPED) {
            showMessage("Starting engine automatically...", false);
            m_car->startEngine();
        }
        
        // Закрываем двери если они открыты
        if (m_car->isLeftDoorOpen() || m_car->isRightDoorOpen()) {
            showMessage("Closing doors automatically...", false);
            m_car->closeAllDoors();
        }
    }
    
    m_currentObject->setSpeed(-2, m_currentObject->getSpeedY());
    showMessage("Moving left");
    forceUpdate();
}

void MainWindow::onMoveRight()
{
    if (!m_currentObject) {
        showMessage("Create an object first!", true);
        return;
    }
    
    if (m_car) {
        if (m_car->getCarState() == CAR_STOPPED) {
            showMessage("Starting engine automatically...", false);
            m_car->startEngine();
        }
        
        if (m_car->isLeftDoorOpen() || m_car->isRightDoorOpen()) {
            showMessage("Closing doors automatically...", false);
            m_car->closeAllDoors();
        }
    }
    
    m_currentObject->setSpeed(2, m_currentObject->getSpeedY());
    showMessage("Moving right");
    forceUpdate();
}

void MainWindow::onMoveUp()
{
    if (!m_currentObject) {
        showMessage("Create an object first!", true);
        return;
    }
    
    if (m_car) {
        if (m_car->getCarState() == CAR_STOPPED) {
            showMessage("Starting engine automatically...", false);
            m_car->startEngine();
        }
        
        if (m_car->isLeftDoorOpen() || m_car->isRightDoorOpen()) {
            showMessage("Closing doors automatically...", false);
            m_car->closeAllDoors();
        }
    }
    
    m_currentObject->setSpeed(m_currentObject->getSpeedX(), -2);
    showMessage("Moving up");
    forceUpdate();
}

void MainWindow::onMoveDown()
{
    if (!m_currentObject) {
        showMessage("Create an object first!", true);
        return;
    }
    
    if (m_car) {
        if (m_car->getCarState() == CAR_STOPPED) {
            showMessage("Starting engine automatically...", false);
            m_car->startEngine();
        }
        
        if (m_car->isLeftDoorOpen() || m_car->isRightDoorOpen()) {
            showMessage("Closing doors automatically...", false);
            m_car->closeAllDoors();
        }
    }
    
    m_currentObject->setSpeed(m_currentObject->getSpeedX(), 2);
    showMessage("Moving down");
    forceUpdate();
}

void MainWindow::onStopMovement()
{
    if (!m_currentObject) {
        showMessage("Create an object first!", true);
        return;
    }
    
    m_currentObject->setSpeed(0, 0);
    showMessage("Movement stopped");
    forceUpdate();
}

void MainWindow::onResetPosition()
{
    if (!m_currentObject) {
        showMessage("Create an object first!", true);
        return;
    }
    
    m_currentObject->setPosition(QPoint(100, 300));
    m_currentObject->setSpeed(0, 0);
    
    if (m_car) {
        m_car->closeAllDoors();
        if (m_car->areHeadlightsOn()) {
            m_car->toggleHeadlights();
        }
    }
    
    showMessage("Position reset");
    forceUpdate();
}

void MainWindow::onErrorOccurred(const QString &message)
{
    showMessage(message, true);
    QMessageBox::critical(this, "Error", message);
    updateStatus();
}

void MainWindow::onEngineStateChanged(bool running)
{
    qDebug() << "Engine state changed:" << (running ? "RUNNING" : "STOPPED");
    showMessage(QString("Engine %1").arg(running ? "started" : "stopped"));
    forceUpdate();
}

void MainWindow::onCarStateChanged(CarState newState)
{
    QString stateStr;
    switch(newState) {
        case CAR_STOPPED: stateStr = "Stopped"; break;
        case CAR_MOVING: stateStr = "Moving"; break;
        case CAR_PARKED: stateStr = "Parked"; break;
    }
    
    qDebug() << "Car state changed to:" << stateStr;
    showMessage(QString("Car state: %1").arg(stateStr));
    forceUpdate();
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "About OOP Demo",
                      "<h3>Object-Oriented Programming Demo</h3>"
                      "<p><b>Laboratory Work:</b> Program development with procedures and records</p>"
                      "<p><b>Goal:</b> Demonstrate OOP principles using inheritance in C++/Qt</p>"
                      "<p><b>Features:</b></p>"
                      "<ul>"
                      "<li>Class inheritance (Rectangle → Car)</li>"
                      "<li>Encapsulation with getters/setters</li>"
                      "<li>Polymorphism through virtual methods</li>"
                      "<li>Exception handling</li>"
                      "<li>Visual I/O with Qt widgets</li>"
                      "<li>File serialization</li>"
                      "</ul>"
                      "<p><b>Classes:</b></p>"
                      "<ul>"
                      "<li><b>MovableRectangle</b> - Parent class with basic functionality</li>"
                      "<li><b>Car</b> - Child class with additional features (doors, headlights, engine)</li>"
                      "</ul>"
                      "<p><b>Version:</b> 1.0.0</p>"
                      "<p><b>Author:</b> Student</p>");
}

void MainWindow::onHelp()
{
    QString helpText = 
        "<h3>OOP Laboratory Work - Help</h3>"
        "<p><b>Program Purpose:</b> Demonstrate object-oriented programming principles "
        "using inheritance, encapsulation, and polymorphism.</p>"
        
        "<p><b>Main Features:</b></p>"
        "<ul>"
        "<li><b>Create Rectangle</b> - Creates a movable rectangle (parent class)</li>"
        "<li><b>Create Car</b> - Creates a car that inherits from rectangle (child class)</li>"
        "<li><b>Movement Control</b> - Arrow keys or buttons to move objects</li>"
        "<li><b>Car Features</b> - Doors, headlights, engine control</li>"
        "<li><b>File Operations</b> - Save/load objects to/from files</li>"
        "</ul>"
        
        "<p><b>Hotkeys:</b></p>"
        "<table border='1' cellpadding='4'>"
        "<tr><th>Key</th><th>Action</th></tr>"
        "<tr><td>Ctrl+R</td><td>Create Rectangle</td></tr>"
        "<tr><td>Ctrl+A</td><td>Create Car</td></tr>"
        "<tr><td>Arrow Keys</td><td>Move object</td></tr>"
        "<tr><td>Space</td><td>Stop movement</td></tr>"
        "<tr><td>L</td><td>Toggle left door</td></tr>"
        "<tr><td>P</td><td>Toggle right door</td></tr>"
        "<tr><td>H</td><td>Toggle headlights</td></tr>"
        "<tr><td>Ctrl+E</td><td>Start engine</td></tr>"
        "<tr><td>Ctrl+P</td><td>Park car</td></tr>"
        "<tr><td>F1</td><td>This help</td></tr>"
        "</table>"
        
        "<p><b>OOP Concepts Demonstrated:</b></p>"
        "<ul>"
        "<li><b>Inheritance:</b> Car inherits from MovableRectangle</li>"
        "<li><b>Polymorphism:</b> Overridden draw() and move() methods</li>"
        "<li><b>Encapsulation:</b> Private data with public getters/setters</li>"
        "<li><b>Abstraction:</b> Hide implementation details</li>"
        "</ul>";
    
    QMessageBox::information(this, "Help", helpText);
}

void MainWindow::showMessage(const QString &message, bool isError)
{
    QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss");
    QString formatted = QString("[%1] %2").arg(timestamp).arg(message);
    
    if (isError) {
        m_statusLabel->setStyleSheet("background-color: #ffcccc; padding: 8px; "
                                    "border-top: 2px solid #ff0000; font-family: monospace;");
    } else {
        m_statusLabel->setStyleSheet("background-color: #f0f0f0; padding: 8px; "
                                    "border-top: 1px solid #cccccc; font-family: monospace;");
    }
    
    m_statusLabel->setText(formatted);
    qDebug().noquote() << (isError ? "ERROR:" : "INFO:") << message;
}

void MainWindow::forceUpdate()
{
    updateStatus();
    update();
    QApplication::processEvents();
}

void MainWindow::saveSettings()
{
    QSettings settings("MyCompany", "CarApp");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    
    if (m_currentObject) {
        settings.setValue("lastObjectType", m_car ? "car" : "rectangle");
        if (m_car) {
            settings.setValue("car/position", m_car->getPosition());
            settings.setValue("car/size", QSize(m_car->getWidth(), m_car->getHeight()));
            settings.setValue("car/bodyColor", m_car->getBodyColor().name(QColor::HexArgb));
            settings.setValue("car/wheelColor", m_car->getWheelColor().name(QColor::HexArgb));
        } else {
            settings.setValue("rect/position", m_currentObject->getPosition());
            settings.setValue("rect/size", QSize(m_currentObject->getWidth(), 
                                                m_currentObject->getHeight()));
            settings.setValue("rect/color", m_currentObject->getColor().name(QColor::HexArgb));
        }
    }
}

void MainWindow::loadSettings()
{
    QSettings settings("MyCompany", "CarApp");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    
    QString lastObjectType = settings.value("lastObjectType").toString();
    
    if (lastObjectType == "car") {
        QPoint pos = settings.value("car/position", QPoint(100, 300)).toPoint();
        QSize size = settings.value("car/size", QSize(200, 100)).toSize();
        QString bodyColorStr = settings.value("car/bodyColor", "#ff0000").toString();
        QString wheelColorStr = settings.value("car/wheelColor", "#000000").toString();
        
        QColor bodyColor(bodyColorStr);
        QColor wheelColor(wheelColorStr);
        
        if (!bodyColor.isValid()) bodyColor = Qt::red;
        if (!wheelColor.isValid()) wheelColor = Qt::black;
        
        if (m_currentObject) {
            delete m_currentObject;
            m_currentObject = nullptr;
            m_car = nullptr;
        }
        
        m_car = new Car(pos, size.width(), size.height(), bodyColor, this);
        m_car->setWheelColor(wheelColor);
        m_currentObject = m_car;
        
        // Соединяем сигналы
        connect(m_car, &Car::errorOccurred, this, &MainWindow::onErrorOccurred);
        connect(m_car, &Car::stateChanged, this, &MainWindow::updateStatus);
        connect(m_car, &Car::carStateChanged, this, &MainWindow::onCarStateChanged);
        connect(m_car, &Car::doorStateChanged, this, &MainWindow::updateStatus);
        connect(m_car, &Car::headlightsStateChanged, this, &MainWindow::updateStatus);
        connect(m_car, &Car::engineStateChanged, this, &MainWindow::onEngineStateChanged);
        
        showMessage("Car state restored from settings");
        
    } else if (lastObjectType == "rectangle") {
        QPoint pos = settings.value("rect/position", QPoint(100, 300)).toPoint();
        QSize size = settings.value("rect/size", QSize(200, 100)).toSize();
        QString colorStr = settings.value("rect/color", "#0000ff").toString();
        
        QColor color(colorStr);
        if (!color.isValid()) color = Qt::blue;
        
        if (m_currentObject) {
            delete m_currentObject;
            m_currentObject = nullptr;
            m_car = nullptr;
        }
        
        m_currentObject = new MovableRectangle(pos, size.width(), size.height(), color, this);
        m_car = nullptr;
        
        connect(m_currentObject, &MovableRectangle::errorOccurred, 
               this, &MainWindow::onErrorOccurred);
        connect(m_currentObject, &MovableRectangle::stateChanged,
               this, &MainWindow::updateStatus);
        
        showMessage("Rectangle state restored from settings");
    }
    
    updateStatus();
    forceUpdate();
}

void MainWindow::updateObjectInfo()
{
    // This method is kept for compatibility
    updateStatus();
}