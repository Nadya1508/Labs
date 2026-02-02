#ifndef FIGURECANVAS_H
#define FIGURECANVAS_H

#include <QWidget>
#include <QVector>
#include "Figure.h"

class FigureCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit FigureCanvas(QWidget *parent = nullptr);
    
    void addFigure(Figure *figure);
    void removeFigure(Figure *figure);
    void clearFigures();
    
    QVector<Figure*> getFigures() const;
    
    void setGridEnabled(bool enabled);
    bool isGridEnabled() const;
    
    void setShowCenters(bool show);
    bool isShowCenters() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void drawGrid(QPainter &painter);
    
private:
    QVector<Figure*> m_figures;
    bool m_gridEnabled;
    bool m_showCenters;
    
    // Для перемещения фигур
    Figure *m_selectedFigure;
    QPointF m_lastMousePos;
    bool m_isDragging;
};

#endif // FIGURECANVAS_H