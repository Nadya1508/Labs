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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_canvas(new FigureCanvas(this))
    , m_currentFigure(nullptr)
    , m_currentLineColor(Qt::blue)
    , m_currentFillColor(Qt::lightGray)
{
    setupUI();
    
    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(100);
    connect(m_updateTimer, &QTimer::timeout, this, &MainWindow::updateCanvas);
    m_updateTimer->start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    setWindowTitle("Geometry Figures App");
    setGeometry(100, 100, 1400, 800);
    
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    
    // ============ ЛЕВАЯ ПАНЕЛЬ - КАНВАС ============
    QVBoxLayout *canvasLayout = new QVBoxLayout();
    canvasLayout->addWidget(m_canvas);
    QGroupBox *canvasGroup = new QGroupBox("Canvas");
    canvasGroup->setLayout(canvasLayout);
    mainLayout->addWidget(canvasGroup, 3);
    
    // ============ ПРАВАЯ ПАНЕЛЬ - УПРАВЛЕНИЕ ============
    QWidget *controlPanel = new QWidget();
    QVBoxLayout *controlLayout = new QVBoxLayout(controlPanel);
    
    // ----- 1. СОЗДАНИЕ ФИГУР -----
    QGroupBox *creationGroup = new QGroupBox("Create Figure");
    QFormLayout *creationLayout = new QFormLayout();
    
    m_figureTypeCombo = new QComboBox();
    m_figureTypeCombo->addItems({"Triangle", "Rectangle", "Square", "Rhombus", 
                                 "Hexagon", "Star", "Circle", "CustomFigure"});
    creationLayout->addRow("Type:", m_figureTypeCombo);
    
    QPushButton *createButton = new QPushButton("Create");
    connect(createButton, &QPushButton::clicked, this, &MainWindow::createFigure);
    creationLayout->addRow(createButton);
    
    QPushButton *removeButton = new QPushButton("Remove Selected");
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeFigure);
    creationLayout->addRow(removeButton);
    
    creationGroup->setLayout(creationLayout);
    controlLayout->addWidget(creationGroup);
    
    // ----- 2. СПИСОК ФИГУР -----
    QGroupBox *listGroup = new QGroupBox("Figures");
    QVBoxLayout *listLayout = new QVBoxLayout();
    m_figureList = new QListWidget();
    connect(m_figureList, &QListWidget::currentRowChanged, this, &MainWindow::updateSelectedFigure);
    listLayout->addWidget(m_figureList);
    listGroup->setLayout(listLayout);
    controlLayout->addWidget(listGroup);
    
    // ----- 3. ИНФОРМАЦИЯ О ФИГУРЕ -----
    QGroupBox *infoGroup = new QGroupBox("Figure Info");
    QFormLayout *infoLayout = new QFormLayout();
    m_areaLabel = new QLabel("0.0");
    m_perimeterLabel = new QLabel("0.0");
    m_centerLabel = new QLabel("(0, 0)");
    infoLayout->addRow("Area:", m_areaLabel);
    infoLayout->addRow("Perimeter:", m_perimeterLabel);
    infoLayout->addRow("Center of Mass:", m_centerLabel);
    infoGroup->setLayout(infoLayout);
    controlLayout->addWidget(infoGroup);
    
    // ----- 4. ПРЕОБРАЗОВАНИЯ -----
    QGroupBox *transformGroup = new QGroupBox("Transformations");
    QVBoxLayout *transformLayout = new QVBoxLayout();
    
    // Перемещение
    QGroupBox *moveGroup = new QGroupBox("Move");
    QFormLayout *moveLayout = new QFormLayout();
    m_moveXSpinBox = new QDoubleSpinBox();
    m_moveXSpinBox->setRange(-500, 500);
    m_moveXSpinBox->setValue(20);
    moveLayout->addRow("ΔX:", m_moveXSpinBox);
    m_moveYSpinBox = new QDoubleSpinBox();
    m_moveYSpinBox->setRange(-500, 500);
    m_moveYSpinBox->setValue(20);
    moveLayout->addRow("ΔY:", m_moveYSpinBox);
    moveGroup->setLayout(moveLayout);
    transformLayout->addWidget(moveGroup);
    
    // Поворот
    QGroupBox *rotateGroup = new QGroupBox("Rotate");
    QFormLayout *rotateLayout = new QFormLayout();
    m_rotateAngleSpinBox = new QDoubleSpinBox();
    m_rotateAngleSpinBox->setRange(-360, 360);
    m_rotateAngleSpinBox->setValue(45);
    rotateLayout->addRow("Angle (degrees):", m_rotateAngleSpinBox);
    m_rotateCenterXSpinBox = new QDoubleSpinBox();
    m_rotateCenterXSpinBox->setRange(-500, 500);
    m_rotateCenterXSpinBox->setValue(0);
    rotateLayout->addRow("Center X:", m_rotateCenterXSpinBox);
    m_rotateCenterYSpinBox = new QDoubleSpinBox();
    m_rotateCenterYSpinBox->setRange(-500, 500);
    m_rotateCenterYSpinBox->setValue(0);
    rotateLayout->addRow("Center Y:", m_rotateCenterYSpinBox);
    rotateGroup->setLayout(rotateLayout);
    transformLayout->addWidget(rotateGroup);
    
    // Масштабирование
    QGroupBox *scaleGroup = new QGroupBox("Scale");
    QFormLayout *scaleLayout = new QFormLayout();
    m_scaleFactorSpinBox = new QDoubleSpinBox();
    m_scaleFactorSpinBox->setRange(0.1, 5.0);
    m_scaleFactorSpinBox->setValue(1.5);
    scaleLayout->addRow("Scale Factor:", m_scaleFactorSpinBox);
    m_scaleCenterXSpinBox = new QDoubleSpinBox();
    m_scaleCenterXSpinBox->setRange(-500, 500);
    m_scaleCenterXSpinBox->setValue(0);
    scaleLayout->addRow("Center X:", m_scaleCenterXSpinBox);
    m_scaleCenterYSpinBox = new QDoubleSpinBox();
    m_scaleCenterYSpinBox->setRange(-500, 500);
    m_scaleCenterYSpinBox->setValue(0);
    scaleLayout->addRow("Center Y:", m_scaleCenterYSpinBox);
    scaleGroup->setLayout(scaleLayout);
    transformLayout->addWidget(scaleGroup);
    
    // Кнопки преобразований
    QHBoxLayout *transformButtonsLayout = new QHBoxLayout();
    QPushButton *applyButton = new QPushButton("Apply");
    QPushButton *animateButton = new QPushButton("Animate (2 sec)");
    connect(applyButton, &QPushButton::clicked, this, &MainWindow::applyTransformation);
    connect(animateButton, &QPushButton::clicked, this, &MainWindow::animateTransformation);
    transformButtonsLayout->addWidget(applyButton);
    transformButtonsLayout->addWidget(animateButton);
    transformLayout->addLayout(transformButtonsLayout);
    
    transformGroup->setLayout(transformLayout);
    controlLayout->addWidget(transformGroup);
    
    // ----- 5. УПРАВЛЕНИЕ ПАРАМЕТРАМИ -----
    QGroupBox *paramsGroup = new QGroupBox("Figure Parameters");
    QVBoxLayout *paramsLayout = new QVBoxLayout();
    
    // Цвета
    QGroupBox *colorGroup = new QGroupBox("Colors");
    QFormLayout *colorLayout = new QFormLayout();
    m_lineColorButton = new QPushButton("Line Color");
    m_lineColorButton->setStyleSheet("background-color: blue;");
    connect(m_lineColorButton, &QPushButton::clicked, this, &MainWindow::chooseLineColor);
    m_fillColorButton = new QPushButton("Fill Color");
    m_fillColorButton->setStyleSheet("background-color: lightgray;");
    connect(m_fillColorButton, &QPushButton::clicked, this, &MainWindow::chooseFillColor);
    colorLayout->addRow(m_lineColorButton);
    colorLayout->addRow(m_fillColorButton);
    colorGroup->setLayout(colorLayout);
    paramsLayout->addWidget(colorGroup);
    
    // Толщина линии
    QGroupBox *styleGroup = new QGroupBox("Style");
    QFormLayout *styleLayout = new QFormLayout();
    m_lineWidthSpinBox = new QSpinBox();
    m_lineWidthSpinBox->setRange(1, 10);
    m_lineWidthSpinBox->setValue(2);
    connect(m_lineWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &MainWindow::updateLineWidth);
    styleLayout->addRow("Line Width:", m_lineWidthSpinBox);
    styleGroup->setLayout(styleLayout);
    paramsLayout->addWidget(styleGroup);
    
    // Специфические параметры
    QGroupBox *specificGroup = new QGroupBox("Specific Parameters");
    QFormLayout *specificLayout = new QFormLayout();
    m_radiusSpinBox = new QDoubleSpinBox();
    m_radiusSpinBox->setRange(10, 200);
    m_radiusSpinBox->setValue(50);
    m_radiusSpinBox->setEnabled(false);
    connect(m_radiusSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateRadius);
    m_widthSpinBox = new QDoubleSpinBox();
    m_widthSpinBox->setRange(10, 200);
    m_widthSpinBox->setValue(100);
    m_widthSpinBox->setEnabled(false);
    connect(m_widthSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateWidth);
    m_heightSpinBox = new QDoubleSpinBox();
    m_heightSpinBox->setRange(10, 200);
    m_heightSpinBox->setValue(80);
    m_heightSpinBox->setEnabled(false);
    connect(m_heightSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateHeight);
    specificLayout->addRow("Radius:", m_radiusSpinBox);
    specificLayout->addRow("Width:", m_widthSpinBox);
    specificLayout->addRow("Height:", m_heightSpinBox);
    specificGroup->setLayout(specificLayout);
    paramsLayout->addWidget(specificGroup);
    
    // Перемещение центра
    QGroupBox *centerGroup = new QGroupBox("Move Center");
    QFormLayout *centerLayout = new QFormLayout();
    m_newCenterXSpinBox = new QDoubleSpinBox();
    m_newCenterXSpinBox->setRange(-500, 500);
    m_newCenterXSpinBox->setValue(100);
    centerLayout->addRow("New Center X:", m_newCenterXSpinBox);
    m_newCenterYSpinBox = new QDoubleSpinBox();
    m_newCenterYSpinBox->setRange(-500, 500);
    m_newCenterYSpinBox->setValue(100);
    centerLayout->addRow("New Center Y:", m_newCenterYSpinBox);
    QPushButton *moveCenterButton = new QPushButton("Move Center");
    connect(moveCenterButton, &QPushButton::clicked, this, &MainWindow::moveCenterToPoint);
    centerLayout->addRow(moveCenterButton);
    centerGroup->setLayout(centerLayout);
    paramsLayout->addWidget(centerGroup);
    
    paramsGroup->setLayout(paramsLayout);
    controlLayout->addWidget(paramsGroup);
    
    // ----- 6. НАСТРОЙКИ КАНВАСА -----
    QGroupBox *settingsGroup = new QGroupBox("Canvas Settings");
    QVBoxLayout *settingsLayout = new QVBoxLayout();
    m_gridCheckBox = new QCheckBox("Show Grid");
    m_gridCheckBox->setChecked(true);
    connect(m_gridCheckBox, &QCheckBox::toggled, m_canvas, &FigureCanvas::setGridEnabled);
    m_centersCheckBox = new QCheckBox("Show Centers");
    m_centersCheckBox->setChecked(true);
    connect(m_centersCheckBox, &QCheckBox::toggled, m_canvas, &FigureCanvas::setShowCenters);
    m_triangulationCheckBox = new QCheckBox("Show Triangulation");
    m_triangulationCheckBox->setChecked(false);
    connect(m_triangulationCheckBox, &QCheckBox::toggled, m_canvas, &FigureCanvas::setShowTriangulation);
    settingsLayout->addWidget(m_gridCheckBox);
    settingsLayout->addWidget(m_centersCheckBox);
    settingsLayout->addWidget(m_triangulationCheckBox);
    settingsGroup->setLayout(settingsLayout);
    controlLayout->addWidget(settingsGroup);
    
    // ----- 7. ФАЙЛОВЫЕ ОПЕРАЦИИ -----
    QGroupBox *fileGroup = new QGroupBox("File Operations");
    QHBoxLayout *fileLayout = new QHBoxLayout();
    QPushButton *saveButton = new QPushButton("Save");
    QPushButton *loadButton = new QPushButton("Load");
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFigure);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFigure);
    fileLayout->addWidget(saveButton);
    fileLayout->addWidget(loadButton);
    fileGroup->setLayout(fileLayout);
    controlLayout->addWidget(fileGroup);
    
    // ----- 8. СБРОС -----
    QPushButton *resetButton = new QPushButton("Reset View");
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetView);
    controlLayout->addWidget(resetButton);
    
    // ----- 9. ПРОГРЕСС АНИМАЦИИ -----
    m_animationProgressBar = new QProgressBar();
    m_animationProgressBar->setRange(0, 100);
    m_animationProgressBar->setValue(0);
    m_animationProgressBar->setVisible(false);
    controlLayout->addWidget(m_animationProgressBar);
    
    controlLayout->addStretch();
    mainLayout->addWidget(controlPanel, 1);
    setCentralWidget(centralWidget);
    
    // Создаем несколько фигур по умолчанию
    createFigureByType("Triangle");
    createFigureByType("Circle");
    createFigureByType("Star");
}

// ============ МЕТОДЫ ДЛЯ ФИГУР ============

void MainWindow::createFigure()
{
    QString type = m_figureTypeCombo->currentText();
    Figure *figure = createFigureByType(type);
    
    if (figure)
    {
        figure->setColor(m_currentLineColor);
        figure->setFillColor(m_currentFillColor);
        figure->setLineWidth(m_lineWidthSpinBox->value());
        
        m_canvas->addFigure(figure);
        updateFigureList();
        m_figureList->setCurrentRow(m_figureList->count() - 1);
    }
}

Figure* MainWindow::createFigureByType(const QString &type)
{
    Figure *figure = nullptr;
    int centerX = 200 + QRandomGenerator::global()->bounded(200);
    int centerY = 200 + QRandomGenerator::global()->bounded(200);
    QPointF center(centerX, centerY);
    
    if (type == "Triangle")
    {
        QPointF p1(center.x() - 40, center.y() + 40);
        QPointF p2(center.x() + 40, center.y() + 40);
        QPointF p3(center.x(), center.y() - 40);
        figure = new Triangle(p1, p2, p3, this);
    }
    else if (type == "Rectangle")
    {
        figure = new Rectangle(center, 80, 60, this);
    }
    else if (type == "Square")
    {
        figure = new Square(center, 70, this);
    }
    else if (type == "Rhombus")
    {
        figure = new Rhombus(center, 80, 60, this);
    }
    else if (type == "Hexagon")
    {
        figure = new Hexagon(center, 50, this);
    }
    else if (type == "Star")
    {
        Star::StarType starType = Star::FivePointed;
        int starChoice = QRandomGenerator::global()->bounded(3);
        if (starChoice == 0) starType = Star::FivePointed;
        else if (starChoice == 1) starType = Star::SixPointed;
        else starType = Star::EightPointed;
        
        figure = new Star(center, 50, 25, starType, this);
    }
    else if (type == "Circle")
    {
        figure = new Circle(center, 40, this);
    }
    else if (type == "CustomFigure")
    {
        figure = new CustomFigure(center, 45, 7, this);
    }
    
    return figure;
}

void MainWindow::removeFigure()
{
    int row = m_figureList->currentRow();
    if (row >= 0 && row < m_canvas->getFigures().size())
    {
        Figure *figure = m_canvas->getFigures()[row];
        m_canvas->removeFigure(figure);
        figure->deleteLater();
        
        updateFigureInfo();
        updateFigureList();
        
        if (m_figureList->count() > 0)
            m_figureList->setCurrentRow(qMin(row, m_figureList->count() - 1));
        else
            m_currentFigure = nullptr;
    }
}

void MainWindow::updateFigureList()
{
    m_figureList->clear();
    for (Figure *figure : m_canvas->getFigures())
    {
        m_figureList->addItem(QString("%1 (Area: %2)")
            .arg(figure->type())
            .arg(figure->area(), 0, 'f', 1));
    }
}

void MainWindow::updateSelectedFigure()
{
    int row = m_figureList->currentRow();
    if (row >= 0 && row < m_canvas->getFigures().size())
    {
        m_currentFigure = m_canvas->getFigures()[row];
        updateFigureInfo();
        updateParameterControls();
    }
    else
    {
        m_currentFigure = nullptr;
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
    }
    else
    {
        m_areaLabel->setText("0.0");
        m_perimeterLabel->setText("0.0");
        m_centerLabel->setText("(0, 0)");
    }
}

void MainWindow::updateParameterControls()
{
    if (!m_currentFigure)
    {
        m_radiusSpinBox->setEnabled(false);
        m_widthSpinBox->setEnabled(false);
        m_heightSpinBox->setEnabled(false);
        return;
    }
    
    // Обновляем цвета кнопок
    m_lineColorButton->setStyleSheet(QString("background-color: %1;").arg(m_currentFigure->getColor().name()));
    m_fillColorButton->setStyleSheet(QString("background-color: %1;").arg(m_currentFigure->fillColor().name()));
    
    // Обновляем толщину линии
    m_lineWidthSpinBox->setValue(m_currentFigure->lineWidth());
    
    // Обновляем специфические параметры
    if (Circle *circle = dynamic_cast<Circle*>(m_currentFigure))
    {
        m_radiusSpinBox->setEnabled(true);
        m_widthSpinBox->setEnabled(false);
        m_heightSpinBox->setEnabled(false);
        m_radiusSpinBox->setValue(circle->radius());
    }
    else if (Rectangle *rect = dynamic_cast<Rectangle*>(m_currentFigure))
    {
        m_radiusSpinBox->setEnabled(false);
        m_widthSpinBox->setEnabled(true);
        m_heightSpinBox->setEnabled(true);
        m_widthSpinBox->setValue(rect->width());
        m_heightSpinBox->setValue(rect->height());
    }
    else if (Square *square = dynamic_cast<Square*>(m_currentFigure))
    {
        m_radiusSpinBox->setEnabled(false);
        m_widthSpinBox->setEnabled(true);
        m_heightSpinBox->setEnabled(false);
        m_widthSpinBox->setValue(square->side());
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(m_currentFigure))
    {
        m_radiusSpinBox->setEnabled(false);
        m_widthSpinBox->setEnabled(true);
        m_heightSpinBox->setEnabled(true);
        m_widthSpinBox->setValue(rhombus->diagonal1());
        m_heightSpinBox->setValue(rhombus->diagonal2());
    }
    else if (Hexagon *hexagon = dynamic_cast<Hexagon*>(m_currentFigure))
    {
        m_radiusSpinBox->setEnabled(true);
        m_widthSpinBox->setEnabled(false);
        m_heightSpinBox->setEnabled(false);
        m_radiusSpinBox->setValue(hexagon->radius());
    }
    else if (Star *star = dynamic_cast<Star*>(m_currentFigure))
    {
        m_radiusSpinBox->setEnabled(true);
        m_widthSpinBox->setEnabled(false);
        m_heightSpinBox->setEnabled(false);
        m_radiusSpinBox->setValue(star->outerRadius());
    }
    else if (CustomFigure *custom = dynamic_cast<CustomFigure*>(m_currentFigure))
    {
        m_radiusSpinBox->setEnabled(true);
        m_widthSpinBox->setEnabled(false);
        m_heightSpinBox->setEnabled(false);
        m_radiusSpinBox->setValue(custom->radius());
    }
    else
    {
        m_radiusSpinBox->setEnabled(false);
        m_widthSpinBox->setEnabled(false);
        m_heightSpinBox->setEnabled(false);
    }
    
    // Обновляем позицию центра
    if (m_currentFigure)
    {
        QPointF center = m_currentFigure->centerOfMass();
        m_newCenterXSpinBox->setValue(center.x());
        m_newCenterYSpinBox->setValue(center.y());
    }
}

// ============ ПРЕОБРАЗОВАНИЯ ============

void MainWindow::applyTransformation()
{
    if (!m_currentFigure)
    {
        QMessageBox::warning(this, "Warning", "Please select a figure first!");
        return;
    }
    
    // 1. Перемещение
    QPointF moveOffset(m_moveXSpinBox->value(), m_moveYSpinBox->value());
    if (!moveOffset.isNull())
    {
        m_currentFigure->move(moveOffset);
        qDebug() << "Moved by:" << moveOffset;
    }
    
    // 2. Поворот
    double angle = m_rotateAngleSpinBox->value();
    if (qAbs(angle) > 0.001)
    {
        QPointF rotateCenter(m_rotateCenterXSpinBox->value(), m_rotateCenterYSpinBox->value());
        if (rotateCenter.isNull())
            rotateCenter = m_currentFigure->centerOfMass();
        
        m_currentFigure->rotate(angle, rotateCenter);
        qDebug() << "Rotated by" << angle << "degrees around" << rotateCenter;
    }
    
    // 3. Масштабирование
    double factor = m_scaleFactorSpinBox->value();
    if (qAbs(factor - 1.0) > 0.001)
    {
        QPointF scaleCenter(m_scaleCenterXSpinBox->value(), m_scaleCenterYSpinBox->value());
        if (scaleCenter.isNull())
            scaleCenter = m_currentFigure->centerOfMass();
        
        m_currentFigure->scale(factor, scaleCenter);
        qDebug() << "Scaled by factor" << factor << "around" << scaleCenter;
    }
    
    updateFigureInfo();
    updateFigureList();
    updateParameterControls();
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
    
    // Подключаем сигналы анимации
    connect(m_currentFigure, &Figure::animationProgress,
            m_animationProgressBar, &QProgressBar::setValue);
    connect(m_currentFigure, &Figure::animationFinished, this, [this]() {
        m_animationProgressBar->setVisible(false);
        updateFigureInfo();
    });
    
    // Получаем текущий центр
    QPointF currentCenter = m_currentFigure->centerOfMass();
    
    // Рассчитываем целевые точки для анимации
    QPointF moveTarget = currentCenter + QPointF(m_moveXSpinBox->value(), m_moveYSpinBox->value());
    double rotateAngle = m_rotateAngleSpinBox->value();
    double scaleFactor = m_scaleFactorSpinBox->value();
    
    // Определяем центр для поворота и масштабирования
    QPointF transformCenter(currentCenter);
    if (m_rotateCenterXSpinBox->value() != 0 || m_rotateCenterYSpinBox->value() != 0)
        transformCenter = QPointF(m_rotateCenterXSpinBox->value(), m_rotateCenterYSpinBox->value());
    if (m_scaleCenterXSpinBox->value() != 0 || m_scaleCenterYSpinBox->value() != 0)
        transformCenter = QPointF(m_scaleCenterXSpinBox->value(), m_scaleCenterYSpinBox->value());
    
    // Запускаем анимации
    if (!QPointF(m_moveXSpinBox->value(), m_moveYSpinBox->value()).isNull())
    {
        m_currentFigure->animateMove(moveTarget, 2000);
    }
    else if (qAbs(rotateAngle) > 0.001)
    {
        m_currentFigure->animateRotate(rotateAngle, transformCenter, 2000);
    }
    else if (qAbs(scaleFactor - 1.0) > 0.001)
    {
        m_currentFigure->animateScale(scaleFactor, transformCenter, 2000);
    }
}

void MainWindow::updateAnimationProgress(double progress)
{
    m_animationProgressBar->setValue(static_cast<int>(progress * 100));
}

// ============ УПРАВЛЕНИЕ ПАРАМЕТРАМИ ============

void MainWindow::chooseLineColor()
{
    QColor color = QColorDialog::getColor(m_currentLineColor, this, "Choose Line Color");
    if (color.isValid())
    {
        m_currentLineColor = color;
        m_lineColorButton->setStyleSheet(QString("background-color: %1;").arg(color.name()));
        if (m_currentFigure)
        {
            m_currentFigure->setColor(color);
            updateCanvas();
        }
    }
}

void MainWindow::chooseFillColor()
{
    QColor color = QColorDialog::getColor(m_currentFillColor, this, "Choose Fill Color");
    if (color.isValid())
    {
        m_currentFillColor = color;
        m_fillColorButton->setStyleSheet(QString("background-color: %1;").arg(color.name()));
        if (m_currentFigure)
        {
            m_currentFigure->setFillColor(color);
            updateCanvas();
        }
    }
}

void MainWindow::updateLineWidth()
{
    if (m_currentFigure)
    {
        m_currentFigure->setLineWidth(m_lineWidthSpinBox->value());
        updateCanvas();
    }
}

void MainWindow::updateRadius()
{
    if (!m_currentFigure) return;
    
    if (Circle *circle = dynamic_cast<Circle*>(m_currentFigure))
    {
        circle->setRadius(m_radiusSpinBox->value());
    }
    else if (Hexagon *hexagon = dynamic_cast<Hexagon*>(m_currentFigure))
    {
        hexagon->setRadius(m_radiusSpinBox->value());
    }
    else if (Star *star = dynamic_cast<Star*>(m_currentFigure))
    {
        star->setOuterRadius(m_radiusSpinBox->value());
    }
    else if (CustomFigure *custom = dynamic_cast<CustomFigure*>(m_currentFigure))
    {
        custom->setRadius(m_radiusSpinBox->value());
    }
    
    updateFigureInfo();
    updateFigureList();
    updateCanvas();
}

void MainWindow::updateWidth()
{
    if (!m_currentFigure) return;
    
    if (Rectangle *rect = dynamic_cast<Rectangle*>(m_currentFigure))
    {
        rect->setWidth(m_widthSpinBox->value());
    }
    else if (Square *square = dynamic_cast<Square*>(m_currentFigure))
    {
        square->setSide(m_widthSpinBox->value());
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(m_currentFigure))
    {
        rhombus->setDiagonal1(m_widthSpinBox->value());
    }
    
    updateFigureInfo();
    updateFigureList();
    updateCanvas();
}

void MainWindow::updateHeight()
{
    if (!m_currentFigure) return;
    
    if (Rectangle *rect = dynamic_cast<Rectangle*>(m_currentFigure))
    {
        rect->setHeight(m_heightSpinBox->value());
    }
    else if (Rhombus *rhombus = dynamic_cast<Rhombus*>(m_currentFigure))
    {
        rhombus->setDiagonal2(m_heightSpinBox->value());
    }
    
    updateFigureInfo();
    updateFigureList();
    updateCanvas();
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
    updateCanvas();
    
    qDebug() << "Moved center to:" << newCenter;
}

// ============ ФАЙЛОВЫЕ ОПЕРАЦИИ ============

void MainWindow::saveFigure()
{
    if (!m_currentFigure)
    {
        QMessageBox::warning(this, "Warning", "No figure selected!");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "Save Figure", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;
    
    QMessageBox::information(this, "Info", "Figure saved to: " + fileName);
}

void MainWindow::loadFigure()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Figure", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;
    
    QMessageBox::information(this, "Info", "Figure loaded from: " + fileName);
}

// ============ ПРОЧИЕ МЕТОДЫ ============

void MainWindow::updateCanvas()
{
    m_canvas->update();
}

void MainWindow::resetView()
{
    m_moveXSpinBox->setValue(20);
    m_moveYSpinBox->setValue(20);
    m_rotateAngleSpinBox->setValue(45);
    m_rotateCenterXSpinBox->setValue(0);
    m_rotateCenterYSpinBox->setValue(0);
    m_scaleFactorSpinBox->setValue(1.5);
    m_scaleCenterXSpinBox->setValue(0);
    m_scaleCenterYSpinBox->setValue(0);
    
    m_currentLineColor = Qt::blue;
    m_currentFillColor = Qt::lightGray;
    m_lineColorButton->setStyleSheet("background-color: blue;");
    m_fillColorButton->setStyleSheet("background-color: lightgray;");
    m_lineWidthSpinBox->setValue(2);
    
    m_animationProgressBar->setVisible(false);
    
    updateCanvas();
}