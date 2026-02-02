#include "CustomFigure.h"
#include <cmath>

CustomFigure::CustomFigure(QObject *parent) 
    : PolygonFigure(parent)
    , m_sides(7)
{
    setPolygon(QPointF(50, 50), 45, 7);
}

CustomFigure::CustomFigure(const QPointF &center, double radius, int sides, QObject *parent)
    : PolygonFigure(parent)
    , m_sides(sides)
{
    setPolygon(center, radius, sides);
}

void CustomFigure::setPolygon(const QPointF &center, double radius, int sides)
{
    m_sides = qMax(3, sides);
    m_vertices.clear();
    
    for (int i = 0; i < m_sides; i++)
    {
        double angle = 2 * M_PI * i / m_sides;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        m_vertices.append(QPointF(x, y));
    }
    
    emit figureChanged();
}

double CustomFigure::radius() const
{
    if (m_vertices.isEmpty())
        return 0.0;
    
    QPointF center = centerOfMass();
    return QLineF(center, m_vertices[0]).length();
}

int CustomFigure::sides() const
{
    return m_sides;
}

void CustomFigure::setRadius(double radius)
{
    QPointF center = centerOfMass();
    setPolygon(center, radius, m_sides);
}

void CustomFigure::setSides(int sides)
{
    QPointF center = centerOfMass();
    double currentRadius = radius();
    setPolygon(center, currentRadius, sides);
}