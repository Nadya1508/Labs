// ЗАМЕНИТЕ ВЕСЬ СОДЕРЖИМОЕ на эту версию:

#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCheckBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_canvas(new FigureCanvas(this))
    , m_currentFigure(nullptr)
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
    setGeometry(100, 100, 1200, 700);
    
    // Основной layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    
    // Левая панель - канвас
    QVBoxLayout *canvasLayout = new QVBoxLayout();
    canvasLayout->addWidget(m_canvas);
    
    QGroupBox *canvasGroup = new QGroupBox("Canvas");
    canvasGroup->setLayout(canvasLayout);
    mainLayout->addWidget(canvasGroup, 3);
    
    // Правая панель - управление
    QWidget *controlPanel = new QWidget();
    QVBoxLayout *controlLayout = new QVBoxLayout(controlPanel);
    
    // Создание фигур
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
    
    // Список фигур
    QGroupBox *listGroup = new QGroupBox("Figures");
    QVBoxLayout *listLayout = new QVBoxLayout();
    
    m_figureList = new QListWidget();
    connect(m_figureList, &QListWidget::currentRowChanged, 
            this, &MainWindow::updateSelectedFigure);
    listLayout->addWidget(m_figureList);
    
    listGroup->setLayout(listLayout);
    controlLayout->addWidget(listGroup);
    
    // Информация о фигуре
    QGroupBox *infoGroup = new QGroupBox("Figure Info");
    QFormLayout *infoLayout = new QFormLayout();
    
    m_areaLabel = new QLabel("0.0");
    m_perimeterLabel = new QLabel("0.0");
    m_centerLabel = new QLabel("(0, 0)");
    
    infoLayout->addRow("Area:", m_areaLabel);
    infoLayout->addRow("Perimeter:", m_perimeterLabel);
    infoLayout->addRow("Center:", m_centerLabel);
    
    infoGroup->setLayout(infoLayout);
    controlLayout->addWidget(infoGroup);
    
    // Преобразования
    QGroupBox *transformGroup = new QGroupBox("Transformations");
    QVBoxLayout *transformLayout = new QVBoxLayout();
    
    // Перемещение
    QGroupBox *moveGroup = new QGroupBox("Move");
    QFormLayout *moveLayout = new QFormLayout();
    
    m_moveXSpinBox = new QDoubleSpinBox();
    m_moveXSpinBox->setRange(-1000, 1000);
    m_moveXSpinBox->setValue(0);
    moveLayout->addRow("X:", m_moveXSpinBox);
    
    m_moveYSpinBox = new QDoubleSpinBox();
    m_moveYSpinBox->setRange(-1000, 1000);
    m_moveYSpinBox->setValue(0);
    moveLayout->addRow("Y:", m_moveYSpinBox);
    
    moveGroup->setLayout(moveLayout);
    transformLayout->addWidget(moveGroup);
    
    // Поворот
    QGroupBox *rotateGroup = new QGroupBox("Rotate");
    QFormLayout *rotateLayout = new QFormLayout();
    
    m_rotateAngleSpinBox = new QDoubleSpinBox();
    m_rotateAngleSpinBox->setRange(-360, 360);
    m_rotateAngleSpinBox->setValue(45);
    rotateLayout->addRow("Angle:", m_rotateAngleSpinBox);
    
    m_rotateCenterXSpinBox = new QDoubleSpinBox();
    m_rotateCenterXSpinBox->setRange(-1000, 1000);
    m_rotateCenterXSpinBox->setValue(0);
    rotateLayout->addRow("Center X:", m_rotateCenterXSpinBox);
    
    m_rotateCenterYSpinBox = new QDoubleSpinBox();
    m_rotateCenterYSpinBox->setRange(-1000, 1000);
    m_rotateCenterYSpinBox->setValue(0);
    rotateLayout->addRow("Center Y:", m_rotateCenterYSpinBox);
    
    rotateGroup->setLayout(rotateLayout);
    transformLayout->addWidget(rotateGroup);
    
    // Масштабирование
    QGroupBox *scaleGroup = new QGroupBox("Scale");
    QFormLayout *scaleLayout = new QFormLayout();
    
    m_scaleFactorSpinBox = new QDoubleSpinBox();
    m_scaleFactorSpinBox->setRange(0.1, 10);
    m_scaleFactorSpinBox->setValue(1.5);
    scaleLayout->addRow("Factor:", m_scaleFactorSpinBox);
    
    m_scaleCenterXSpinBox = new QDoubleSpinBox();
    m_scaleCenterXSpinBox->setRange(-1000, 1000);
    m_scaleCenterXSpinBox->setValue(0);
    scaleLayout->addRow("Center X:", m_scaleCenterXSpinBox);
    
    m_scaleCenterYSpinBox = new QDoubleSpinBox();
    m_scaleCenterYSpinBox->setRange(-1000, 1000);
    m_scaleCenterYSpinBox->setValue(0);
    scaleLayout->addRow("Center Y:", m_scaleCenterYSpinBox);
    
    scaleGroup->setLayout(scaleLayout);
    transformLayout->addWidget(scaleGroup);
    
    // Кнопки применения
    QHBoxLayout *transformButtonsLayout = new QHBoxLayout();
    QPushButton *applyButton = new QPushButton("Apply");
    QPushButton *animateButton = new QPushButton("Animate");
    
    connect(applyButton, &QPushButton::clicked, this, &MainWindow::applyTransformation);
    connect(animateButton, &QPushButton::clicked, this, &MainWindow::animateTransformation);
    
    transformButtonsLayout->addWidget(applyButton);
    transformButtonsLayout->addWidget(animateButton);
    transformLayout->addLayout(transformButtonsLayout);
    
    transformGroup->setLayout(transformLayout);
    controlLayout->addWidget(transformGroup);
    
    // Настройки канваса
    QGroupBox *canvasSettingsGroup = new QGroupBox("Canvas Settings");
    QFormLayout *settingsLayout = new QFormLayout();
    
    QCheckBox *gridCheckBox = new QCheckBox("Show Grid");
    gridCheckBox->setChecked(true);
    connect(gridCheckBox, &QCheckBox::toggled, m_canvas, &FigureCanvas::setGridEnabled);
    
    QCheckBox *centersCheckBox = new QCheckBox("Show Centers");
    centersCheckBox->setChecked(true);
    connect(centersCheckBox, &QCheckBox::toggled, m_canvas, &FigureCanvas::setShowCenters);
    
    settingsLayout->addRow(gridCheckBox);
    settingsLayout->addRow(centersCheckBox);
    
    canvasSettingsGroup->setLayout(settingsLayout);
    controlLayout->addWidget(canvasSettingsGroup);
    
    // Кнопки сохранения/загрузки
    QHBoxLayout *fileButtonsLayout = new QHBoxLayout();
    QPushButton *saveButton = new QPushButton("Save");
    QPushButton *loadButton = new QPushButton("Load");
    
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFigure);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFigure);
    
    fileButtonsLayout->addWidget(saveButton);
    fileButtonsLayout->addWidget(loadButton);
    controlLayout->addLayout(fileButtonsLayout);
    
    controlLayout->addStretch();
    
    mainLayout->addWidget(controlPanel, 1);
    setCentralWidget(centralWidget);
    
    // Создаем несколько фигур по умолчанию
    createFigureByType("Triangle");
    createFigureByType("Circle");
    createFigureByType("Square");
}

void MainWindow::createFigure()
{
    QString type = m_figureTypeCombo->currentText();
    Figure *figure = createFigureByType(type);
    
    if (figure)
    {
        m_canvas->addFigure(figure);
        updateFigureList();
        m_figureList->setCurrentRow(m_figureList->count() - 1);
    }
}

Figure* MainWindow::createFigureByType(const QString &type)
{
    Figure *figure = nullptr;
    QPointF center(100 + QRandomGenerator::global()->bounded(400), 
                   100 + QRandomGenerator::global()->bounded(200));
    
    if (type == "Triangle")
    {
        figure = new Triangle(this);
    }
    else if (type == "Rectangle")
    {
        figure = new Rectangle(center, 80 + QRandomGenerator::global()->bounded(50), 
                               60 + QRandomGenerator::global()->bounded(40), this);
    }
    else if (type == "Square")
    {
        figure = new Square(center, 60 + QRandomGenerator::global()->bounded(40), this);
    }
    else if (type == "Rhombus")
    {
        figure = new Rhombus(center, 80 + QRandomGenerator::global()->bounded(40), 
                             60 + QRandomGenerator::global()->bounded(40), this);
    }
    else if (type == "Hexagon")
    {
        figure = new Hexagon(center, 50 + QRandomGenerator::global()->bounded(30), this);
    }
    else if (type == "Star")
    {
        Star::StarType starType = static_cast<Star::StarType>(5 + (QRandomGenerator::global()->bounded(3)) * 1);
        figure = new Star(center, 50 + QRandomGenerator::global()->bounded(30), 
                          25 + QRandomGenerator::global()->bounded(20), starType, this);
    }
    else if (type == "Circle")
    {
        figure = new Circle(center, 40 + QRandomGenerator::global()->bounded(30), this);
    }
    else if (type == "CustomFigure")
    {
        figure = new CustomFigure(center, 40 + QRandomGenerator::global()->bounded(30), 7, this);
    }
    
    if (figure)
    {
        // Случайный цвет
        QColor color(QRandomGenerator::global()->bounded(256), 
                     QRandomGenerator::global()->bounded(256), 
                     QRandomGenerator::global()->bounded(256));
        figure->setColor(color);
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
        updateFigureList();
        
        if (m_figureList->count() > 0)
        {
            m_figureList->setCurrentRow(qMin(row, m_figureList->count() - 1));
        }
        else
        {
            m_currentFigure = nullptr;
            updateFigureInfo();
        }
    }
}

void MainWindow::updateFigureList()
{
    m_figureList->clear();
    
    for (Figure *figure : m_canvas->getFigures())
    {
        m_figureList->addItem(QString("%1 (Area: %2)")
            .arg(figure->type())
            .arg(figure->area(), 0, 'f', 2));
    }
}

void MainWindow::updateSelectedFigure()
{
    int row = m_figureList->currentRow();
    if (row >= 0 && row < m_canvas->getFigures().size())
    {
        m_currentFigure = m_canvas->getFigures()[row];
        updateFigureInfo();
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
        m_centerLabel->setText(QString("(%1, %2)")
            .arg(center.x(), 0, 'f', 1)
            .arg(center.y(), 0, 'f', 1));
    }
    else
    {
        m_areaLabel->setText("0.0");
        m_perimeterLabel->setText("0.0");
        m_centerLabel->setText("(0, 0)");
    }
}

void MainWindow::applyTransformation()
{
    if (!m_currentFigure)
        return;
    
    // Перемещение
    QPointF moveOffset(m_moveXSpinBox->value(), m_moveYSpinBox->value());
    if (!moveOffset.isNull())
    {
        m_currentFigure->move(moveOffset);
    }
    
    // Поворот
    double angle = m_rotateAngleSpinBox->value();
    QPointF rotateCenter(m_rotateCenterXSpinBox->value(), m_rotateCenterYSpinBox->value());
    if (qAbs(angle) > 0.001)
    {
        if (rotateCenter.isNull())
            rotateCenter = m_currentFigure->centerOfMass();
        
        m_currentFigure->rotate(angle, rotateCenter);
    }
    
    // Масштабирование
    double factor = m_scaleFactorSpinBox->value();
    QPointF scaleCenter(m_scaleCenterXSpinBox->value(), m_scaleCenterYSpinBox->value());
    if (qAbs(factor - 1.0) > 0.001)
    {
        if (scaleCenter.isNull())
            scaleCenter = m_currentFigure->centerOfMass();
        
        m_currentFigure->scale(factor, scaleCenter);
    }
    
    updateFigureInfo();
    updateFigureList();
}

void MainWindow::animateTransformation()
{
    if (!m_currentFigure)
        return;
    
    // Анимированное перемещение
    QPointF moveOffset(m_moveXSpinBox->value(), m_moveYSpinBox->value());
    QPointF targetCenter = m_currentFigure->centerOfMass() + moveOffset;
    
    connect(m_currentFigure, &Figure::animationFinished, 
            this, &MainWindow::updateFigureInfo, Qt::UniqueConnection);
    connect(m_currentFigure, &Figure::animationProgress,
            this, &MainWindow::updateAnimationProgress, Qt::UniqueConnection);
    
    m_currentFigure->animateMove(targetCenter, 1000);
}

void MainWindow::updateAnimationProgress(double progress)
{
    Q_UNUSED(progress);
    updateCanvas();
}

void MainWindow::updateFigureProperties()
{
    if (!m_currentFigure)
        return;
}

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
    
    QMessageBox::information(this, "Info", "Save functionality not fully implemented");
}

void MainWindow::loadFigure()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Figure", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;
    
    QMessageBox::information(this, "Info", "Load functionality not fully implemented");
}

void MainWindow::updateCanvas()
{
    m_canvas->update();
}