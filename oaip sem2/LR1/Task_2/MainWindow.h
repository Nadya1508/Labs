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
#include "FigureCanvas.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Rhombus.h"
#include "Hexagon.h"
#include "Star.h"
#include "Circle.h"
#include "CustomFigure.h"

// УДАЛИТЬ эту строку:
// namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createFigure();
    void removeFigure();
    void updateFigureInfo();
    void updateSelectedFigure();
    void applyTransformation();
    void animateTransformation();
    void updateAnimationProgress(double progress);
    void updateFigureProperties();
    void saveFigure();
    void loadFigure();
    void updateCanvas();

private:
    void setupUI();
    void createFigureControls();
    void updateFigureList();
    Figure* createFigureByType(const QString &type);
    void updatePropertiesPanel(Figure *figure);

private:
    // УДАЛИТЬ эту строку:
    // Ui::MainWindow *ui;
    
    FigureCanvas *m_canvas;
    QListWidget *m_figureList;
    QComboBox *m_figureTypeCombo;
    QSpinBox *m_sidesSpinBox;
    QDoubleSpinBox *m_radiusSpinBox;
    QDoubleSpinBox *m_outerRadiusSpinBox;
    QDoubleSpinBox *m_innerRadiusSpinBox;
    QDoubleSpinBox *m_widthSpinBox;
    QDoubleSpinBox *m_heightSpinBox;
    QDoubleSpinBox *m_diagonal1SpinBox;
    QDoubleSpinBox *m_diagonal2SpinBox;
    QComboBox *m_starTypeCombo;
    QLabel *m_areaLabel;
    QLabel *m_perimeterLabel;
    QLabel *m_centerLabel;
    
    QDoubleSpinBox *m_moveXSpinBox;
    QDoubleSpinBox *m_moveYSpinBox;
    QDoubleSpinBox *m_rotateAngleSpinBox;
    QDoubleSpinBox *m_rotateCenterXSpinBox;
    QDoubleSpinBox *m_rotateCenterYSpinBox;
    QDoubleSpinBox *m_scaleFactorSpinBox;
    QDoubleSpinBox *m_scaleCenterXSpinBox;
    QDoubleSpinBox *m_scaleCenterYSpinBox;
    
    QTimer *m_updateTimer;
    
    Figure *m_currentFigure;
};

#endif // MAINWINDOW_H