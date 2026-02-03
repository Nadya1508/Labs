#ifndef FIGURECANVAS_H
#define FIGURECANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QList>
#include "Figure.h"
#include "DrawingTool.h"

class FigureCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit FigureCanvas(QWidget *parent = nullptr);
    ~FigureCanvas();

    // Drawing mode
    void setDrawingMode(DrawingTool::DrawingMode mode);
    DrawingTool::DrawingMode drawingMode() const;
    
    // View controls
    void zoomIn();
    void zoomOut();
    void zoom(double factor, const QPointF &center = QPointF());
    void pan(const QPointF &delta);
    void resetView();
    void fitToView();

    // Figure management
    void addFigure(Figure *figure);
    void removeFigure(Figure *figure);
    void clearFigures();
    QList<Figure*> getFigures() const;

    // Selection
    void setSelectedFigure(Figure *figure);
    Figure* selectedFigure() const;

    // Canvas settings
    void setGridEnabled(bool enabled);
    bool isGridEnabled() const;
    void setShowCenters(bool show);
    bool isShowCenters() const;
    void setShowTriangulation(bool show);
    bool isShowTriangulation() const;
    void setShowVertices(bool show);
    bool isShowVertices() const;
    void setShowBoundingBox(bool show);
    bool isShowBoundingBox() const;

    // Drawing properties
    void setDrawingColor(const QColor &color);
    void setDrawingFillColor(const QColor &color);
    void setDrawingLineWidth(int width);

    // View parameters
    double scale() const;
    QPointF offset() const;
    void setScale(double scale);
    void setOffset(const QPointF &offset);

signals:
    void viewChanged();
    void figureSelected(Figure *figure);
    void figureDoubleClicked(Figure *figure);
    void figureCreated(Figure *figure);
    void mouseMoved(const QPointF &scenePos);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateViewport();
    void drawGrid(QPainter &painter);
    void drawTriangulation(QPainter &painter, Figure *figure);
    void drawSelection(QPainter &painter, Figure *figure);
    void drawCurrentDrawing(QPainter &painter);

    QList<Figure*> m_figures;
    Figure *m_selectedFigure;
    DrawingTool *m_drawingTool;
    QList<QPointF> m_currentDrawingPoints;

    // View parameters
    double m_scale;
    QPointF m_offset;
    QRectF m_viewport;

    // Canvas settings
    bool m_gridEnabled;
    bool m_showCenters;
    bool m_showTriangulation;
    bool m_showVertices;
    bool m_showBoundingBox;

    // Interaction state
    bool m_isDragging;
    bool m_isPanning;
    QPointF m_lastMousePos;
    QPointF m_panStartPos;
};

#endif // FIGURECANVAS_H