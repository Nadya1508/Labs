#include "mainwindow.h"
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    
    setWindowTitle("OOP Demo: Car with Opening Doors");
    resize(1000, 700);
    
    showMessage("Application started. Create a car or rectangle.");
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    m_canvas = new QLabel(this);
    m_canvas->setMinimumSize(600, 400);
    m_canvas->setStyleSheet("background-color: white; border: 2px solid #cccccc;");
    m_canvas->setAlignment(Qt::AlignCenter);
    m_canvas->setText("Click 'Create Car' or 'Create Rectangle'");
    
    m_statusLabel = new QLabel(this);
    m_statusLabel->setStyleSheet("background-color: #f0f0f0; padding: 5px; border-top: 1px solid #cccccc;");
    m_statusLabel->setText("Ready");
    
    mainLayout->addWidget(m_canvas);
    mainLayout->addWidget(m_statusLabel);
    
    setCentralWidget(centralWidget);
}

void MainWindow::setupMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    QAction *createRectAction = new QAction("Create &Rectangle", this);
    createRectAction->setShortcut(QKeySequence("Ctrl+R"));
    fileMenu->addAction(createRectAction);
    connect(createRectAction, &QAction::triggered, this, &MainWindow::onCreateRectangle);
    
    QAction *createCarAction = new QAction("Create &Car", this);
    createCarAction->setShortcut(QKeySequence("Ctrl+A"));
    fileMenu->addAction(createCarAction);
    connect(createCarAction, &QAction::triggered, this, &MainWindow::onCreateCar);
    
    fileMenu->addSeparator();
    
    QAction *saveCarAction = new QAction("&Save Car", this);
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
    
    QAction *stopAction = new QAction("&Stop", this);
    stopAction->setShortcut(QKeySequence("Space"));
    controlMenu->addAction(stopAction);
    connect(stopAction, &QAction::triggered, this, &MainWindow::onStopMovement);
    
    QAction *resetAction = new QAction("&Reset Position", this);
    resetAction->setShortcut(QKeySequence("R"));
    controlMenu->addAction(resetAction);
    connect(resetAction, &QAction::triggered, this, &MainWindow::onResetPosition);
    
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
    
    carMenu->addSeparator();
    
    QAction *changeCarColorAction = new QAction("Change &Body Color", this);
    carMenu->addAction(changeCarColorAction);
    connect(changeCarColorAction, &QAction::triggered, this, &MainWindow::onChangeCarColor);
    
    QAction *changeWheelColorAction = new QAction("Change &Wheel Color", this);
    carMenu->addAction(changeWheelColorAction);
    connect(changeWheelColorAction, &QAction::triggered, this, &MainWindow::onChangeWheelColor);
    
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
    QToolBar *toolbar = addToolBar("Toolbar");
    toolbar->setMovable(false);
    
    toolbar->addAction("Create Rectangle", this, &MainWindow::onCreateRectangle);
    toolbar->addAction("Create Car", this, &MainWindow::onCreateCar);
    toolbar->addSeparator();
    toolbar->addAction("Move Left", this, &MainWindow::onMoveLeft);
    toolbar->addAction("Move Right", this, &MainWindow::onMoveRight);
    toolbar->addAction("Stop", this, &MainWindow::onStopMovement);
    toolbar->addSeparator();
    toolbar->addAction("Left Door", this, &MainWindow::onToggleLeftDoor);
    toolbar->addAction("Right Door", this, &MainWindow::onToggleRightDoor);
    toolbar->addAction("Headlights", this, &MainWindow::onToggleHeadlights);
}

void MainWindow::setupControlPanel()
{
    QDockWidget *dock = new QDockWidget("Control Panel", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    QWidget *dockWidget = new QWidget(dock);
    QVBoxLayout *dockLayout = new QVBoxLayout(dockWidget);
    
    QGroupBox *rectGroup = new QGroupBox("Rectangle Control", dockWidget);
    QGridLayout *rectLayout = new QGridLayout(rectGroup);
    
    QPushButton *btnCreateRect = new QPushButton("Create Rectangle", rectGroup);
    QPushButton *btnCreateCar = new QPushButton("Create Car", rectGroup);
    
    rectLayout->addWidget(btnCreateRect, 0, 0);
    rectLayout->addWidget(btnCreateCar, 0, 1);
    
    QGroupBox *carGroup = new QGroupBox("Car Control", dockWidget);
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
    
    QGroupBox *moveGroup = new QGroupBox("Movement Control", dockWidget);
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
    
    dockLayout->addWidget(rectGroup);
    dockLayout->addWidget(carGroup);
    dockLayout->addWidget(moveGroup);
    dockLayout->addStretch();
    
    dockWidget->setLayout(dockLayout);
    dock->setWidget(dockWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    
    connect(btnCreateRect, &QPushButton::clicked, this, &MainWindow::onCreateRectangle);
    connect(btnCreateCar, &QPushButton::clicked, this, &MainWindow::onCreateCar);
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
    // Обработка ошибок будет подключена при создании автомобиля
}

void MainWindow::onAnimationTimer()
{
    if (m_car) {
        m_car->move();
        m_car->updateAnimation();
    }
    update();
    updateStatus();
}

void MainWindow::updateStatus()
{
    if (!m_car) {
        m_statusLabel->setText("No active object. Create a rectangle or car.");
        return;
    }
    
    QString status = QString("Car | Position: (%1, %2) | Size: %3x%4 | "
                           "Speed: (%5, %6) | Doors: %7%8 | Lights: %9 | State: %10")
        .arg(m_car->getPosition().x())
        .arg(m_car->getPosition().y())
        .arg(m_car->getWidth())
        .arg(m_car->getHeight())
        .arg(m_car->getSpeedX(), 0, 'f', 1)
        .arg(m_car->getSpeedY(), 0, 'f', 1)
        .arg(m_car->isLeftDoorOpen() ? "L-" : "L+")
        .arg(m_car->isRightDoorOpen() ? "R-" : "R+")
        .arg(m_car->areHeadlightsOn() ? "ON" : "OFF")
        .arg(m_car->getCarState() == CAR_MOVING ? "Moving" : 
             m_car->getCarState() == CAR_PARKED ? "Parked" : "Stopped");
    
    m_statusLabel->setText(status);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    if (!m_car) return;
    
    QPixmap pixmap(m_canvas->size());
    pixmap.fill(Qt::white);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    painter.fillRect(0, pixmap.height()/2 - 50, pixmap.width(), 100, QBrush(Qt::darkGray));
    
    painter.setPen(QPen(Qt::yellow, 3, Qt::DashLine));
    for (int i = 0; i < pixmap.width(); i += 40) {
        painter.drawLine(i, pixmap.height()/2, i + 20, pixmap.height()/2);
    }
    
    m_car->draw(painter);
    
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
        onResetPosition();
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
    case Qt::Key_F1:
        onHelp();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::onCreateRectangle()
{
    try {
        int x, y, width, height;
        QColor color;
        
        if (InputDialog::getRectangleParameters(this, x, y, width, height, color)) {
            if (m_car) delete m_car;
            m_car = new Car(QPoint(x, y), width, height, color, this);
            
            connect(m_car, &Car::errorOccurred, this, &MainWindow::onErrorOccurred);
            
            showMessage(QString("Created rectangle: X=%1, Y=%2, W=%3, H=%4, Color=%5")
                       .arg(x).arg(y).arg(width).arg(height).arg(color.name()));
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
            if (m_car) delete m_car;
            m_car = new Car(QPoint(x, y), width, height, color, this);
            
            connect(m_car, &Car::errorOccurred, this, &MainWindow::onErrorOccurred);
            
            showMessage(QString("Created car: X=%1, Y=%2, W=%3, H=%4, Color=%5")
                       .arg(x).arg(y).arg(width).arg(height).arg(color.name()));
        }
    } catch (const std::exception &e) {
        onErrorOccurred(QString("Create car error: %1").arg(e.what()));
    }
}

void MainWindow::onToggleLeftDoor()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->toggleLeftDoor();
    showMessage(QString("Left door: %1").arg(m_car->isLeftDoorOpen() ? "opened" : "closed"));
}

void MainWindow::onToggleRightDoor()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->toggleRightDoor();
    showMessage(QString("Right door: %1").arg(m_car->isRightDoorOpen() ? "opened" : "closed"));
}

void MainWindow::onToggleHeadlights()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->toggleHeadlights();
    showMessage(QString("Headlights: %1").arg(m_car->areHeadlightsOn() ? "on" : "off"));
}

void MainWindow::onOpenAllDoors()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->openAllDoors();
    showMessage("All doors opened");
}

void MainWindow::onCloseAllDoors()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->closeAllDoors();
    showMessage("All doors closed");
}

void MainWindow::onStartEngine()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->startEngine();
    showMessage("Engine started");
}

void MainWindow::onStopEngine()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->stopEngine();
    showMessage("Engine stopped");
}

void MainWindow::onParkCar()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    m_car->park();
    showMessage("Car parked");
}

void MainWindow::onChangeCarColor()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    QColor color = QColorDialog::getColor(m_car->getBodyColor(), this, "Choose Body Color");
    if (color.isValid()) {
        m_car->setBodyColor(color);
        showMessage(QString("Body color changed to: %1").arg(color.name()));
    }
}

void MainWindow::onChangeWheelColor()
{
    if (!m_car) {
        showMessage("First create a car!", true);
        return;
    }
    
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose Wheel Color");
    if (color.isValid()) {
        m_car->setWheelColor(color);
        showMessage(QString("Wheel color changed to: %1").arg(color.name()));
    }
}

void MainWindow::onSaveCar()
{
    if (!m_car) {
        showMessage("No car to save!", true);
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
        if (m_car) delete m_car;
        m_car = new Car(this);
        
        if (m_car->loadFromFile(filename)) {
            connect(m_car, &Car::errorOccurred, this, &MainWindow::onErrorOccurred);
            showMessage(QString("Car loaded from: %1").arg(filename));
        } else {
            delete m_car;
            m_car = nullptr;
        }
    }
}

void MainWindow::onMoveLeft()
{
    if (!m_car) {
        showMessage("First create an object!", true);
        return;
    }
    
    m_car->setSpeed(-2, m_car->getSpeedY());
    showMessage("Moving left");
}

void MainWindow::onMoveRight()
{
    if (!m_car) {
        showMessage("First create an object!", true);
        return;
    }
    
    m_car->setSpeed(2, m_car->getSpeedY());
    showMessage("Moving right");
}

void MainWindow::onMoveUp()
{
    if (!m_car) {
        showMessage("First create an object!", true);
        return;
    }
    
    m_car->setSpeed(m_car->getSpeedX(), -2);
    showMessage("Moving up");
}

void MainWindow::onMoveDown()
{
    if (!m_car) {
        showMessage("First create an object!", true);
        return;
    }
    
    m_car->setSpeed(m_car->getSpeedX(), 2);
    showMessage("Moving down");
}

void MainWindow::onStopMovement()
{
    if (!m_car) {
        showMessage("First create an object!", true);
        return;
    }
    
    m_car->setSpeed(0, 0);
    showMessage("Movement stopped");
}

void MainWindow::onResetPosition()
{
    if (!m_car) {
        showMessage("First create an object!", true);
        return;
    }
    
    m_car->setPosition(QPoint(100, 200));
    m_car->setSpeed(0, 0);
    m_car->closeAllDoors();
    if (m_car->areHeadlightsOn()) {
        m_car->toggleHeadlights();
    }
    m_car->setCarState(CAR_STOPPED);
    
    showMessage("Position reset");
}

void MainWindow::onErrorOccurred(const QString &message)
{
    showMessage(message, true);
    QMessageBox::critical(this, "Error", message);
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "About",
                      "<h3>OOP Demo in Qt/C++</h3>"
                      "<p><b>Laboratory Work: Program development with procedures and records</b></p>"
                      "<p>This program demonstrates OOP principles using inheritance.</p>"
                      "<p>Features:</p>"
                      "<ul>"
                      "<li>Class inheritance</li>"
                      "<li>Encapsulation</li>"
                      "<li>Polymorphism</li>"
                      "<li>Exception handling</li>"
                      "<li>Visual I/O</li>"
                      "</ul>"
                      "<p>Version: 1.0.0</p>");
}

void MainWindow::onHelp()
{
    QMessageBox::information(this, "Help",
                           "<h3>Program Control</h3>"
                           "<p><b>Hotkeys:</b></p>"
                           "<ul>"
                           "<li><b>Ctrl+R</b> - Create rectangle</li>"
                           "<li><b>Ctrl+A</b> - Create car</li>"
                           "<li><b>Arrows</b> - Movement control</li>"
                           "<li><b>Space</b> - Stop movement</li>"
                           "<li><b>R</b> - Reset position</li>"
                           "<li><b>L/P</b> - Left/Right door</li>"
                           "<li><b>H</b> - Headlights</li>"
                           "<li><b>F1</b> - Help</li>"
                           "</ul>"
                           "<p><b>Description:</b></p>"
                           "<p>This program demonstrates OOP principles using a car "
                           "that inherits properties from a movable rectangle.</p>");
}

void MainWindow::showMessage(const QString &message, bool isError)
{
    QString timestamp = QDateTime::currentDateTime().toString("HH:mm:ss");
    QString formatted = QString("[%1] %2").arg(timestamp).arg(message);
    
    if (isError) {
        m_statusLabel->setStyleSheet("background-color: #ffcccc; padding: 5px; border-top: 1px solid #ff0000;");
    } else {
        m_statusLabel->setStyleSheet("background-color: #f0f0f0; padding: 5px; border-top: 1px solid #cccccc;");
    }
    
    m_statusLabel->setText(formatted);
    qDebug() << (isError ? "ERROR:" : "INFO:") << message;
}

// Добавляем недостающие методы
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}

void MainWindow::onLoadRectangle()
{
    showMessage("Load Rectangle not implemented", true);
}

void MainWindow::onMoveRectangle()
{
    showMessage("Move Rectangle not implemented", true);
}

void MainWindow::onSaveRectangle()
{
    showMessage("Save Rectangle not implemented", true);
}

void MainWindow::onChangeRectangleColor()
{
    showMessage("Change Rectangle Color not implemented", true);
}