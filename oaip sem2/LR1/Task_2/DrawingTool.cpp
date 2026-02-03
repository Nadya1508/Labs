#include "DrawingTool.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"
#include "Rhombus.h"
#include "Hexagon.h"
#include "Star.h"
#include "CustomFigure.h"
#include <QLineF>
#include <cmath>

DrawingTool::DrawingTool(QObject *parent)
    : QObject(parent)
    , m_drawingMode(NoDrawing)
    , m_isDrawing(false)
    , m_currentColor(Qt::blue)
    , m_currentFillColor(Qt::lightGray)
    , m_currentLineWidth(2)
{
}

void DrawingTool::setDrawingMode(DrawingMode mode)
{
    if (m_isDrawing)
        cancelDrawing();
    
    m_drawingMode = mode;
}

void DrawingTool::startDrawing(const QPointF &startPoint)
{
    if (m_drawingMode == NoDrawing)
        return;
    
    m_isDrawing = true;
    m_startPoint = startPoint;
    m_drawingPoints.clear();
    m_drawingPoints.append(startPoint);
}

void DrawingTool::updateDrawing(const QPointF &currentPoint)
{
    if (!m_isDrawing || m_drawingMode == NoDrawing)
        return;
    
    if (m_drawingPoints.size() < 2)
    {
        m_drawingPoints.append(currentPoint);
    }
    else
    {
        m_drawingPoints.last() = currentPoint;
    }
}

Figure* DrawingTool::finishDrawing()
{
    if (!m_isDrawing || m_drawingMode == NoDrawing || m_drawingPoints.size() < 2)
    {
        cancelDrawing();
        return nullptr;
    }
    
    Figure *figure = createFigureFromPoints(m_drawingPoints);
    
    if (figure)
    {
        figure->setColor(m_currentColor);
        figure->setFillColor(m_currentFillColor);
        figure->setLineWidth(m_currentLineWidth);
        emit figureCreated(figure);
    }
    
    m_isDrawing = false;
    m_drawingPoints.clear();
    
    return figure;
}

void DrawingTool::cancelDrawing()
{
    m_isDrawing = false;
    m_drawingPoints.clear();
}

QPointF DrawingTool::calculateSquarePoint(const QPointF &start, const QPointF &current)
{
    double dx = current.x() - start.x();
    double dy = current.y() - start.y();
    double side = qMin(qAbs(dx), qAbs(dy));
    
    QPointF result = start;
    
    if (dx >= 0)
        result.rx() += side;
    else
        result.rx() -= side;
    
    if (dy >= 0)
        result.ry() += side;
    else
        result.ry() -= side;
    
    return result;
}

Figure* DrawingTool::createFigureFromPoints(const QList<QPointF> &points)
{
    if (points.size() < 2)
        return nullptr;
    
    QPointF start = points.first();
    QPointF end = points.last();
    
    switch (m_drawingMode)
    {
    case DrawTriangle:
    {
        QPointF p1 = start;
        QPointF p2 = QPointF(end.x(), start.y());
        QPointF p3 = QPointF(start.x() + (end.x() - start.x()) / 2, end.y());
        return new Triangle(p1, p2, p3, this);
    }
    
    case DrawRectangle:
    {
        double width = qAbs(end.x() - start.x());
        double height = qAbs(end.y() - start.y());
        QPointF topLeft(qMin(start.x(), end.x()), qMin(start.y(), end.y()));
        return new Rectangle(topLeft, width, height, this);
    }
    
    case DrawSquare:
    {
        QPointF squareEnd = calculateSquarePoint(start, end);
        double side = qAbs(squareEnd.x() - start.x());
        QPointF topLeft(qMin(start.x(), squareEnd.x()), qMin(start.y(), squareEnd.y()));
        return new Square(topLeft, side, this);
    }
    
    case DrawCircle:
    {
        QPointF center = (start + end) / 2;
        double radius = QLineF(center, start).length();
        return new Circle(center, radius, this);
    }
    
    case DrawRhombus:
    {
        QPointF center = (start + end) / 2;
        double diagonal1 = qAbs(end.x() - start.x());
        double diagonal2 = qAbs(end.y() - start.y());
        return new Rhombus(center, diagonal1, diagonal2, this);
    }
    
    case DrawHexagon:
    {
        QPointF center = (start + end) / 2;
        double radius = QLineF(center, start).length();
        return new Hexagon(center, radius, this);
    }
    
    case DrawStar:
    {
        QPointF center = (start + end) / 2;
        double outerRadius = QLineF(center, start).length();
        double innerRadius = outerRadius * 0.5;
        return new Star(center, outerRadius, innerRadius, Star::FivePointed, this);
    }
    
    case DrawPolygon:
    {
        // Для многоугольника нужно больше точек
        if (points.size() >= 3)
        {
            CustomFigure *polygon = new CustomFigure(this);
            polygon->setVertices(points);
            return polygon;
        }
        return nullptr;
    }
    
    case DrawCustomPolygon:
    {
        if (points.size() >= 3)
        {
            CustomFigure *polygon = new CustomFigure(this);
            polygon->setVertices(points);
            return polygon;
        }
        return nullptr;
    }
    
    default:
        return nullptr;
    }
}