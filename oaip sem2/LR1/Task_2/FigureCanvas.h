#ifndef FIGURECANVAS_H
#define FIGURECANVAS_H

#include <QWidget>
#include <QList>
#include <QPainter>
#include "Figure.h"

// Forward declaration
class PolygonFigure;

class FigureCanvas : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double scale READ scale WRITE setScale)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset)

public:
    explicit FigureCanvas(QWidget *parent = nullptr);
    
    void addFigure(Figure *figure);
    void removeFigure(Figure *figure);
    void clearFigures();
    
    QList<Figure*> getFigures() const;
    
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
    
    void resetView();
    
    Figure* selectedFigure() const { return m_selectedFigure; }
    void setSelectedFigure(Figure *figure);
    
    // Public methods for zoom control
    void zoomIn();
    void zoomOut();
    void zoom(double factor, const QPointF &center = QPointF());
    void pan(const QPointF &delta);
    
    double scale() const { return m_scale; }
    void setScale(double scale);
    QPointF offset() const { return m_offset; }
    void setOffset(const QPointF &offset);

signals:
    void figureSelected(Figure *figure);
    void figureDoubleClicked(Figure *figure);
    void viewChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawGrid(QPainter &painter);
    void drawTriangulation(QPainter &painter, Figure *figure);
    void drawSelection(QPainter &painter, Figure *figure);
    void updateViewport();
    
private:
    QList<Figure*> m_figures;
    bool m_gridEnabled;
    bool m_showCenters;
    bool m_showTriangulation;
    bool m_showVertices;
    bool m_showBoundingBox;
    
    // For dragging figures
    Figure *m_selectedFigure;
    QPointF m_lastMousePos;
    bool m_isDragging;
    
    // For panning
    bool m_isPanning;
    QPointF m_panStartPos;
    
    // For wheel zoom
    double m_scale;
    QPointF m_offset;
    
    // Viewport
    QRectF m_viewport;
};

#endif // FIGURECANVAS_H