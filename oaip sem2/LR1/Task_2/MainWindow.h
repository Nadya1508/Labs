#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QCheckBox>
#include <QColorDialog>
#include <QGroupBox>
#include <QProgressBar>
#include <QFormLayout>
#include "FigureCanvas.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Rhombus.h"
#include "Hexagon.h"
#include "Star.h"
#include "Circle.h"
#include "CustomFigure.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Управление фигурами
    void createFigure();
    void removeFigure();
    void updateFigureInfo();
    void updateSelectedFigure();
    void updateFigureList();  // Добавлена эта строка!
    
    // Преобразования
    void applyTransformation();
    void animateTransformation();
    void updateAnimationProgress(double progress);
    
    // Управление параметрами
    void chooseLineColor();
    void chooseFillColor();
    void updateLineWidth();
    void updateRadius();
    void updateWidth();
    void updateHeight();
    
    // Файловые операции
    void saveFigure();
    void loadFigure();
    
    // Обновление канваса
    void updateCanvas();
    
    // Управление центром
    void moveCenterToPoint();
    
    // Сброс вида
    void resetView();

private:
    void setupUI();
    Figure* createFigureByType(const QString &type);
    void updateParameterControls();
    
    // Основные элементы UI
    FigureCanvas *m_canvas;
    QListWidget *m_figureList;
    
    // Панель создания фигур
    QComboBox *m_figureTypeCombo;
    
    // Панель информации
    QLabel *m_areaLabel;
    QLabel *m_perimeterLabel;
    QLabel *m_centerLabel;
    
    // Панель преобразований
    QDoubleSpinBox *m_moveXSpinBox;
    QDoubleSpinBox *m_moveYSpinBox;
    
    QDoubleSpinBox *m_rotateAngleSpinBox;
    QDoubleSpinBox *m_rotateCenterXSpinBox;
    QDoubleSpinBox *m_rotateCenterYSpinBox;
    
    QDoubleSpinBox *m_scaleFactorSpinBox;
    QDoubleSpinBox *m_scaleCenterXSpinBox;
    QDoubleSpinBox *m_scaleCenterYSpinBox;
    
    // Панель параметров
    QPushButton *m_lineColorButton;
    QPushButton *m_fillColorButton;
    QSpinBox *m_lineWidthSpinBox;
    
    QDoubleSpinBox *m_radiusSpinBox;
    QDoubleSpinBox *m_widthSpinBox;
    QDoubleSpinBox *m_heightSpinBox;
    
    QDoubleSpinBox *m_newCenterXSpinBox;
    QDoubleSpinBox *m_newCenterYSpinBox;
    
    // Настройки канваса
    QCheckBox *m_gridCheckBox;
    QCheckBox *m_centersCheckBox;
    QCheckBox *m_triangulationCheckBox;
    
    // Анимация
    QTimer *m_updateTimer;
    QProgressBar *m_animationProgressBar;
    
    // Текущая фигура
    Figure *m_currentFigure;
    
    // Цвета
    QColor m_currentLineColor;
    QColor m_currentFillColor;
};

#endif // MAINWINDOW_H