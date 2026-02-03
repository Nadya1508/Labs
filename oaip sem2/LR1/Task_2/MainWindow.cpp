#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QRandomGenerator>
#include <QDebug>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QSplitter>
#include <QApplication>
#include <QRadioButton>
#include <QButtonGroup>
#include <QShortcut>
#include <QPainter>

// Добавим include для всех классов фигур
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Rhombus.h"
#include "Hexagon.h"
#include "Star.h"
#include "Circle.h"
#include "CustomFigure.h"
#include "PolygonFigure.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_canvas(new FigureCanvas(this))
    , m_currentFigure(nullptr)
    , m_currentLineColor(Qt::blue)
    , m_currentFillColor(Qt::lightGray)
{
    setupUI();
    setupMenuBar();
    setupToolBar();
    setupDockWidgets();
    setupStatusBar();
    createConnections();
    
    // Create some default figures
    createFigureByType("Triangle", QPointF(200, 200));
    createFigureByType("Circle", QPointF(400, 300));
    createFigureByType("Star", QPointF(600, 400));
    createFigureByType("Square", QPointF(300, 500));
    
    // Update UI
    updateFigureList();
    if (m_figureList->count() > 0)
    {
        m_figureList->setCurrentRow(0);
    }
    
    // Setup update timer
    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(100);
    connect(m_updateTimer, &QTimer::timeout, m_canvas, qOverload<>(&FigureCanvas::update));
    m_updateTimer->start();
    
    resize(1400, 900);
    setWindowTitle("Geometry Figures Application");
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    setCentralWidget(m_canvas);
}

void MainWindow::setupMenuBar()
{
    // File menu
    m_fileMenu = menuBar()->addMenu("&File");
    
    QAction *newAction = new QAction("&New Project", this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setIcon(QIcon::fromTheme("document-new"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    m_fileMenu->addAction(newAction);
    
    QAction *openAction = new QAction("&Open...", this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setIcon(QIcon::fromTheme("document-open"));
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    m_fileMenu->addAction(openAction);
    
    QAction *saveAction = new QAction("&Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon::fromTheme("document-save"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    m_fileMenu->addAction(saveAction);
    
    QAction *saveAsAction = new QAction("Save &As...", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFile);
    m_fileMenu->addAction(saveAsAction);
    
    m_fileMenu->addSeparator();
    
    QAction *exportAction = new QAction("&Export Image...", this);
    exportAction->setIcon(QIcon::fromTheme("document-export"));
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportImage);
    m_fileMenu->addAction(exportAction);
    
    m_fileMenu->addSeparator();
    
    QAction *exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setIcon(QIcon::fromTheme("application-exit"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApplication);
    m_fileMenu->addAction(exitAction);
    
    // Edit menu
    m_editMenu = menuBar()->addMenu("&Edit");
    
    QAction *copyAction = new QAction("&Copy", this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setIcon(QIcon::fromTheme("edit-copy"));
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyFigure);
    m_editMenu->addAction(copyAction);
    
    QAction *pasteAction = new QAction("&Paste", this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setIcon(QIcon::fromTheme("edit-paste"));
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteFigure);
    m_editMenu->addAction(pasteAction);
    
    QAction *deleteAction = new QAction("&Delete", this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setIcon(QIcon::fromTheme("edit-delete"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteFigure);
    m_editMenu->addAction(deleteAction);
    
    m_editMenu->addSeparator();
    
    QAction *selectAllAction = new QAction("Select &All", this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    connect(selectAllAction, &QAction::triggered, this, &MainWindow::selectAll);
    m_editMenu->addAction(selectAllAction);
    
    QAction *deselectAllAction = new QAction("&Deselect All", this);
    deselectAllAction->setShortcut(QKeySequence("Ctrl+Shift+A"));
    connect(deselectAllAction, &QAction::triggered, this, &MainWindow::deselectAll);
    m_editMenu->addAction(deselectAllAction);
    
    // View menu
    m_viewMenu = menuBar()->addMenu("&View");
    
    QAction *zoomInAction = new QAction("Zoom &In", this);
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    zoomInAction->setIcon(QIcon::fromTheme("zoom-in"));
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    m_viewMenu->addAction(zoomInAction);
    
    QAction *zoomOutAction = new QAction("Zoom &Out", this);
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    zoomOutAction->setIcon(QIcon::fromTheme("zoom-out"));
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    m_viewMenu->addAction(zoomOutAction);
    
    QAction *resetViewAction = new QAction("&Reset View", this);
    resetViewAction->setShortcut(QKeySequence("Ctrl+R"));
    resetViewAction->setIcon(QIcon::fromTheme("view-refresh"));
    connect(resetViewAction, &QAction::triggered, this, &MainWindow::resetView);
    m_viewMenu->addAction(resetViewAction);
    
    QAction *fitViewAction = new QAction("&Fit to View", this);
    fitViewAction->setShortcut(QKeySequence("Ctrl+F"));
    fitViewAction->setIcon(QIcon::fromTheme("zoom-fit-best"));
    connect(fitViewAction, &QAction::triggered, this, &MainWindow::fitToView);
    m_viewMenu->addAction(fitViewAction);
    
    m_viewMenu->addSeparator();
    
    QAction *gridAction = new QAction("Show &Grid", this);
    gridAction->setCheckable(true);
    gridAction->setChecked(true);
    gridAction->setShortcut(QKeySequence("Ctrl+G"));
    connect(gridAction, &QAction::toggled, this, &MainWindow::toggleGrid);
    m_viewMenu->addAction(gridAction);
    
    QAction *centersAction = new QAction("Show &Centers", this);
    centersAction->setCheckable(true);
    centersAction->setChecked(true);
    centersAction->setShortcut(QKeySequence("Ctrl+C"));
    connect(centersAction, &QAction::toggled, this, &MainWindow::toggleCenters);
    m_viewMenu->addAction(centersAction);
    
    QAction *verticesAction = new QAction("Show &Vertices", this);
    verticesAction->setCheckable(true);
    verticesAction->setChecked(true);
    verticesAction->setShortcut(QKeySequence("Ctrl+V"));
    connect(verticesAction, &QAction::toggled, this, &MainWindow::toggleVertices);
    m_viewMenu->addAction(verticesAction);
    
    QAction *bboxAction = new QAction("Show &Bounding Boxes", this);
    bboxAction->setCheckable(true);
    bboxAction->setChecked(false);
    bboxAction->setShortcut(QKeySequence("Ctrl+B"));
    connect(bboxAction, &QAction::toggled, this, &MainWindow::toggleBoundingBox);
    m_viewMenu->addAction(bboxAction);
    
    QAction *triangulationAction = new QAction("Show &Triangulation", this);
    triangulationAction->setCheckable(true);
    triangulationAction->setChecked(false);
    triangulationAction->setShortcut(QKeySequence("Ctrl+T"));
    connect(triangulationAction, &QAction::toggled, this, &MainWindow::toggleTriangulation);
    m_viewMenu->addAction(triangulationAction);
    
    QAction *snapAction = new QAction("&Snap to Grid", this);
    snapAction->setCheckable(true);
    snapAction->setChecked(false);
    snapAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(snapAction, &QAction::toggled, this, &MainWindow::toggleSnapToGrid);
    m_viewMenu->addAction(snapAction);
    
    m_viewMenu->addSeparator();
    
    QAction *fullScreenAction = new QAction("&Full Screen", this);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);
    connect(fullScreenAction, &QAction::triggered, this, &MainWindow::showFullScreen);
    m_viewMenu->addAction(fullScreenAction);
    
    // Figure menu
    m_figureMenu = menuBar()->addMenu("&Figure");
    
    QStringList figureTypes = {"Triangle", "Rectangle", "Square", "Rhombus", 
                              "Hexagon", "Star", "Circle", "Polygon"};
    
    for (const QString &type : figureTypes)
    {
        QAction *action = new QAction(type, this);
        connect(action, &QAction::triggered, this, [this, type]() {
            createFigureFromType(type);
        });
        m_figureMenu->addAction(action);
    }
    
    m_figureMenu->addSeparator();
    
    QAction *clearAction = new QAction("&Clear All Figures", this);
    clearAction->setIcon(QIcon::fromTheme("edit-clear"));
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearAllFigures);
    m_figureMenu->addAction(clearAction);
    
    // Drawing menu
    m_drawingMenu = menuBar()->addMenu("&Drawing");
    
    m_drawTriangleAction = new QAction("Draw &Triangle", this);
    m_drawTriangleAction->setCheckable(true);
    m_drawTriangleAction->setShortcut(QKeySequence("Alt+T"));
    connect(m_drawTriangleAction, &QAction::triggered, this, &MainWindow::setDrawTriangleMode);
    m_drawingMenu->addAction(m_drawTriangleAction);
    
    m_drawRectangleAction = new QAction("Draw &Rectangle", this);
    m_drawRectangleAction->setCheckable(true);
    m_drawRectangleAction->setShortcut(QKeySequence("Alt+R"));
    connect(m_drawRectangleAction, &QAction::triggered, this, &MainWindow::setDrawRectangleMode);
    m_drawingMenu->addAction(m_drawRectangleAction);
    
    m_drawSquareAction = new QAction("Draw S&quare", this);
    m_drawSquareAction->setCheckable(true);
    m_drawSquareAction->setShortcut(QKeySequence("Alt+Q"));
    connect(m_drawSquareAction, &QAction::triggered, this, &MainWindow::setDrawSquareMode);
    m_drawingMenu->addAction(m_drawSquareAction);
    
    m_drawCircleAction = new QAction("Draw &Circle", this);
    m_drawCircleAction->setCheckable(true);
    m_drawCircleAction->setShortcut(QKeySequence("Alt+C"));
    connect(m_drawCircleAction, &QAction::triggered, this, &MainWindow::setDrawCircleMode);
    m_drawingMenu->addAction(m_drawCircleAction);
    
    m_drawRhombusAction = new QAction("Draw Rh&ombus", this);
    m_drawRhombusAction->setCheckable(true);
    m_drawRhombusAction->setShortcut(QKeySequence("Alt+O"));
    connect(m_drawRhombusAction, &QAction::triggered, this, &MainWindow::setDrawRhombusMode);
    m_drawingMenu->addAction(m_drawRhombusAction);
    
    m_drawHexagonAction = new QAction("Draw &Hexagon", this);
    m_drawHexagonAction->setCheckable(true);
    m_drawHexagonAction->setShortcut(QKeySequence("Alt+H"));
    connect(m_drawHexagonAction, &QAction::triggered, this, &MainWindow::setDrawHexagonMode);
    m_drawingMenu->addAction(m_drawHexagonAction);
    
    m_drawStarAction = new QAction("Draw &Star", this);
    m_drawStarAction->setCheckable(true);
    m_drawStarAction->setShortcut(QKeySequence("Alt+S"));
    connect(m_drawStarAction, &QAction::triggered, this, &MainWindow::setDrawStarMode);
    m_drawingMenu->addAction(m_drawStarAction);
    
    m_drawPolygonAction = new QAction("Draw &Polygon", this);
    m_drawPolygonAction->setCheckable(true);
    m_drawPolygonAction->setShortcut(QKeySequence("Alt+P"));
    connect(m_drawPolygonAction, &QAction::triggered, this, &MainWindow::setDrawPolygonMode);
    m_drawingMenu->addAction(m_drawPolygonAction);
    
    m_drawingMenu->addSeparator();
    
    m_stopDrawingAction = new QAction("&Stop Drawing", this);
    m_stopDrawingAction->setShortcut(QKeySequence("Escape"));
    m_stopDrawingAction->setIcon(QIcon::fromTheme("process-stop"));
    connect(m_stopDrawingAction, &QAction::triggered, this, &MainWindow::stopDrawingMode);
    m_drawingMenu->addAction(m_stopDrawingAction);
    
    // Transform menu
    m_transformMenu = menuBar()->addMenu("&Transform");
    
    QAction *applyTransformAction = new QAction("&Apply Transformations", this);
    applyTransformAction->setShortcut(QKeySequence("Ctrl+T"));
    applyTransformAction->setIcon(QIcon::fromTheme("transform-move"));
    connect(applyTransformAction, &QAction::triggered, this, &MainWindow::applyTransformation);
    m_transformMenu->addAction(applyTransformAction);
    
    QAction *animateTransformAction = new QAction("&Animate Transformations", this);
    animateTransformAction->setShortcut(QKeySequence("Ctrl+Shift+T"));
    animateTransformAction->setIcon(QIcon::fromTheme("media-playback-start"));
    connect(animateTransformAction, &QAction::triggered, this, &MainWindow::animateTransformation);
    m_transformMenu->addAction(animateTransformAction);
    
    m_transformMenu->addSeparator();
    
    QAction *calculateAreaAction = new QAction("Calculate &Total Area", this);
    calculateAreaAction->setIcon(QIcon::fromTheme("calculator"));
    connect(calculateAreaAction, &QAction::triggered, this, &MainWindow::calculateTotalArea);
    m_transformMenu->addAction(calculateAreaAction);
    
    QAction *calculatePerimeterAction = new QAction("Calculate Total &Perimeter", this);
    calculatePerimeterAction->setIcon(QIcon::fromTheme("calculator"));
    connect(calculatePerimeterAction, &QAction::triggered, this, &MainWindow::calculateTotalPerimeter);
    m_transformMenu->addAction(calculatePerimeterAction);
    
    // Help menu
    m_helpMenu = menuBar()->addMenu("&Help");
    
    QAction *helpAction = new QAction("&Help Contents", this);
    helpAction->setShortcut(QKeySequence::HelpContents);
    helpAction->setIcon(QIcon::fromTheme("help-contents"));
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelp);
    m_helpMenu->addAction(helpAction);
    
    QAction *shortcutsAction = new QAction("&Keyboard Shortcuts", this);
    shortcutsAction->setShortcut(QKeySequence("Ctrl+K"));
    connect(shortcutsAction, &QAction::triggered, this, &MainWindow::showShortcuts);
    m_helpMenu->addAction(shortcutsAction);
    
    m_helpMenu->addSeparator();
    
    QAction *aboutAction = new QAction("&About", this);
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    m_helpMenu->addAction(aboutAction);
}

void MainWindow::setupToolBar()
{
    // Main toolbar - только базовые инструменты (без кнопок создания фигур)
    m_mainToolBar = addToolBar("Main Toolbar");
    m_mainToolBar->setMovable(false);
    
    // Кнопки трансформации
    QAction *moveAction = new QAction("Move", this);
    moveAction->setToolTip("Move selected figure");
    moveAction->setIcon(QIcon::fromTheme("transform-move"));
    connect(moveAction, &QAction::triggered, this, [this]() {
        if (m_currentFigure)
        {
            QPointF offset(m_moveXSpinBox->value(), m_moveYSpinBox->value());
            m_currentFigure->move(offset);
        }
    });
    m_mainToolBar->addAction(moveAction);
    
    QAction *rotateAction = new QAction("Rotate", this);
    rotateAction->setToolTip("Rotate selected figure");
    rotateAction->setIcon(QIcon::fromTheme("object-rotate-right"));
    connect(rotateAction, &QAction::triggered, this, [this]() {
        if (m_currentFigure)
        {
            double angle = m_rotateAngleSpinBox->value();
            QPointF center(m_rotateCenterXSpinBox->value(), m_rotateCenterYSpinBox->value());
            m_currentFigure->rotate(angle, center);
        }
    });
    m_mainToolBar->addAction(rotateAction);
    
    QAction *scaleAction = new QAction("Scale", this);
    scaleAction->setToolTip("Scale selected figure");
    scaleAction->setIcon(QIcon::fromTheme("transform-scale"));
    connect(scaleAction, &QAction::triggered, this, [this]() {
        if (m_currentFigure)
        {
            double factor = m_scaleFactorSpinBox->value();
            QPointF center(m_scaleCenterXSpinBox->value(), m_scaleCenterYSpinBox->value());
            m_currentFigure->scale(factor, center);
        }
    });
    m_mainToolBar->addAction(scaleAction);
    
    m_mainToolBar->addSeparator();
    
    // Кнопки управления
    QAction *zoomInAction = new QAction("Zoom In", this);
    zoomInAction->setIcon(QIcon::fromTheme("zoom-in"));
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    m_mainToolBar->addAction(zoomInAction);
    
    QAction *zoomOutAction = new QAction("Zoom Out", this);
    zoomOutAction->setIcon(QIcon::fromTheme("zoom-out"));
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    m_mainToolBar->addAction(zoomOutAction);
    
    QAction *resetViewAction = new QAction("Reset View", this);
    resetViewAction->setIcon(QIcon::fromTheme("view-refresh"));
    connect(resetViewAction, &QAction::triggered, this, &MainWindow::resetView);
    m_mainToolBar->addAction(resetViewAction);
    
    // Drawing toolbar
    m_drawingToolBar = addToolBar("Drawing Tools");
    m_drawingToolBar->setMovable(false);
    
    // Drawing mode buttons
    m_drawTriangleAction->setIcon(QIcon::fromTheme("draw-triangle"));
    m_drawTriangleAction->setToolTip("Draw Triangle (Alt+T)");
    m_drawingToolBar->addAction(m_drawTriangleAction);
    
    m_drawRectangleAction->setIcon(QIcon::fromTheme("draw-rectangle"));
    m_drawRectangleAction->setToolTip("Draw Rectangle (Alt+R)");
    m_drawingToolBar->addAction(m_drawRectangleAction);
    
    m_drawSquareAction->setIcon(QIcon::fromTheme("draw-square"));
    m_drawSquareAction->setToolTip("Draw Square (Alt+Q)");
    m_drawingToolBar->addAction(m_drawSquareAction);
    
    m_drawCircleAction->setIcon(QIcon::fromTheme("draw-circle"));
    m_drawCircleAction->setToolTip("Draw Circle (Alt+C)");
    m_drawingToolBar->addAction(m_drawCircleAction);
    
    m_drawRhombusAction->setIcon(QIcon::fromTheme("draw-polygon"));
    m_drawRhombusAction->setToolTip("Draw Rhombus (Alt+O)");
    m_drawingToolBar->addAction(m_drawRhombusAction);
    
    m_drawHexagonAction->setIcon(QIcon::fromTheme("draw-polygon"));
    m_drawHexagonAction->setToolTip("Draw Hexagon (Alt+H)");
    m_drawingToolBar->addAction(m_drawHexagonAction);
    
    m_drawStarAction->setIcon(QIcon::fromTheme("draw-star"));
    m_drawStarAction->setToolTip("Draw Star (Alt+S)");
    m_drawingToolBar->addAction(m_drawStarAction);
    
    m_drawPolygonAction->setIcon(QIcon::fromTheme("draw-polygon"));
    m_drawPolygonAction->setToolTip("Draw Polygon (Alt+P)");
    m_drawingToolBar->addAction(m_drawPolygonAction);
    
    m_drawingToolBar->addSeparator();
    
    m_stopDrawingAction->setIcon(QIcon::fromTheme("process-stop"));
    m_stopDrawingAction->setToolTip("Stop Drawing (Esc)");
    m_drawingToolBar->addAction(m_stopDrawingAction);
    
    // Create action group for exclusive drawing modes
    QActionGroup *drawingGroup = new QActionGroup(this);
    drawingGroup->addAction(m_drawTriangleAction);
    drawingGroup->addAction(m_drawRectangleAction);
    drawingGroup->addAction(m_drawSquareAction);
    drawingGroup->addAction(m_drawCircleAction);
    drawingGroup->addAction(m_drawRhombusAction);
    drawingGroup->addAction(m_drawHexagonAction);
    drawingGroup->addAction(m_drawStarAction);
    drawingGroup->addAction(m_drawPolygonAction);
    drawingGroup->setExclusive(true);
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Ready");
    statusBar()->addWidget(m_statusLabel);
    
    m_mousePositionLabel = new QLabel("Mouse: (0, 0)");
    statusBar()->addPermanentWidget(m_mousePositionLabel);
    
    m_drawingModeLabel = new QLabel("Mode: Selection");
    statusBar()->addPermanentWidget(m_drawingModeLabel);
    
    statusBar()->showMessage("Geometry Figures Application Ready", 3000);
}

void MainWindow::setupDockWidgets()
{
    // Figures dock (left)
    m_figuresDock = new QDockWidget("Figures", this);
    m_figuresDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    QWidget *figuresWidget = new QWidget();
    QVBoxLayout *figuresLayout = new QVBoxLayout(figuresWidget);
    
    // Figure creation controls
    QGroupBox *creationGroup = new QGroupBox("Create Figure");
    QVBoxLayout *creationLayout = new QVBoxLayout();
    
    m_figureTypeCombo = new QComboBox();
    m_figureTypeCombo->addItems({"Triangle", "Rectangle", "Square", "Rhombus", 
                                 "Hexagon", "Star", "Circle", "Polygon"});
    creationLayout->addWidget(m_figureTypeCombo);
    
    QPushButton *createButton = new QPushButton("Create Figure");
    createButton->setStyleSheet("QPushButton { padding: 8px; font-weight: bold; }");
    connect(createButton, &QPushButton::clicked, this, &MainWindow::createFigure);
    creationLayout->addWidget(createButton);
    
    QPushButton *createAtCenterButton = new QPushButton("Create at Center");
    connect(createAtCenterButton, &QPushButton::clicked, this, [this]() {
        createFigureByType(m_figureTypeCombo->currentText(), 
                          QPointF(m_canvas->width()/2.0, m_canvas->height()/2.0));
    });
    creationLayout->addWidget(createAtCenterButton);
    
    QPushButton *createRandomButton = new QPushButton("Create Random");
    connect(createRandomButton, &QPushButton::clicked, this, [this]() {
        int x = 100 + QRandomGenerator::global()->bounded(600);
        int y = 100 + QRandomGenerator::global()->bounded(400);
        createFigureByType(m_figureTypeCombo->currentText(), QPointF(x, y));
    });
    creationLayout->addWidget(createRandomButton);
    
    creationGroup->setLayout(creationLayout);
    figuresLayout->addWidget(creationGroup);
    
    // Drawing controls
    m_drawingControlsGroup = new QGroupBox("Drawing Mode");
    QVBoxLayout *drawingLayout = new QVBoxLayout();
    
    m_drawingButtonGroup = new QButtonGroup(this);
    
    m_noDrawingRadio = new QRadioButton("No Drawing (Select)");
    m_noDrawingRadio->setChecked(true);
    m_drawingButtonGroup->addButton(m_noDrawingRadio, 0);
    drawingLayout->addWidget(m_noDrawingRadio);
    
    m_drawTriangleRadio = new QRadioButton("Draw Triangle");
    m_drawingButtonGroup->addButton(m_drawTriangleRadio, 1);
    drawingLayout->addWidget(m_drawTriangleRadio);
    
    m_drawRectangleRadio = new QRadioButton("Draw Rectangle");
    m_drawingButtonGroup->addButton(m_drawRectangleRadio, 2);
    drawingLayout->addWidget(m_drawRectangleRadio);
    
    m_drawSquareRadio = new QRadioButton("Draw Square");
    m_drawingButtonGroup->addButton(m_drawSquareRadio, 3);
    drawingLayout->addWidget(m_drawSquareRadio);
    
    m_drawCircleRadio = new QRadioButton("Draw Circle");
    m_drawingButtonGroup->addButton(m_drawCircleRadio, 4);
    drawingLayout->addWidget(m_drawCircleRadio);
    
    m_drawRhombusRadio = new QRadioButton("Draw Rhombus");
    m_drawingButtonGroup->addButton(m_drawRhombusRadio, 5);
    drawingLayout->addWidget(m_drawRhombusRadio);
    
    m_drawHexagonRadio = new QRadioButton("Draw Hexagon");
    m_drawingButtonGroup->addButton(m_drawHexagonRadio, 6);
    drawingLayout->addWidget(m_drawHexagonRadio);
    
    m_drawStarRadio = new QRadioButton("Draw Star");
    m_drawingButtonGroup->addButton(m_drawStarRadio, 7);
    drawingLayout->addWidget(m_drawStarRadio);
    
    m_drawPolygonRadio = new QRadioButton("Draw Polygon");
    m_drawingButtonGroup->addButton(m_drawPolygonRadio, 8);
    drawingLayout->addWidget(m_drawPolygonRadio);
    
    // Исправим подключение сигнала
    connect(m_drawingButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, [this](QAbstractButton *button) {
        int id = m_drawingButtonGroup->id(button);
        switch(id) {
            case 0: m_canvas->setDrawingMode(DrawingTool::NoDrawing); break;
            case 1: m_canvas->setDrawingMode(DrawingTool::DrawTriangle); break;
            case 2: m_canvas->setDrawingMode(DrawingTool::DrawRectangle); break;
            case 3: m_canvas->setDrawingMode(DrawingTool::DrawSquare); break;
            case 4: m_canvas->setDrawingMode(DrawingTool::DrawCircle); break;
            case 5: m_canvas->setDrawingMode(DrawingTool::DrawRhombus); break;
            case 6: m_canvas->setDrawingMode(DrawingTool::DrawHexagon); break;
            case 7: m_canvas->setDrawingMode(DrawingTool::DrawStar); break;
            case 8: m_canvas->setDrawingMode(DrawingTool::DrawPolygon); break;
        }
        updateDrawingControls();
    });
    
    m_drawingControlsGroup->setLayout(drawingLayout);
    figuresLayout->addWidget(m_drawingControlsGroup);
    
    // Figure list
    QGroupBox *listGroup = new QGroupBox("Figure List");
    QVBoxLayout *listLayout = new QVBoxLayout();
    
    m_figureList = new QListWidget();
    m_figureList->setSelectionMode(QListWidget::SingleSelection);
    connect(m_figureList, &QListWidget::currentRowChanged, 
            this, &MainWindow::updateSelectedFigure);
    
    listLayout->addWidget(m_figureList);
    
    QHBoxLayout *listButtonsLayout = new QHBoxLayout();
    QPushButton *removeButton = new QPushButton("Remove");
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeSelectedFigure);
    listButtonsLayout->addWidget(removeButton);
    
    QPushButton *clearButton = new QPushButton("Clear All");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearAllFigures);
    listButtonsLayout->addWidget(clearButton);
    
    QPushButton *statisticsButton = new QPushButton("Statistics");
    connect(statisticsButton, &QPushButton::clicked, this, &MainWindow::showFigureStatistics);
    listButtonsLayout->addWidget(statisticsButton);
    
    listLayout->addLayout(listButtonsLayout);
    listGroup->setLayout(listLayout);
    figuresLayout->addWidget(listGroup);
    
    figuresLayout->addStretch();
    m_figuresDock->setWidget(figuresWidget);
    addDockWidget(Qt::LeftDockWidgetArea, m_figuresDock);
    
    // Properties dock (right)
    m_propertiesDock = new QDockWidget("Properties", this);
    m_propertiesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    QWidget *propertiesWidget = new QWidget();
    QVBoxLayout *propertiesLayout = new QVBoxLayout(propertiesWidget);
    
    // Style properties
    QGroupBox *styleGroup = new QGroupBox("Style");
    QFormLayout *styleLayout = new QFormLayout();
    
    m_lineColorButton = new QPushButton("Line Color");
    m_lineColorButton->setStyleSheet("background-color: blue; color: white; padding: 5px;");
    connect(m_lineColorButton, &QPushButton::clicked, this, &MainWindow::chooseLineColor);
    styleLayout->addRow("Line Color:", m_lineColorButton);
    
    m_fillColorButton = new QPushButton("Fill Color");
    m_fillColorButton->setStyleSheet("background-color: lightgray; padding: 5px;");
    connect(m_fillColorButton, &QPushButton::clicked, this, &MainWindow::chooseFillColor);
    styleLayout->addRow("Fill Color:", m_fillColorButton);
    
    m_lineWidthSpinBox = new QSpinBox();
    m_lineWidthSpinBox->setRange(1, 10);
    m_lineWidthSpinBox->setValue(2);
    connect(m_lineWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &MainWindow::updateLineWidth);
    styleLayout->addRow("Line Width:", m_lineWidthSpinBox);
    
    styleGroup->setLayout(styleLayout);
    propertiesLayout->addWidget(styleGroup);
    
    // Specific parameters (tabbed)
    QGroupBox *paramsGroup = new QGroupBox("Figure Parameters");
    QVBoxLayout *paramsLayout = new QVBoxLayout();
    
    m_paramTabs = new QTabWidget();
    
    // Circle parameters
    m_circleParams = new QWidget();
    QFormLayout *circleLayout = new QFormLayout(m_circleParams);
    m_radiusSpinBox = new QDoubleSpinBox();
    m_radiusSpinBox->setRange(10, 500);
    m_radiusSpinBox->setValue(50);
    m_radiusSpinBox->setSuffix(" px");
    circleLayout->addRow("Radius:", m_radiusSpinBox);
    m_paramTabs->addTab(m_circleParams, "Circle");
    
    // Rectangle parameters
    m_rectangleParams = new QWidget();
    QFormLayout *rectLayout = new QFormLayout(m_rectangleParams);
    m_widthSpinBox = new QDoubleSpinBox();
    m_widthSpinBox->setRange(10, 500);
    m_widthSpinBox->setValue(100);
    m_widthSpinBox->setSuffix(" px");
    rectLayout->addRow("Width:", m_widthSpinBox);
    
    m_heightSpinBox = new QDoubleSpinBox();
    m_heightSpinBox->setRange(10, 500);
    m_heightSpinBox->setValue(80);
    m_heightSpinBox->setSuffix(" px");
    rectLayout->addRow("Height:", m_heightSpinBox);
    m_paramTabs->addTab(m_rectangleParams, "Rectangle");
    
    // Square parameters
    m_squareParams = new QWidget();
    QFormLayout *squareLayout = new QFormLayout(m_squareParams);
    m_sideSpinBox = new QDoubleSpinBox();
    m_sideSpinBox->setRange(10, 500);
    m_sideSpinBox->setValue(80);
    m_sideSpinBox->setSuffix(" px");
    squareLayout->addRow("Side:", m_sideSpinBox);
    m_paramTabs->addTab(m_squareParams, "Square");
    
    // Rhombus parameters
    m_rhombusParams = new QWidget();
    QFormLayout *rhombusLayout = new QFormLayout(m_rhombusParams);
    m_diag1SpinBox = new QDoubleSpinBox();
    m_diag1SpinBox->setRange(10, 500);
    m_diag1SpinBox->setValue(80);
    m_diag1SpinBox->setSuffix(" px");
    rhombusLayout->addRow("Diagonal 1:", m_diag1SpinBox);
    
    m_diag2SpinBox = new QDoubleSpinBox();
    m_diag2SpinBox->setRange(10, 500);
    m_diag2SpinBox->setValue(60);
    m_diag2SpinBox->setSuffix(" px");
    rhombusLayout->addRow("Diagonal 2:", m_diag2SpinBox);
    m_paramTabs->addTab(m_rhombusParams, "Rhombus");
    
    // Polygon parameters
    m_polygonParams = new QWidget();
    QFormLayout *polygonLayout = new QFormLayout(m_polygonParams);
    m_sidesSpinBox = new QSpinBox();
    m_sidesSpinBox->setRange(3, 20);
    m_sidesSpinBox->setValue(7);
    polygonLayout->addRow("Sides:", m_sidesSpinBox);
    m_paramTabs->addTab(m_polygonParams, "Polygon");
    
    // Star parameters
    m_starParams = new QWidget();
    QFormLayout *starLayout = new QFormLayout(m_starParams);
    m_starTypeCombo = new QComboBox();
    m_starTypeCombo->addItems({"5-pointed", "6-pointed", "8-pointed"});
    starLayout->addRow("Type:", m_starTypeCombo);
    
    m_outerRadiusSpinBox = new QDoubleSpinBox();
    m_outerRadiusSpinBox->setRange(10, 500);
    m_outerRadiusSpinBox->setValue(50);
    m_outerRadiusSpinBox->setSuffix(" px");
    starLayout->addRow("Outer Radius:", m_outerRadiusSpinBox);
    
    m_innerRadiusSpinBox = new QDoubleSpinBox();
    m_innerRadiusSpinBox->setRange(5, 250);
    m_innerRadiusSpinBox->setValue(25);
    m_innerRadiusSpinBox->setSuffix(" px");
    starLayout->addRow("Inner Radius:", m_innerRadiusSpinBox);
    m_paramTabs->addTab(m_starParams, "Star");
    
    // Triangle parameters
    m_triangleParams = new QWidget();
    QFormLayout *triangleLayout = new QFormLayout(m_triangleParams);
    m_triangleBaseSpinBox = new QDoubleSpinBox();
    m_triangleBaseSpinBox->setRange(10, 500);
    m_triangleBaseSpinBox->setValue(100);
    m_triangleBaseSpinBox->setSuffix(" px");
    triangleLayout->addRow("Base:", m_triangleBaseSpinBox);
    
    m_triangleHeightSpinBox = new QDoubleSpinBox();
    m_triangleHeightSpinBox->setRange(10, 500);
    m_triangleHeightSpinBox->setValue(80);
    m_triangleHeightSpinBox->setSuffix(" px");
    triangleLayout->addRow("Height:", m_triangleHeightSpinBox);
    m_paramTabs->addTab(m_triangleParams, "Triangle");
    
    // Hexagon parameters
    m_hexagonParams = new QWidget();
    QFormLayout *hexagonLayout = new QFormLayout(m_hexagonParams);
    QDoubleSpinBox *hexagonRadiusSpinBox = new QDoubleSpinBox();
    hexagonRadiusSpinBox->setRange(10, 500);
    hexagonRadiusSpinBox->setValue(70);
    hexagonRadiusSpinBox->setSuffix(" px");
    hexagonLayout->addRow("Radius:", hexagonRadiusSpinBox);
    m_paramTabs->addTab(m_hexagonParams, "Hexagon");
    
    paramsLayout->addWidget(m_paramTabs);
    
    QPushButton *updateParamsButton = new QPushButton("Update Parameters");
    connect(updateParamsButton, &QPushButton::clicked, 
            this, &MainWindow::updateSpecificParameter);
    paramsLayout->addWidget(updateParamsButton);
    
    paramsGroup->setLayout(paramsLayout);
    propertiesLayout->addWidget(paramsGroup);
    
    // Vertex control
    m_vertexGroup = new QGroupBox("Vertex Control");
    QFormLayout *vertexLayout = new QFormLayout();
    
    m_vertexIndexSpinBox = new QSpinBox();
    m_vertexIndexSpinBox->setRange(0, 0);
    m_vertexIndexSpinBox->setValue(0);
    vertexLayout->addRow("Vertex Index:", m_vertexIndexSpinBox);
    
    m_vertexXSpinBox = new QDoubleSpinBox();
    m_vertexXSpinBox->setRange(-1000, 1000);
    m_vertexXSpinBox->setValue(0);
    vertexLayout->addRow("Vertex X:", m_vertexXSpinBox);
    
    m_vertexYSpinBox = new QDoubleSpinBox();
    m_vertexYSpinBox->setRange(-1000, 1000);
    m_vertexYSpinBox->setValue(0);
    vertexLayout->addRow("Vertex Y:", m_vertexYSpinBox);
    
    QPushButton *updateVertexButton = new QPushButton("Update Vertex");
    connect(updateVertexButton, &QPushButton::clicked, this, [this]() {
        if (m_currentFigure) {
            if (PolygonFigure *polygon = dynamic_cast<PolygonFigure*>(m_currentFigure)) {
                int index = m_vertexIndexSpinBox->value();
                QPointF point(m_vertexXSpinBox->value(), m_vertexYSpinBox->value());
                polygon->setVertex(index, point);
                updateFigureInfo();
                m_canvas->update();
                statusBar()->showMessage("Vertex updated", 2000);
            }
        }
    });
    vertexLayout->addRow(updateVertexButton);
    
    m_vertexGroup->setLayout(vertexLayout);
    propertiesLayout->addWidget(m_vertexGroup);
    
    // Center control
    QGroupBox *centerGroup = new QGroupBox("Center Control");
    QFormLayout *centerLayout = new QFormLayout();
    
    m_newCenterXSpinBox = new QDoubleSpinBox();
    m_newCenterXSpinBox->setRange(-1000, 1000);
    m_newCenterXSpinBox->setValue(300);
    centerLayout->addRow("Center X:", m_newCenterXSpinBox);
    
    m_newCenterYSpinBox = new QDoubleSpinBox();
    m_newCenterYSpinBox->setRange(-1000, 1000);
    m_newCenterYSpinBox->setValue(300);
    centerLayout->addRow("Center Y:", m_newCenterYSpinBox);
    
    QPushButton *moveCenterButton = new QPushButton("Move Center");
    connect(moveCenterButton, &QPushButton::clicked, this, &MainWindow::moveCenterToPoint);
    centerLayout->addRow(moveCenterButton);
    
    centerGroup->setLayout(centerLayout);
    propertiesLayout->addWidget(centerGroup);
    
    propertiesLayout->addStretch();
    m_propertiesDock->setWidget(propertiesWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);
    
    // Transformations dock (right, below properties)
    m_transformationsDock = new QDockWidget("Transformations", this);
    m_transformationsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    QWidget *transformWidget = new QWidget();
    QVBoxLayout *transformLayout = new QVBoxLayout(transformWidget);
    
    // Move transformation
    QGroupBox *moveGroup = new QGroupBox("Move");
    QFormLayout *moveForm = new QFormLayout();
    m_moveXSpinBox = new QDoubleSpinBox();
    m_moveXSpinBox->setRange(-500, 500);
    m_moveXSpinBox->setValue(20);
    m_moveXSpinBox->setSuffix(" px");
    moveForm->addRow("Offset X:", m_moveXSpinBox);
    
    m_moveYSpinBox = new QDoubleSpinBox();
    m_moveYSpinBox->setRange(-500, 500);
    m_moveYSpinBox->setValue(20);
    m_moveYSpinBox->setSuffix(" px");
    moveForm->addRow("Offset Y:", m_moveYSpinBox);
    moveGroup->setLayout(moveForm);
    transformLayout->addWidget(moveGroup);
    
    // Rotate transformation
    QGroupBox *rotateGroup = new QGroupBox("Rotate");
    QFormLayout *rotateForm = new QFormLayout();
    m_rotateAngleSpinBox = new QDoubleSpinBox();
    m_rotateAngleSpinBox->setRange(-360, 360);
    m_rotateAngleSpinBox->setValue(45);
    m_rotateAngleSpinBox->setSuffix(" °");
    rotateForm->addRow("Angle:", m_rotateAngleSpinBox);
    
    m_rotateCenterXSpinBox = new QDoubleSpinBox();
    m_rotateCenterXSpinBox->setRange(-1000, 1000);
    rotateForm->addRow("Center X:", m_rotateCenterXSpinBox);
    
    m_rotateCenterYSpinBox = new QDoubleSpinBox();
    m_rotateCenterYSpinBox->setRange(-1000, 1000);
    rotateForm->addRow("Center Y:", m_rotateCenterYSpinBox);
    rotateGroup->setLayout(rotateForm);
    transformLayout->addWidget(rotateGroup);
    
    // Scale transformation
    QGroupBox *scaleGroup = new QGroupBox("Scale");
    QFormLayout *scaleForm = new QFormLayout();
    m_scaleFactorSpinBox = new QDoubleSpinBox();
    m_scaleFactorSpinBox->setRange(0.1, 5.0);
    m_scaleFactorSpinBox->setValue(1.5);
    m_scaleFactorSpinBox->setSingleStep(0.1);
    scaleForm->addRow("Scale Factor:", m_scaleFactorSpinBox);
    
    m_scaleCenterXSpinBox = new QDoubleSpinBox();
    m_scaleCenterXSpinBox->setRange(-1000, 1000);
    scaleForm->addRow("Center X:", m_scaleCenterXSpinBox);
    
    m_scaleCenterYSpinBox = new QDoubleSpinBox();
    m_scaleCenterYSpinBox->setRange(-1000, 1000);
    scaleForm->addRow("Center Y:", m_scaleCenterYSpinBox);
    scaleGroup->setLayout(scaleForm);
    transformLayout->addWidget(scaleGroup);
    
    // Transformation buttons
    QHBoxLayout *transformButtonsLayout = new QHBoxLayout();
    QPushButton *applyButton = new QPushButton("Apply");
    applyButton->setStyleSheet("QPushButton { padding: 8px; font-weight: bold; }");
    connect(applyButton, &QPushButton::clicked, this, &MainWindow::applyTransformation);
    transformButtonsLayout->addWidget(applyButton);
    
    QPushButton *animateButton = new QPushButton("Animate");
    connect(animateButton, &QPushButton::clicked, this, &MainWindow::animateTransformation);
    transformButtonsLayout->addWidget(animateButton);
    
    transformLayout->addLayout(transformButtonsLayout);
    
    // Animation progress
    m_animationProgressBar = new QProgressBar();
    m_animationProgressBar->setRange(0, 100);
    m_animationProgressBar->setValue(0);
    m_animationProgressBar->setVisible(false);
    transformLayout->addWidget(m_animationProgressBar);
    
    m_stopAnimationButton = new QPushButton("Stop Animation");
    m_stopAnimationButton->setEnabled(false);
    connect(m_stopAnimationButton, &QPushButton::clicked, this, &MainWindow::stopAnimation);
    transformLayout->addWidget(m_stopAnimationButton);
    
    transformLayout->addStretch();
    m_transformationsDock->setWidget(transformWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_transformationsDock);
    
    // Info dock (bottom)
    m_infoDock = new QDockWidget("Figure Information", this);
    m_infoDock->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    
    QWidget *infoWidget = new QWidget();
    QFormLayout *infoLayout = new QFormLayout(infoWidget);
    
    m_areaLabel = new QLabel("0.0");
    m_perimeterLabel = new QLabel("0.0");
    m_centerLabel = new QLabel("(0, 0)");
    m_verticesLabel = new QLabel("0");
    m_trianglesLabel = new QLabel("0");
    m_figureTypeLabel = new QLabel("None");
    
    infoLayout->addRow("Type:", m_figureTypeLabel);
    infoLayout->addRow("Area:", m_areaLabel);
    infoLayout->addRow("Perimeter:", m_perimeterLabel);
    infoLayout->addRow("Center of Mass:", m_centerLabel);
    infoLayout->addRow("Vertices:", m_verticesLabel);
    infoLayout->addRow("Triangles:", m_trianglesLabel);
    
    QHBoxLayout *infoButtonsLayout = new QHBoxLayout();
    QPushButton *showCenterButton = new QPushButton("Show Center Info");
    connect(showCenterButton, &QPushButton::clicked, this, &MainWindow::showCenterInfo);
    infoButtonsLayout->addWidget(showCenterButton);
    
    QPushButton *refreshButton = new QPushButton("Refresh");
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::updateFigureInfo);
    infoButtonsLayout->addWidget(refreshButton);
    
    infoLayout->addRow(infoButtonsLayout);
    
    m_infoDock->setWidget(infoWidget);
    addDockWidget(Qt::BottomDockWidgetArea, m_infoDock);
    
    // Set initial sizes
    m_figuresDock->setMinimumWidth(250);
    m_propertiesDock->setMinimumWidth(300);
    m_transformationsDock->setMinimumWidth(300);
    m_infoDock->setMaximumHeight(200);
    
    // Tabify docks
    tabifyDockWidget(m_propertiesDock, m_transformationsDock);
}

void MainWindow::createConnections()
{
    // Connect canvas signals
    connect(m_canvas, &FigureCanvas::figureSelected, this, &MainWindow::updateSelectedFigure);
    connect(m_canvas, &FigureCanvas::figureCreated, this, [this](Figure *figure) {
        Q_UNUSED(figure);
        updateFigureList();
        m_figureList->setCurrentRow(m_figureList->count() - 1);
        statusBar()->showMessage("Figure created", 2000);
    });
    
    // Connect mouse position tracking
    connect(m_canvas, &FigureCanvas::viewChanged, this, [this]() {
        updateDrawingControls();
    });
    
    // Connect drawing mode changes
    connect(m_canvas, &FigureCanvas::viewChanged, this, [this]() {
        m_canvas->update();
    });
}

void MainWindow::updateDrawingControls()
{
    DrawingTool::DrawingMode mode = m_canvas->drawingMode();
    
    // Update radio buttons
    switch(mode) {
        case DrawingTool::NoDrawing:
            m_noDrawingRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Selection");
            break;
        case DrawingTool::DrawTriangle:
            m_drawTriangleRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Triangle");
            break;
        case DrawingTool::DrawRectangle:
            m_drawRectangleRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Rectangle");
            break;
        case DrawingTool::DrawSquare:
            m_drawSquareRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Square");
            break;
        case DrawingTool::DrawCircle:
            m_drawCircleRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Circle");
            break;
        case DrawingTool::DrawRhombus:
            m_drawRhombusRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Rhombus");
            break;
        case DrawingTool::DrawHexagon:
            m_drawHexagonRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Hexagon");
            break;
        case DrawingTool::DrawStar:
            m_drawStarRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Star");
            break;
        case DrawingTool::DrawPolygon:
            m_drawPolygonRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Drawing Polygon");
            break;
        default:
            m_noDrawingRadio->setChecked(true);
            m_drawingModeLabel->setText("Mode: Unknown");
            break;
    }
    
    // Update toolbar actions
    m_drawTriangleAction->setChecked(mode == DrawingTool::DrawTriangle);
    m_drawRectangleAction->setChecked(mode == DrawingTool::DrawRectangle);
    m_drawSquareAction->setChecked(mode == DrawingTool::DrawSquare);
    m_drawCircleAction->setChecked(mode == DrawingTool::DrawCircle);
    m_drawRhombusAction->setChecked(mode == DrawingTool::DrawRhombus);
    m_drawHexagonAction->setChecked(mode == DrawingTool::DrawHexagon);
    m_drawStarAction->setChecked(mode == DrawingTool::DrawStar);
    m_drawPolygonAction->setChecked(mode == DrawingTool::DrawPolygon);
}

void MainWindow::uncheckDrawingActions()
{
    m_drawTriangleAction->setChecked(false);
    m_drawRectangleAction->setChecked(false);
    m_drawSquareAction->setChecked(false);
    m_drawCircleAction->setChecked(false);
    m_drawRhombusAction->setChecked(false);
    m_drawHexagonAction->setChecked(false);
    m_drawStarAction->setChecked(false);
    m_drawPolygonAction->setChecked(false);
}

// ============ FILE OPERATIONS ============

void MainWindow::newFile()
{
    int result = QMessageBox::question(this, "New File", 
                                      "Clear all figures and start new project?",
                                      QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        clearAllFigures();
        m_canvas->resetView();
        statusBar()->showMessage("New project created", 2000);
    }
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", 
                                                   "", "Geometry Files (*.geom);;All Files (*)");
    if (!fileName.isEmpty())
    {
        // TODO: Implement file loading
        statusBar()->showMessage("Loaded: " + fileName, 3000);
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Project", 
                                                   "project.geom", "Geometry Files (*.geom);;All Files (*)");
    if (!fileName.isEmpty())
    {
        // TODO: Implement file saving
        statusBar()->showMessage("Saved: " + fileName, 3000);
    }
}

void MainWindow::saveAsFile()
{
    saveFile();
}

void MainWindow::exportImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export Image", 
                                                   "figure.png", 
                                                   "Images (*.png *.jpg *.bmp *.tiff);;All Files (*)");
    if (!fileName.isEmpty())
    {
        QPixmap pixmap(m_canvas->size());
        m_canvas->render(&pixmap);
        if (pixmap.save(fileName))
        {
            statusBar()->showMessage("Exported: " + fileName, 3000);
        }
        else
        {
            QMessageBox::warning(this, "Export Error", "Failed to save image");
        }
    }
}

void MainWindow::exitApplication()
{
    int result = QMessageBox::question(this, "Exit", 
                                      "Are you sure you want to exit?",
                                      QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

// ============ EDIT OPERATIONS ============

void MainWindow::copyFigure()
{
    if (m_currentFigure)
    {
        // TODO: Implement figure copying
        statusBar()->showMessage("Figure copied to clipboard", 2000);
    }
}

void MainWindow::pasteFigure()
{
    // TODO: Implement figure pasting
    statusBar()->showMessage("Figure pasted from clipboard", 2000);
}

void MainWindow::deleteFigure()
{
    removeSelectedFigure();
}

void MainWindow::selectAll()
{
    if (!m_canvas->getFigures().isEmpty())
    {
        m_figureList->selectAll();
    }
}

void MainWindow::deselectAll()
{
    m_figureList->clearSelection();
    m_currentFigure = nullptr;
    m_canvas->setSelectedFigure(nullptr);
    updateFigureInfo();
}

// ============ FIGURE METHODS ============

void MainWindow::createFigure()
{
    QString type = m_figureTypeCombo->currentText();
    createFigureFromType(type);
}

void MainWindow::createFigureFromType(const QString &type)
{
    // Create figure at random position
    int x = 200 + QRandomGenerator::global()->bounded(400);
    int y = 200 + QRandomGenerator::global()->bounded(300);
    Figure *figure = createFigureByType(type, QPointF(x, y));
    
    if (figure)
    {
        figure->setColor(m_currentLineColor);
        figure->setFillColor(m_currentFillColor);
        figure->setLineWidth(m_lineWidthSpinBox->value());
        
        m_canvas->addFigure(figure);
        
        connect(figure, &Figure::figureChanged, this, &MainWindow::updateFigureInfo);
        connect(figure, &Figure::animationProgress, this, &MainWindow::updateAnimationProgress);
        connect(figure, &Figure::animationFinished, this, [this]() {
            m_animationProgressBar->setVisible(false);
            m_stopAnimationButton->setEnabled(false);
            updateFigureInfo();
        });
        
        updateFigureList();
        m_figureList->setCurrentRow(m_figureList->count() - 1);
        
        statusBar()->showMessage("Created " + type, 2000);
    }
}

Figure* MainWindow::createFigureByType(const QString &type, const QPointF &center)
{
    Figure *figure = nullptr;
    
    if (type == "Triangle")
    {
        QPointF p1(center.x() - 40, center.y() + 40);
        QPointF p2(center.x() + 40, center.y() + 40);
        QPointF p3(center.x(), center.y() - 40);
        figure = new Triangle(p1, p2, p3, this);
    }
    else if (type == "Rectangle")
    {
        figure = new Rectangle(center, 120, 80, this);
    }
    else if (type == "Square")
    {
        figure = new Square(center, 100, this);
    }
    else if (type == "Rhombus")
    {
        figure = new Rhombus(center, 120, 80, this);
    }
    else if (type == "Hexagon")
    {
        figure = new Hexagon(center, 70, this);
    }
    else if (type == "Star")
    {
        Star::StarType starType = Star::FivePointed;
        int starChoice = QRandomGenerator::global()->bounded(3);
        if (starChoice == 0) starType = Star::FivePointed;
        else if (starChoice == 1) starType = Star::SixPointed;
        else starType = Star::EightPointed;
        
        figure = new Star(center, 70, 35, starType, this);
    }
    else if (type == "Circle")
    {
        figure = new Circle(center, 60, this);
    }
    else if (type == "Polygon")
    {
        figure = new CustomFigure(center, 65, 7, this);
    }
    
    return figure;
}

// ИСПРАВЛЕННЫЙ МЕТОД УДАЛЕНИЯ ФИГУРЫ
void MainWindow::removeSelectedFigure()
{
    if (m_currentFigure)
    {
        // Отключаем все соединения перед удалением
        m_currentFigure->disconnect();
        
        // Удаляем из canvas
        m_canvas->removeFigure(m_currentFigure);
        
        // Находим индекс удаляемой фигуры
        int index = m_canvas->getFigures().indexOf(m_currentFigure);
        
        // Удаляем объект
        m_currentFigure->deleteLater();
        m_currentFigure = nullptr;
        
        // Обновляем интерфейс
        updateFigureInfo();
        updateFigureList();
        
        // Выбираем следующую фигуру, если есть
        if (m_figureList->count() > 0)
        {
            int newIndex = qMin(index, m_figureList->count() - 1);
            m_figureList->setCurrentRow(newIndex);
        }
        else
        {
            // Если фигур не осталось, очищаем параметры
            updateParameterControls();
        }
        
        statusBar()->showMessage("Figure removed", 2000);
    }
    else
    {
        QMessageBox::information(this, "Info", "No figure selected");
    }
}

void MainWindow::clearAllFigures()
{
    int result = QMessageBox::question(this, "Clear All", 
                                      "Remove all figures?",
                                      QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        // Отключаем все соединения
        for (Figure *figure : m_canvas->getFigures())
        {
            figure->disconnect();
        }
        
        m_canvas->clearFigures();
        updateFigureInfo();
        updateFigureList();
        m_currentFigure = nullptr;
        updateParameterControls();
        statusBar()->showMessage("All figures cleared", 2000);
    }
}

void MainWindow::updateFigureList()
{
    m_figureList->clear();
    int counter = 1;
    for (Figure *figure : m_canvas->getFigures())
    {
        QPointF center = figure->centerOfMass();
        m_figureList->addItem(QString("%1. %2 - Area: %3, Center: (%4, %5)")
            .arg(counter++)
            .arg(figure->type())
            .arg(figure->area(), 0, 'f', 1)
            .arg(center.x(), 0, 'f', 0)
            .arg(center.y(), 0, 'f', 0));
    }
}

void MainWindow::updateSelectedFigure()
{
    int row = m_figureList->currentRow();
    if (row >= 0 && row < m_canvas->getFigures().size())
    {
        m_currentFigure = m_canvas->getFigures()[row];
        m_canvas->setSelectedFigure(m_currentFigure);
        updateFigureInfo();
        updateParameterControls();
        updateTransformationControls();
    }
    else
    {
        m_currentFigure = nullptr;
        m_canvas->setSelectedFigure(nullptr);
        updateFigureInfo();
        updateParameterControls();
    }
}

void MainWindow::updateFigureInfo()
{
    if (m_currentFigure)
    {
        m_figureTypeLabel->setText(m_currentFigure->type());
        m_areaLabel->setText(QString::number(m_currentFigure->area(), 'f', 2));
        m_perimeterLabel->setText(QString::number(m_currentFigure->perimeter(), 'f', 2));
        
        QPointF center = m_currentFigure->centerOfMass();
        m_centerLabel->setText(QString("(%1, %2)").arg(center.x(), 0, 'f', 1).arg(center.y(), 0, 'f', 1));
        
        PolygonFigure *polygon = dynamic_cast<PolygonFigure*>(m_currentFigure);
        if (polygon)
        {
            m_verticesLabel->setText(QString::number(polygon->vertexCount()));
            m_trianglesLabel->setText(QString::number(polygon->triangulate().size()));
        }
        else
        {
            m_verticesLabel->setText("N/A");
            m_trianglesLabel->setText("N/A");
        }
    }
    else
    {
        m_figureTypeLabel->setText("None");
        m_areaLabel->setText("0.0");
        m_perimeterLabel->setText("0.0");
        m_centerLabel->setText("(0, 0)");
        m_verticesLabel->setText("0");
        m_trianglesLabel->setText("0");
    }
}

void MainWindow::updateParameterControls()
{
    if (!m_currentFigure)
    {
        // Disable all controls
        m_lineColorButton->setEnabled(false);
        m_fillColorButton->setEnabled(false);
        m_lineWidthSpinBox->setEnabled(false);
        m_paramTabs->setEnabled(false);
        m_vertexGroup->setEnabled(false);
        return;
    }
    
    // Enable basic controls
    m_lineColorButton->setEnabled(true);
    m_fillColorButton->setEnabled(true);
    m_lineWidthSpinBox->setEnabled(true);
    
    // Update color buttons
    m_lineColorButton->setStyleSheet(
        QString("background-color: %1; color: white; padding: 5px;").arg(m_currentFigure->getColor().name()));
    m_fillColorButton->setStyleSheet(
        QString("background-color: %1; padding: 5px;").arg(m_currentFigure->fillColor().name()));
    
    // Update line width
    m_lineWidthSpinBox->setValue(m_currentFigure->lineWidth());
    
    // Update specific parameters based on figure type
    m_paramTabs->setEnabled(true);
    
    Circle *circle = dynamic_cast<Circle*>(m_currentFigure);
    if (circle)
    {
        m_paramTabs->setCurrentWidget(m_circleParams);
        m_radiusSpinBox->setValue(circle->radius());
    }
    
    Rectangle *rect = dynamic_cast<Rectangle*>(m_currentFigure);
    if (rect)
    {
        m_paramTabs->setCurrentWidget(m_rectangleParams);
        m_widthSpinBox->setValue(rect->width());
        m_heightSpinBox->setValue(rect->height());
    }
    
    Square *square = dynamic_cast<Square*>(m_currentFigure);
    if (square)
    {
        m_paramTabs->setCurrentWidget(m_squareParams);
        m_sideSpinBox->setValue(square->side());
    }
    
    Rhombus *rhombus = dynamic_cast<Rhombus*>(m_currentFigure);
    if (rhombus)
    {
        m_paramTabs->setCurrentWidget(m_rhombusParams);
        m_diag1SpinBox->setValue(rhombus->diagonal1());
        m_diag2SpinBox->setValue(rhombus->diagonal2());
    }
    
    Hexagon *hexagon = dynamic_cast<Hexagon*>(m_currentFigure);
    if (hexagon)
    {
        m_paramTabs->setCurrentWidget(m_hexagonParams);
        QDoubleSpinBox *radiusSpinBox = m_hexagonParams->findChild<QDoubleSpinBox*>();
        if (radiusSpinBox)
        {
            radiusSpinBox->setValue(hexagon->radius());
        }
    }
    
    Star *star = dynamic_cast<Star*>(m_currentFigure);
    if (star)
    {
        m_paramTabs->setCurrentWidget(m_starParams);
        m_starTypeCombo->setCurrentIndex(static_cast<int>(star->starType()) - 5);
        m_outerRadiusSpinBox->setValue(star->outerRadius());
        m_innerRadiusSpinBox->setValue(star->innerRadius());
    }
    
    Triangle *triangle = dynamic_cast<Triangle*>(m_currentFigure);
    if (triangle)
    {
        m_paramTabs->setCurrentWidget(m_triangleParams);
        QList<QPointF> points = triangle->getPoints();
        if (points.size() == 3)
        {
            double base = QLineF(points[0], points[1]).length();
            double height = qAbs(points[2].y() - points[0].y());
            m_triangleBaseSpinBox->setValue(base);
            m_triangleHeightSpinBox->setValue(height);
        }
    }
    
    CustomFigure *custom = dynamic_cast<CustomFigure*>(m_currentFigure);
    if (custom)
    {
        m_paramTabs->setCurrentWidget(m_polygonParams);
        m_sidesSpinBox->setValue(custom->sides());
    }
    
    // Update vertex control
    PolygonFigure *polygon = dynamic_cast<PolygonFigure*>(m_currentFigure);
    if (polygon)
    {
        m_vertexGroup->setEnabled(true);
        int vertexCount = polygon->vertexCount();
        m_vertexIndexSpinBox->setRange(0, qMax(0, vertexCount - 1));
        
        if (vertexCount > 0)
        {
            QList<QPointF> vertices = polygon->getVertices();
            int index = m_vertexIndexSpinBox->value();
            if (index < vertices.size())
            {
                m_vertexXSpinBox->setValue(vertices[index].x());
                m_vertexYSpinBox->setValue(vertices[index].y());
            }
        }
    }
    else
    {
        m_vertexGroup->setEnabled(false);
    }
    
    // Update center position
    if (m_currentFigure)
    {
        QPointF center = m_currentFigure->centerOfMass();
        m_newCenterXSpinBox->setValue(center.x());
        m_newCenterYSpinBox->setValue(center.y());
    }
}

void MainWindow::updateTransformationControls()
{
    if (!m_currentFigure)
        return;
    
    // Set current center as transformation center
    QPointF center = m_currentFigure->centerOfMass();
    m_rotateCenterXSpinBox->setValue(center.x());
    m_rotateCenterYSpinBox->setValue(center.y());
    m_scaleCenterXSpinBox->setValue(center.x());
    m_scaleCenterYSpinBox->setValue(center.y());
}

void MainWindow::showCenterInfo()
{
    if (m_currentFigure)
    {
        QPointF center = m_currentFigure->centerOfMass();
        QMessageBox::information(this, "Center of Mass", 
            QString("Center of mass is at:\nX = %1\nY = %2\n\nArea: %3\nPerimeter: %4")
                .arg(center.x(), 0, 'f', 2)
                .arg(center.y(), 0, 'f', 2)
                .arg(m_currentFigure->area(), 0, 'f', 2)
                .arg(m_currentFigure->perimeter(), 0, 'f', 2));
    }
}

// ============ DRAWING MODES ============

void MainWindow::setDrawTriangleMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawTriangle);
    uncheckDrawingActions();
    m_drawTriangleAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Triangle", 2000);
}

void MainWindow::setDrawRectangleMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawRectangle);
    uncheckDrawingActions();
    m_drawRectangleAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Rectangle", 2000);
}

void MainWindow::setDrawSquareMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawSquare);
    uncheckDrawingActions();
    m_drawSquareAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Square", 2000);
}

void MainWindow::setDrawCircleMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawCircle);
    uncheckDrawingActions();
    m_drawCircleAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Circle", 2000);
}

void MainWindow::setDrawRhombusMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawRhombus);
    uncheckDrawingActions();
    m_drawRhombusAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Rhombus", 2000);
}

void MainWindow::setDrawHexagonMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawHexagon);
    uncheckDrawingActions();
    m_drawHexagonAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Hexagon", 2000);
}

void MainWindow::setDrawStarMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawStar);
    uncheckDrawingActions();
    m_drawStarAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Star", 2000);
}

void MainWindow::setDrawPolygonMode()
{
    m_canvas->setDrawingMode(DrawingTool::DrawPolygon);
    uncheckDrawingActions();
    m_drawPolygonAction->setChecked(true);
    statusBar()->showMessage("Drawing mode: Polygon", 2000);
}

void MainWindow::stopDrawingMode()
{
    m_canvas->setDrawingMode(DrawingTool::NoDrawing);
    uncheckDrawingActions();
    m_noDrawingRadio->setChecked(true);
    statusBar()->showMessage("Drawing stopped", 2000);
}

// ============ TRANSFORMATIONS ============

void MainWindow::applyTransformation()
{
    if (!m_currentFigure)
    {
        QMessageBox::warning(this, "Warning", "Please select a figure first!");
        return;
    }
    
    bool transformed = false;
    
    // 1. Move
    QPointF moveOffset(m_moveXSpinBox->value(), m_moveYSpinBox->value());
    if (!moveOffset.isNull())
    {
        m_currentFigure->move(moveOffset);
        transformed = true;
    }
    
    // 2. Rotate
    double angle = m_rotateAngleSpinBox->value();
    if (qAbs(angle) > 0.001)
    {
        QPointF rotateCenter(m_rotateCenterXSpinBox->value(), m_rotateCenterYSpinBox->value());
        m_currentFigure->rotate(angle, rotateCenter);
        transformed = true;
    }
    
    // 3. Scale
    double factor = m_scaleFactorSpinBox->value();
    if (qAbs(factor - 1.0) > 0.001)
    {
        QPointF scaleCenter(m_scaleCenterXSpinBox->value(), m_scaleCenterYSpinBox->value());
        m_currentFigure->scale(factor, scaleCenter);
        transformed = true;
    }
    
    if (transformed)
    {
        updateFigureInfo();
        updateFigureList();
        updateParameterControls();
        m_canvas->update();
        statusBar()->showMessage("Transformation applied", 2000);
    }
}

void MainWindow::animateTransformation()
{
    if (!m_currentFigure)
    {
        QMessageBox::warning(this, "Warning", "Please select a figure first!");
        return;
    }
    
    m_animationProgressBar->setVisible(true);
    m_animationProgressBar->setValue(0);
    m_stopAnimationButton->setEnabled(true);
    
    QPointF currentCenter = m_currentFigure->centerOfMass();
    QPointF moveTarget = currentCenter + QPointF(m_moveXSpinBox->value(), m_moveYSpinBox->value());
    double rotateAngle = m_rotateAngleSpinBox->value();
    double scaleFactor = m_scaleFactorSpinBox->value();
    
    QPointF rotateCenter(m_rotateCenterXSpinBox->value(), m_rotateCenterYSpinBox->value());
    QPointF scaleCenter(m_scaleCenterXSpinBox->value(), m_scaleCenterYSpinBox->value());
    
    bool animationStarted = false;
    
    if (!QPointF(m_moveXSpinBox->value(), m_moveYSpinBox->value()).isNull())
    {
        m_currentFigure->animateMove(moveTarget, 2000);
        animationStarted = true;
    }
    
    if (qAbs(rotateAngle) > 0.001)
    {
        m_currentFigure->animateRotate(rotateAngle, rotateCenter, 2000);
        animationStarted = true;
    }
    
    if (qAbs(scaleFactor - 1.0) > 0.001)
    {
        m_currentFigure->animateScale(scaleFactor, scaleCenter, 2000);
        animationStarted = true;
    }
    
    if (!animationStarted)
    {
        QMessageBox::information(this, "Info", "No transformation parameters set!");
        m_animationProgressBar->setVisible(false);
        m_stopAnimationButton->setEnabled(false);
    }
    else
    {
        statusBar()->showMessage("Animation started", 2000);
    }
}

void MainWindow::stopAnimation()
{
    if (m_currentFigure && m_currentFigure->isAnimating())
    {
        m_currentFigure->stopAnimation();
        m_animationProgressBar->setVisible(false);
        m_stopAnimationButton->setEnabled(false);
        updateFigureInfo();
        statusBar()->showMessage("Animation stopped", 2000);
    }
}

void MainWindow::updateAnimationProgress(double progress)
{
    m_animationProgressBar->setValue(static_cast<int>(progress * 100));
}

// ============ PARAMETER MANAGEMENT ============

void MainWindow::chooseLineColor()
{
    QColor color = QColorDialog::getColor(m_currentLineColor, this, "Choose Line Color");
    if (color.isValid())
    {
        m_currentLineColor = color;
        m_lineColorButton->setStyleSheet(
            QString("background-color: %1; color: white; padding: 5px;").arg(color.name()));
        if (m_currentFigure)
        {
            m_currentFigure->setColor(color);
            m_canvas->update();
        }
        // Also update drawing color
        m_canvas->setDrawingColor(color);
    }
}

void MainWindow::chooseFillColor()
{
    QColor color = QColorDialog::getColor(m_currentFillColor, this, "Choose Fill Color");
    if (color.isValid())
    {
        m_currentFillColor = color;
        m_fillColorButton->setStyleSheet(
            QString("background-color: %1; padding: 5px;").arg(color.name()));
        if (m_currentFigure)
        {
            m_currentFigure->setFillColor(color);
            m_canvas->update();
        }
        // Also update drawing fill color
        m_canvas->setDrawingFillColor(color);
    }
}

void MainWindow::updateLineWidth()
{
    if (m_currentFigure)
    {
        m_currentFigure->setLineWidth(m_lineWidthSpinBox->value());
        m_canvas->update();
    }
    // Also update drawing line width
    m_canvas->setDrawingLineWidth(m_lineWidthSpinBox->value());
}

void MainWindow::updateSpecificParameter()
{
    if (!m_currentFigure) return;
    
    Circle *circle = dynamic_cast<Circle*>(m_currentFigure);
    if (circle)
    {
        circle->setRadius(m_radiusSpinBox->value());
    }
    
    Rectangle *rect = dynamic_cast<Rectangle*>(m_currentFigure);
    if (rect)
    {
        rect->setWidth(m_widthSpinBox->value());
        rect->setHeight(m_heightSpinBox->value());
    }
    
    Square *square = dynamic_cast<Square*>(m_currentFigure);
    if (square)
    {
        square->setSide(m_sideSpinBox->value());
    }
    
    Rhombus *rhombus = dynamic_cast<Rhombus*>(m_currentFigure);
    if (rhombus)
    {
        rhombus->setDiagonal1(m_diag1SpinBox->value());
        rhombus->setDiagonal2(m_diag2SpinBox->value());
    }
    
    Hexagon *hexagon = dynamic_cast<Hexagon*>(m_currentFigure);
    if (hexagon)
    {
        QDoubleSpinBox *radiusSpinBox = m_hexagonParams->findChild<QDoubleSpinBox*>();
        if (radiusSpinBox)
        {
            QPointF center = hexagon->centerOfMass();
            double radius = radiusSpinBox->value();
            hexagon->setHexagon(center, radius);
        }
    }
    
    Star *star = dynamic_cast<Star*>(m_currentFigure);
    if (star)
    {
        Star::StarType starType = static_cast<Star::StarType>(5 + m_starTypeCombo->currentIndex());
        star->setStarType(starType);
        star->setOuterRadius(m_outerRadiusSpinBox->value());
        star->setInnerRadius(m_innerRadiusSpinBox->value());
    }
    
    Triangle *triangle = dynamic_cast<Triangle*>(m_currentFigure);
    if (triangle)
    {
        QList<QPointF> points = triangle->getPoints();
        if (points.size() == 3)
        {
            QPointF center = triangle->centerOfMass();
            double base = m_triangleBaseSpinBox->value();
            double height = m_triangleHeightSpinBox->value();
            
            QPointF p1(center.x() - base/2, center.y() + height/2);
            QPointF p2(center.x() + base/2, center.y() + height/2);
            QPointF p3(center.x(), center.y() - height/2);
            
            triangle->setPoints(p1, p2, p3);
        }
    }
    
    CustomFigure *custom = dynamic_cast<CustomFigure*>(m_currentFigure);
    if (custom)
    {
        custom->setSides(m_sidesSpinBox->value());
    }
    
    updateFigureInfo();
    updateFigureList();
    m_canvas->update();
    statusBar()->showMessage("Parameters updated", 2000);
}

void MainWindow::updateVertex()
{
    if (!m_currentFigure)
        return;
    
    PolygonFigure *polygon = dynamic_cast<PolygonFigure*>(m_currentFigure);
    if (polygon)
    {
        int index = m_vertexIndexSpinBox->value();
        QPointF point(m_vertexXSpinBox->value(), m_vertexYSpinBox->value());
        polygon->setVertex(index, point);
        updateFigureInfo();
        m_canvas->update();
        statusBar()->showMessage("Vertex updated", 2000);
    }
}

void MainWindow::moveCenterToPoint()
{
    if (!m_currentFigure)
    {
        QMessageBox::warning(this, "Warning", "Please select a figure first!");
        return;
    }
    
    QPointF newCenter(m_newCenterXSpinBox->value(), m_newCenterYSpinBox->value());
    m_currentFigure->setCenter(newCenter);
    
    updateFigureInfo();
    updateFigureList();
    m_canvas->update();
    statusBar()->showMessage("Center moved", 2000);
}

// ============ VIEW OPERATIONS ============

void MainWindow::toggleGrid(bool enabled)
{
    m_canvas->setGridEnabled(enabled);
    statusBar()->showMessage(enabled ? "Grid enabled" : "Grid disabled", 1000);
}

void MainWindow::toggleCenters(bool enabled)
{
    m_canvas->setShowCenters(enabled);
    statusBar()->showMessage(enabled ? "Centers visible" : "Centers hidden", 1000);
}

void MainWindow::toggleTriangulation(bool enabled)
{
    m_canvas->setShowTriangulation(enabled);
    statusBar()->showMessage(enabled ? "Triangulation visible" : "Triangulation hidden", 1000);
}

void MainWindow::toggleVertices(bool enabled)
{
    m_canvas->setShowVertices(enabled);
    statusBar()->showMessage(enabled ? "Vertices visible" : "Vertices hidden", 1000);
}

void MainWindow::toggleBoundingBox(bool enabled)
{
    m_canvas->setShowBoundingBox(enabled);
    statusBar()->showMessage(enabled ? "Bounding boxes visible" : "Bounding boxes hidden", 1000);
}

void MainWindow::toggleSnapToGrid(bool enabled)
{
    // TODO: Implement snap to grid
    statusBar()->showMessage(enabled ? "Snap to grid enabled" : "Snap to grid disabled", 1000);
}

void MainWindow::zoomIn()
{
    m_canvas->zoomIn();
    statusBar()->showMessage("Zoomed in", 1000);
}

void MainWindow::zoomOut()
{
    m_canvas->zoomOut();
    statusBar()->showMessage("Zoomed out", 1000);
}

void MainWindow::resetView()
{
    m_canvas->resetView();
    statusBar()->showMessage("View reset", 2000);
}

void MainWindow::fitToView()
{
    if (m_canvas->getFigures().isEmpty())
    {
        statusBar()->showMessage("No figures to fit", 2000);
        return;
    }
    
    // Calculate bounding box of all figures
    QRectF totalBounds;
    for (Figure *figure : m_canvas->getFigures())
    {
        totalBounds = totalBounds.united(figure->boundingRect());
    }
    
    // Add some padding
    totalBounds.adjust(-50, -50, 50, 50);
    
    // TODO: Implement fit to view logic
    statusBar()->showMessage("Fit to view", 2000);
}

void MainWindow::showFullScreen()
{
    if (isFullScreen())
    {
        showNormal();
        statusBar()->showMessage("Exited full screen", 1000);
    }
    else
    {
        showFullScreen();
        statusBar()->showMessage("Entered full screen", 1000);
    }
}

// ============ CALCULATIONS ============

void MainWindow::calculateTotalArea()
{
    double totalArea = 0.0;
    for (Figure *figure : m_canvas->getFigures())
    {
        totalArea += figure->area();
    }
    
    QMessageBox::information(this, "Total Area", 
        QString("Total area of all figures: %1").arg(totalArea, 0, 'f', 2));
}

void MainWindow::calculateTotalPerimeter()
{
    double totalPerimeter = 0.0;
    for (Figure *figure : m_canvas->getFigures())
    {
        totalPerimeter += figure->perimeter();
    }
    
    QMessageBox::information(this, "Total Perimeter", 
        QString("Total perimeter of all figures: %1").arg(totalPerimeter, 0, 'f', 2));
}

void MainWindow::showFigureStatistics()
{
    int triangleCount = 0;
    int rectangleCount = 0;
    int squareCount = 0;
    int circleCount = 0;
    int rhombusCount = 0;
    int hexagonCount = 0;
    int starCount = 0;
    int polygonCount = 0;
    
    double totalArea = 0.0;
    double totalPerimeter = 0.0;
    
    for (Figure *figure : m_canvas->getFigures())
    {
        totalArea += figure->area();
        totalPerimeter += figure->perimeter();
        
        QString type = figure->type();
        if (type == "Triangle") triangleCount++;
        else if (type == "Rectangle") rectangleCount++;
        else if (type == "Square") squareCount++;
        else if (type == "Circle") circleCount++;
        else if (type == "Rhombus") rhombusCount++;
        else if (type == "Hexagon") hexagonCount++;
        else if (type == "Star") starCount++;
        else if (type == "Polygon" || type == "CustomFigure") polygonCount++;
    }
    
    QString stats = QString(
        "Figure Statistics:\n\n"
        "Total Figures: %1\n"
        "Triangles: %2\n"
        "Rectangles: %3\n"
        "Squares: %4\n"
        "Circles: %5\n"
        "Rhombuses: %6\n"
        "Hexagons: %7\n"
        "Stars: %8\n"
        "Polygons: %9\n\n"
        "Total Area: %10\n"
        "Total Perimeter: %11"
    ).arg(m_canvas->getFigures().size())
     .arg(triangleCount).arg(rectangleCount).arg(squareCount)
     .arg(circleCount).arg(rhombusCount).arg(hexagonCount)
     .arg(starCount).arg(polygonCount)
     .arg(totalArea, 0, 'f', 2)
     .arg(totalPerimeter, 0, 'f', 2);
    
    QMessageBox::information(this, "Figure Statistics", stats);
}

// ============ HELP ============

void MainWindow::about()
{
    QMessageBox::about(this, "About Geometry Figures Application",
        "<h3>Geometry Figures Application</h3>"
        "<p>Version 1.0</p>"
        "<p>This application demonstrates object-oriented programming concepts "
        "with geometric figures using Qt framework.</p>"
        "<p>Features:</p>"
        "<ul>"
        "<li>Create various geometric figures (programmatically or by drawing)</li>"
        "<li>Transform figures (move, rotate, scale)</li>"
        "<li>Animate transformations</li>"
        "<li>Calculate area, perimeter, center of mass</li>"
        "<li>Visualize triangulation</li>"
        "<li>Edit figure properties in real-time</li>"
        "</ul>"
        "<p>Developed for educational purposes.</p>");
}

void MainWindow::showHelp()
{
    QMessageBox::information(this, "Help", 
        "<h3>Geometry Figures Application Help</h3>"
        "<p><b>Creating Figures:</b><br>"
        "1. Use the Figure menu or sidebar to create figures<br>"
        "2. Use the Drawing tools to draw figures with the mouse</p>"
        "<p><b>Drawing Modes:</b><br>"
        "- Triangle: Click and drag to draw<br>"
        "- Rectangle: Click and drag to draw<br>"
        "- Square: Click and drag (hold Shift for perfect square)<br>"
        "- Circle: Click and drag to draw<br>"
        "- Polygon: Click to add vertices, right-click to finish</p>"
        "<p><b>Selecting Figures:</b><br>"
        "Click on a figure to select it or select from the list.</p>"
        "<p><b>Transforming Figures:</b><br>"
        "Use the Transformations dock to move, rotate, or scale figures.</p>"
        "<p><b>Modifying Properties:</b><br>"
        "Use the Properties dock to change colors, line width, and parameters.</p>");
}

void MainWindow::showShortcuts()
{
    QMessageBox::information(this, "Keyboard Shortcuts",
        "<h3>Keyboard Shortcuts</h3>"
        "<p><b>File:</b><br>"
        "Ctrl+N - New project<br>"
        "Ctrl+O - Open<br>"
        "Ctrl+S - Save<br>"
        "Ctrl+Shift+S - Save As<br>"
        "Ctrl+Q - Quit</p>"
        "<p><b>Edit:</b><br>"
        "Ctrl+C - Copy<br>"
        "Ctrl+V - Paste<br>"
        "Del - Delete<br>"
        "Ctrl+A - Select All<br>"
        "Ctrl+Shift+A - Deselect All</p>"
        "<p><b>View:</b><br>"
        "Ctrl++ - Zoom In<br>"
        "Ctrl+- - Zoom Out<br>"
        "Ctrl+R - Reset View<br>"
        "Ctrl+F - Fit to View<br>"
        "Ctrl+G - Toggle Grid</p>"
        "<p><b>Drawing:</b><br>"
        "Alt+T - Draw Triangle<br>"
        "Alt+R - Draw Rectangle<br>"
        "Alt+Q - Draw Square<br>"
        "Alt+C - Draw Circle<br>"
        "Esc - Stop Drawing</p>");
}