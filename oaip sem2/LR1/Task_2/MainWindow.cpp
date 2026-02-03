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
    
    // Connect signals
    connect(m_canvas, &FigureCanvas::figureSelected, this, &MainWindow::updateSelectedFigure);
    
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
    
    QAction *newAction = new QAction("&New", this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    m_fileMenu->addAction(newAction);
    
    QAction *openAction = new QAction("&Open...", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    m_fileMenu->addAction(openAction);
    
    QAction *saveAction = new QAction("&Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    m_fileMenu->addAction(saveAction);
    
    QAction *saveAsAction = new QAction("Save &As...", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFile);
    m_fileMenu->addAction(saveAsAction);
    
    m_fileMenu->addSeparator();
    
    QAction *exportAction = new QAction("&Export Image...", this);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportImage);
    m_fileMenu->addAction(exportAction);
    
    m_fileMenu->addSeparator();
    
    QAction *exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    m_fileMenu->addAction(exitAction);
    
    // Edit menu
    m_editMenu = menuBar()->addMenu("&Edit");
    
    QAction *copyAction = new QAction("&Copy", this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyFigure);
    m_editMenu->addAction(copyAction);
    
    QAction *pasteAction = new QAction("&Paste", this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteFigure);
    m_editMenu->addAction(pasteAction);
    
    QAction *deleteAction = new QAction("&Delete", this);
    deleteAction->setShortcut(QKeySequence::Delete);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteFigure);
    m_editMenu->addAction(deleteAction);
    
    // View menu
    m_viewMenu = menuBar()->addMenu("&View");
    
    QAction *zoomInAction = new QAction("Zoom &In", this);
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    m_viewMenu->addAction(zoomInAction);
    
    QAction *zoomOutAction = new QAction("Zoom &Out", this);
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    m_viewMenu->addAction(zoomOutAction);
    
    QAction *resetViewAction = new QAction("&Reset View", this);
    resetViewAction->setShortcut(QKeySequence("Ctrl+R"));
    connect(resetViewAction, &QAction::triggered, this, &MainWindow::resetView);
    m_viewMenu->addAction(resetViewAction);
    
    QAction *fitViewAction = new QAction("&Fit to View", this);
    fitViewAction->setShortcut(QKeySequence("Ctrl+F"));
    connect(fitViewAction, &QAction::triggered, this, &MainWindow::fitToView);
    m_viewMenu->addAction(fitViewAction);
    
    m_viewMenu->addSeparator();
    
    QAction *gridAction = new QAction("Show &Grid", this);
    gridAction->setCheckable(true);
    gridAction->setChecked(true);
    connect(gridAction, &QAction::toggled, this, &MainWindow::toggleGrid);
    m_viewMenu->addAction(gridAction);
    
    QAction *centersAction = new QAction("Show &Centers", this);
    centersAction->setCheckable(true);
    centersAction->setChecked(true);
    connect(centersAction, &QAction::toggled, this, &MainWindow::toggleCenters);
    m_viewMenu->addAction(centersAction);
    
    QAction *verticesAction = new QAction("Show &Vertices", this);
    verticesAction->setCheckable(true);
    verticesAction->setChecked(true);
    connect(verticesAction, &QAction::toggled, this, &MainWindow::toggleVertices);
    m_viewMenu->addAction(verticesAction);
    
    QAction *bboxAction = new QAction("Show &Bounding Boxes", this);
    bboxAction->setCheckable(true);
    bboxAction->setChecked(false);
    connect(bboxAction, &QAction::toggled, this, &MainWindow::toggleBoundingBox);
    m_viewMenu->addAction(bboxAction);
    
    QAction *triangulationAction = new QAction("Show &Triangulation", this);
    triangulationAction->setCheckable(true);
    triangulationAction->setChecked(false);
    connect(triangulationAction, &QAction::toggled, this, &MainWindow::toggleTriangulation);
    m_viewMenu->addAction(triangulationAction);
    
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
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearAllFigures);
    m_figureMenu->addAction(clearAction);
    
    // Help menu
    m_helpMenu = menuBar()->addMenu("&Help");
    
    QAction *helpAction = new QAction("&Help Contents", this);
    helpAction->setShortcut(QKeySequence::HelpContents);
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelp);
    m_helpMenu->addAction(helpAction);
    
    QAction *aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    m_helpMenu->addAction(aboutAction);
}

void MainWindow::setupToolBar()
{
    m_mainToolBar = addToolBar("Main Toolbar");
    
    // Figure creation buttons
    QStringList figureTypes = {"Triangle", "Rectangle", "Square", "Rhombus", 
                              "Hexagon", "Star", "Circle", "Polygon"};
    
    for (const QString &type : figureTypes)
    {
        QAction *action = new QAction(type, this);
        action->setIconText(type.left(3));
        connect(action, &QAction::triggered, this, [this, type]() {
            createFigureFromType(type);
        });
        m_mainToolBar->addAction(action);
    }
    
    m_mainToolBar->addSeparator();
    
    // Transformation buttons
    QAction *moveAction = new QAction("Move", this);
    moveAction->setIconText("Move");
    connect(moveAction, &QAction::triggered, this, [this]() {
        if (m_currentFigure)
        {
            QPointF offset(m_moveXSpinBox->value(), m_moveYSpinBox->value());
            m_currentFigure->move(offset);
        }
    });
    m_mainToolBar->addAction(moveAction);
    
    QAction *rotateAction = new QAction("Rotate", this);
    rotateAction->setIconText("Rotate");
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
    scaleAction->setIconText("Scale");
    connect(scaleAction, &QAction::triggered, this, [this]() {
        if (m_currentFigure)
        {
            double factor = m_scaleFactorSpinBox->value();
            QPointF center(m_scaleCenterXSpinBox->value(), m_scaleCenterYSpinBox->value());
            m_currentFigure->scale(factor, center);
        }
    });
    m_mainToolBar->addAction(scaleAction);
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Ready");
    statusBar()->addWidget(m_statusLabel);
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
                          QPointF(m_canvas->width()/2, m_canvas->height()/2));
    });
    creationLayout->addWidget(createAtCenterButton);
    
    creationGroup->setLayout(creationLayout);
    figuresLayout->addWidget(creationGroup);
    
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
    
    paramsLayout->addWidget(m_paramTabs);
    
    QPushButton *updateParamsButton = new QPushButton("Update Parameters");
    connect(updateParamsButton, &QPushButton::clicked, 
            this, &MainWindow::updateSpecificParameter);
    paramsLayout->addWidget(updateParamsButton);
    
    paramsGroup->setLayout(paramsLayout);
    propertiesLayout->addWidget(paramsGroup);
    
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
    
    infoLayout->addRow("Area:", m_areaLabel);
    infoLayout->addRow("Perimeter:", m_perimeterLabel);
    infoLayout->addRow("Center of Mass:", m_centerLabel);
    infoLayout->addRow("Vertices:", m_verticesLabel);
    infoLayout->addRow("Triangles:", m_trianglesLabel);
    
    QPushButton *showCenterButton = new QPushButton("Show Center Info");
    connect(showCenterButton, &QPushButton::clicked, this, &MainWindow::showCenterInfo);
    infoLayout->addRow(showCenterButton);
    
    m_infoDock->setWidget(infoWidget);
    addDockWidget(Qt::BottomDockWidgetArea, m_infoDock);
    
    // Set initial sizes
    m_figuresDock->setMinimumWidth(200);
    m_propertiesDock->setMinimumWidth(250);
    m_transformationsDock->setMinimumWidth(250);
    m_infoDock->setMaximumHeight(150);
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
                                                   "", "Geometry Files (*.geom)");
    if (!fileName.isEmpty())
    {
        // TODO: Implement file loading
        statusBar()->showMessage("Loaded: " + fileName, 3000);
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Project", 
                                                   "project.geom", "Geometry Files (*.geom)");
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
                                                   "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty())
    {
        QPixmap pixmap(m_canvas->size());
        m_canvas->render(&pixmap);
        pixmap.save(fileName);
        statusBar()->showMessage("Exported: " + fileName, 3000);
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

void MainWindow::removeSelectedFigure()
{
    if (m_currentFigure)
    {
        m_canvas->removeFigure(m_currentFigure);
        m_currentFigure->deleteLater();
        m_currentFigure = nullptr;
        
        updateFigureInfo();
        updateFigureList();
        
        if (m_figureList->count() > 0)
            m_figureList->setCurrentRow(0);
        
        statusBar()->showMessage("Figure removed", 2000);
    }
}

void MainWindow::clearAllFigures()
{
    int result = QMessageBox::question(this, "Clear All", 
                                      "Remove all figures?",
                                      QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes)
    {
        m_canvas->clearFigures();
        updateFigureInfo();
        updateFigureList();
        m_currentFigure = nullptr;
        statusBar()->showMessage("All figures cleared", 2000);
    }
}

void MainWindow::updateFigureList()
{
    m_figureList->clear();
    for (Figure *figure : m_canvas->getFigures())
    {
        m_figureList->addItem(QString("%1 - Area: %2, Center: (%3, %4)")
            .arg(figure->type())
            .arg(figure->area(), 0, 'f', 1)
            .arg(figure->centerOfMass().x(), 0, 'f', 0)
            .arg(figure->centerOfMass().y(), 0, 'f', 0));
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
    }
}

void MainWindow::updateFigureInfo()
{
    if (m_currentFigure)
    {
        m_areaLabel->setText(QString::number(m_currentFigure->area(), 'f', 2));
        m_perimeterLabel->setText(QString::number(m_currentFigure->perimeter(), 'f', 2));
        
        QPointF center = m_currentFigure->centerOfMass();
        m_centerLabel->setText(QString("(%1, %2)").arg(center.x(), 0, 'f', 1).arg(center.y(), 0, 'f', 1));
        
        if (PolygonFigure *polygon = dynamic_cast<PolygonFigure*>(m_currentFigure))
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
    
    if (Circle *circle = dynamic_cast<Circle*>(m_currentFigure))
    {
        m_paramTabs->setCurrentWidget(m_circleParams);
        m_radiusSpinBox->setValue(circle->radius());
    }
    else if (Rectangle *rect = dynamic_cast<Rectangle*>(m_currentFigure))
    {
        m_paramTabs->setCurrentWidget(m_rectangleParams);
        m_widthSpinBox->setValue(rect->width());
        m_heightSpinBox->setValue(rect->height());
    }
    else if (Square *square = dynamic_cast<Square*>(m_currentFigure))
    {
        m_paramTabs->setCurrentWidget(m_squareParams);
        m_sideSpinBox->setValue(square->side());
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(m_currentFigure))
    {
        m_paramTabs->setCurrentWidget(m_rhombusParams);
        m_diag1SpinBox->setValue(rhombus->diagonal1());
        m_diag2SpinBox->setValue(rhombus->diagonal2());
    }
    else if (Hexagon *hexagon = dynamic_cast<Hexagon*>(m_currentFigure))
    {
        m_paramTabs->setCurrentWidget(m_circleParams); // Reuse circle params for radius
        m_radiusSpinBox->setValue(hexagon->radius());
    }
    else if (Star *star = dynamic_cast<Star*>(m_currentFigure))
    {
        m_paramTabs->setCurrentWidget(m_starParams);
        m_starTypeCombo->setCurrentIndex(static_cast<int>(star->starType()) - 5);
        m_outerRadiusSpinBox->setValue(star->outerRadius());
        m_innerRadiusSpinBox->setValue(star->innerRadius());
    }
    else if (CustomFigure *custom = dynamic_cast<CustomFigure*>(m_currentFigure))
    {
        m_paramTabs->setCurrentWidget(m_polygonParams);
        m_sidesSpinBox->setValue(custom->sides());
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
    }
}

void MainWindow::updateLineWidth()
{
    if (m_currentFigure)
    {
        m_currentFigure->setLineWidth(m_lineWidthSpinBox->value());
        m_canvas->update();
    }
}

void MainWindow::updateSpecificParameter()
{
    if (!m_currentFigure) return;
    
    if (Circle *circle = dynamic_cast<Circle*>(m_currentFigure))
    {
        circle->setRadius(m_radiusSpinBox->value());
    }
    else if (Rectangle *rect = dynamic_cast<Rectangle*>(m_currentFigure))
    {
        rect->setWidth(m_widthSpinBox->value());
        rect->setHeight(m_heightSpinBox->value());
    }
    else if (Square *square = dynamic_cast<Square*>(m_currentFigure))
    {
        square->setSide(m_sideSpinBox->value());
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(m_currentFigure))
    {
        rhombus->setDiagonal1(m_diag1SpinBox->value());
        rhombus->setDiagonal2(m_diag2SpinBox->value());
    }
    else if (Hexagon *hexagon = dynamic_cast<Hexagon*>(m_currentFigure))
    {
        hexagon->setRadius(m_radiusSpinBox->value());
    }
    else if (Star *star = dynamic_cast<Star*>(m_currentFigure))
    {
        Star::StarType starType = static_cast<Star::StarType>(5 + m_starTypeCombo->currentIndex());
        star->setStarType(starType);
        star->setOuterRadius(m_outerRadiusSpinBox->value());
        star->setInnerRadius(m_innerRadiusSpinBox->value());
    }
    else if (CustomFigure *custom = dynamic_cast<CustomFigure*>(m_currentFigure))
    {
        custom->setSides(m_sidesSpinBox->value());
    }
    
    updateFigureInfo();
    updateFigureList();
    m_canvas->update();
    statusBar()->showMessage("Parameters updated", 2000);
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
}

void MainWindow::toggleCenters(bool enabled)
{
    m_canvas->setShowCenters(enabled);
}

void MainWindow::toggleTriangulation(bool enabled)
{
    m_canvas->setShowTriangulation(enabled);
}

void MainWindow::toggleVertices(bool enabled)
{
    m_canvas->setShowVertices(enabled);
}

void MainWindow::toggleBoundingBox(bool enabled)
{
    m_canvas->setShowBoundingBox(enabled);
}

void MainWindow::zoomIn()
{
    m_canvas->zoomIn();
}

void MainWindow::zoomOut()
{
    m_canvas->zoomOut();
}

void MainWindow::resetView()
{
    m_canvas->resetView();
    statusBar()->showMessage("View reset", 2000);
}

void MainWindow::fitToView()
{
    if (m_canvas->getFigures().isEmpty())
        return;
    
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
        "<li>Create various geometric figures</li>"
        "<li>Transform figures (move, rotate, scale)</li>"
        "<li>Animate transformations</li>"
        "<li>Calculate area, perimeter, center of mass</li>"
        "<li>Visualize triangulation</li>"
        "</ul>"
        "<p>Developed for educational purposes.</p>");
}

void MainWindow::showHelp()
{
    QMessageBox::information(this, "Help", 
        "<h3>Geometry Figures Application Help</h3>"
        "<p><b>Creating Figures:</b><br>"
        "Use the Figure menu or toolbar to create new figures. "
        "Figures can also be created from the Figures dock.</p>"
        "<p><b>Selecting Figures:</b><br>"
        "Click on a figure to select it. Selected figures show a bounding box "
        "and can be manipulated.</p>"
        "<p><b>Transforming Figures:</b><br>"
        "Use the Transformations dock to move, rotate, or scale figures. "
        "Transformations can be applied immediately or animated over 2 seconds.</p>"
        "<p><b>Modifying Properties:</b><br>"
        "Use the Properties dock to change colors, line width, and figure-specific "
        "parameters like radius, width, height, etc.</p>"
        "<p><b>View Controls:</b><br>"
        "- Zoom: Use mouse wheel or View menu<br>"
        "- Pan: Middle-click and drag<br>"
        "- Reset View: View → Reset View or Ctrl+R</p>"
        "<p><b>Figure Information:</b><br>"
        "The bottom dock shows detailed information about the selected figure.</p>");
}