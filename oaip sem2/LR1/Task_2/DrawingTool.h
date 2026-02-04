#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QObject>
#include <QPointF>
#include <QList>
#include "Figure.h"

class DrawingTool : public QObject
{
    Q_OBJECT

public:
    enum DrawingMode {
        NoDrawing,
        DrawTriangle,
        DrawRectangle,
        DrawSquare,
        DrawCircle,
        DrawPolygon,
        DrawStar,
        DrawRhombus,
        DrawHexagon
    };

    explicit DrawingTool(QObject *parent = nullptr);
    
    void setDrawingMode(DrawingMode mode);
    DrawingMode drawingMode() const { return m_drawingMode; }
    
    void startDrawing(const QPointF &startPoint);
    void updateDrawing(const QPointF &currentPoint);
    void addPointToPolygon(const QPointF &point); // Новая функция
    Figure* finishDrawing();
    void cancelDrawing();
    
    bool isDrawing() const { return m_isDrawing; }
    
    void setCurrentColor(const QColor &color) { m_currentColor = color; }
    void setCurrentFillColor(const QColor &color) { m_currentFillColor = color; }
    void setCurrentLineWidth(int width) { m_currentLineWidth = width; }

signals:
    void figureCreated(Figure *figure);

private:
    Figure* createFigureFromPoints(const QList<QPointF> &points);
    QPointF calculateSquarePoint(const QPointF &start, const QPointF &current);
    
private:
    DrawingMode m_drawingMode;
    bool m_isDrawing;
    QList<QPointF> m_drawingPoints;
    QPointF m_startPoint;
    
    QColor m_currentColor;
    QColor m_currentFillColor;
    int m_currentLineWidth;
};

#endif // DRAWINGTOOL_H