#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
#include <QActionGroup>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QSplitter>
#include <QRadioButton>
#include <QButtonGroup>
#include <QShortcut>
#include "FigureCanvas.h"

// Добавим forward declarations для всех фигур
class Triangle;
class Rectangle;
class Square;
class Rhombus;
class Hexagon;
class Star;
class Circle;
class CustomFigure;
class PolygonFigure;

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
    void exitApplication();
    
    // Edit operations
    void copyFigure();
    void pasteFigure();
    void deleteFigure();
    void selectAll();
    void deselectAll();
    
    // Figure management
    void createFigure();
    void createFigureFromType(const QString &type);
    void removeSelectedFigure();
    void clearAllFigures();
    void updateFigureInfo();
    void updateSelectedFigure();
    void updateFigureList();
    
    // Drawing modes
    void setDrawTriangleMode();
    void setDrawRectangleMode();
    void setDrawSquareMode();
    void setDrawCircleMode();
    void setDrawRhombusMode();
    void setDrawHexagonMode();
    void setDrawStarMode();
    void setDrawPolygonMode();
    void stopDrawingMode();
    
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
    void updateVertex();  // Добавлен этот слот!
    
    // Center management
    void moveCenterToPoint();
    void showCenterInfo();
    
    // Canvas settings
    void toggleGrid(bool enabled);
    void toggleCenters(bool enabled);
    void toggleTriangulation(bool enabled);
    void toggleVertices(bool enabled);
    void toggleBoundingBox(bool enabled);
    void toggleSnapToGrid(bool enabled);
    
    // View operations
    void zoomIn();
    void zoomOut();
    void resetView();
    void fitToView();
    void showFullScreen();
    
    // Calculations
    void calculateTotalArea();
    void calculateTotalPerimeter();
    
    // Help
    void about();
    void showHelp();
    void showShortcuts();

    // Drawing button handler - добавлен этот слот!
    void handleDrawingButtonClicked(QAbstractButton *button);

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupDockWidgets();
    void createConnections();
    
    Figure* createFigureByType(const QString &type, const QPointF &center = QPointF(300, 300));
    void updateParameterControls();
    void updateTransformationControls();
    void updateDrawingControls();
    void uncheckDrawingActions();
    void showFigureStatistics();
    
    // UI Elements
    FigureCanvas *m_canvas;
    
    // Menu bar
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_viewMenu;
    QMenu *m_figureMenu;
    QMenu *m_drawingMenu;
    QMenu *m_transformMenu;
    QMenu *m_helpMenu;
    
    // Toolbar
    QToolBar *m_mainToolBar;
    QToolBar *m_drawingToolBar;
    
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
    QLabel *m_figureTypeLabel;
    
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
    QWidget *m_triangleParams;
    QWidget *m_hexagonParams;
    
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
    QDoubleSpinBox *m_triangleBaseSpinBox;
    QDoubleSpinBox *m_triangleHeightSpinBox;
    
    // Vertex control
    QGroupBox *m_vertexGroup;
    QSpinBox *m_vertexIndexSpinBox;
    QDoubleSpinBox *m_vertexXSpinBox;
    QDoubleSpinBox *m_vertexYSpinBox;
    
    // Center control
    QDoubleSpinBox *m_newCenterXSpinBox;
    QDoubleSpinBox *m_newCenterYSpinBox;
    
    // Animation
    QProgressBar *m_animationProgressBar;
    QPushButton *m_stopAnimationButton;
    
    // Drawing controls
    QGroupBox *m_drawingControlsGroup;
    QButtonGroup *m_drawingButtonGroup;
    QRadioButton *m_drawTriangleRadio;
    QRadioButton *m_drawRectangleRadio;
    QRadioButton *m_drawSquareRadio;
    QRadioButton *m_drawCircleRadio;
    QRadioButton *m_drawRhombusRadio;
    QRadioButton *m_drawHexagonRadio;
    QRadioButton *m_drawStarRadio;
    QRadioButton *m_drawPolygonRadio;
    QRadioButton *m_noDrawingRadio;
    
    // Current figure
    Figure *m_currentFigure;
    
    // Colors
    QColor m_currentLineColor;
    QColor m_currentFillColor;
    
    // Status bar
    QLabel *m_statusLabel;
    QLabel *m_mousePositionLabel;
    QLabel *m_drawingModeLabel;
    
    // Actions
    QAction *m_drawTriangleAction;
    QAction *m_drawRectangleAction;
    QAction *m_drawSquareAction;
    QAction *m_drawCircleAction;
    QAction *m_drawRhombusAction;
    QAction *m_drawHexagonAction;
    QAction *m_drawStarAction;
    QAction *m_drawPolygonAction;
    QAction *m_stopDrawingAction;
    
    // Timer for updates
    QTimer *m_updateTimer;
};

#endif // MAINWINDOW_H