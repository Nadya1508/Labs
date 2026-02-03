#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent> 
#include <QDockWidget>
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
#include <QScrollArea>
#include <QTabWidget>
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
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
    // File operations
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void exportImage();
    
    // Edit operations
    void copyFigure();
    void pasteFigure();
    void deleteFigure();
    
    // Figure management
    void createFigure();
    void createFigureFromType(const QString &type);
    void removeSelectedFigure();
    void clearAllFigures();
    void updateFigureInfo();
    void updateSelectedFigure();
    void updateFigureList();
    
    // Transformations
    void applyTransformation();
    void animateTransformation();
    void stopAnimation();
    void updateAnimationProgress(double progress);
    
    // Parameter management
    void chooseLineColor();
    void chooseFillColor();
    void updateLineWidth();
    void updateSpecificParameter();
    
    // Center management
    void moveCenterToPoint();
    void showCenterInfo();
    
    // Canvas settings
    void toggleGrid(bool enabled);
    void toggleCenters(bool enabled);
    void toggleTriangulation(bool enabled);
    void toggleVertices(bool enabled);
    void toggleBoundingBox(bool enabled);
    
    // View operations
    void zoomIn();
    void zoomOut();
    void resetView();
    void fitToView();
    
    // Help
    void about();
    void showHelp();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupDockWidgets();
    
    Figure* createFigureByType(const QString &type, const QPointF &center = QPointF(300, 300));
    void updateParameterControls();
    void updateTransformationControls();
    void showFigureProperties(Figure *figure);
    
    // UI Elements
    FigureCanvas *m_canvas;
    
    // Menu bar
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_viewMenu;
    QMenu *m_figureMenu;
    QMenu *m_helpMenu;
    
    // Toolbar
    QToolBar *m_mainToolBar;
    
    // Dock widgets
    QDockWidget *m_figuresDock;
    QDockWidget *m_propertiesDock;
    QDockWidget *m_transformationsDock;
    QDockWidget *m_infoDock;
    
    // Figure list
    QListWidget *m_figureList;
    
    // Figure creation
    QComboBox *m_figureTypeCombo;
    
    // Figure info
    QLabel *m_areaLabel;
    QLabel *m_perimeterLabel;
    QLabel *m_centerLabel;
    QLabel *m_verticesLabel;
    QLabel *m_trianglesLabel;
    
    // Transformations
    QDoubleSpinBox *m_moveXSpinBox;
    QDoubleSpinBox *m_moveYSpinBox;
    
    QDoubleSpinBox *m_rotateAngleSpinBox;
    QDoubleSpinBox *m_rotateCenterXSpinBox;
    QDoubleSpinBox *m_rotateCenterYSpinBox;
    
    QDoubleSpinBox *m_scaleFactorSpinBox;
    QDoubleSpinBox *m_scaleCenterXSpinBox;
    QDoubleSpinBox *m_scaleCenterYSpinBox;
    
    // Parameters
    QPushButton *m_lineColorButton;
    QPushButton *m_fillColorButton;
    QSpinBox *m_lineWidthSpinBox;
    
    // Specific parameters
    QTabWidget *m_paramTabs;
    QWidget *m_circleParams;
    QWidget *m_rectangleParams;
    QWidget *m_squareParams;
    QWidget *m_rhombusParams;
    QWidget *m_polygonParams;
    QWidget *m_starParams;
    
    QDoubleSpinBox *m_radiusSpinBox;
    QDoubleSpinBox *m_widthSpinBox;
    QDoubleSpinBox *m_heightSpinBox;
    QDoubleSpinBox *m_sideSpinBox;
    QDoubleSpinBox *m_diag1SpinBox;
    QDoubleSpinBox *m_diag2SpinBox;
    QSpinBox *m_sidesSpinBox;
    QComboBox *m_starTypeCombo;
    QDoubleSpinBox *m_outerRadiusSpinBox;
    QDoubleSpinBox *m_innerRadiusSpinBox;
    
    QDoubleSpinBox *m_newCenterXSpinBox;
    QDoubleSpinBox *m_newCenterYSpinBox;
    
    // Animation
    QProgressBar *m_animationProgressBar;
    QPushButton *m_stopAnimationButton;
    
    // Current figure
    Figure *m_currentFigure;
    
    // Colors
    QColor m_currentLineColor;
    QColor m_currentFillColor;
    
    // Status bar
    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H