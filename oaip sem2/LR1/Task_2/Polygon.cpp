#include "Polygon.h"
#include <cmath>

Polygon::Polygon(QObject *parent) 
    : PolygonFigure(parent)
    , m_sides(6)
{
    setRegularPolygon(QPointF(100, 100), 50, 6);
}

Polygon::Polygon(const QPointF &center, double radius, int sides, QObject *parent)
    : PolygonFigure(parent)
    , m_sides(sides)
{
    setRegularPolygon(center, radius, sides);
}

QString Polygon::type() const 
{ 
    return "Polygon"; 
}

double Polygon::radius() const
{
    if (m_vertices.isEmpty()) return 0.0;
    QPointF c = centerOfMass();
    return QLineF(c, m_vertices.first()).length();
}

int Polygon::sides() const
{
    return m_sides;
}

void Polygon::setSides(int sides)
{
    if (sides < 3) return;
    m_sides = sides;
    QPointF c = centerOfMass();
    double r = radius();
    setRegularPolygon(c, r, sides);
}

void Polygon::setRadius(double radius)
{
    QPointF c = centerOfMass();
    setRegularPolygon(c, radius, m_sides);
}

void Polygon::setRegularPolygon(const QPointF &center, double radius, int sides)
{
    m_sides = qMax(3, sides);
    m_vertices.clear();
    
    for (int i = 0; i < m_sides; i++)
    {
        double angle = 2 * M_PI * i / m_sides;
        double x = center.x() + radius * std::cos(angle);
        double y = center.y() + radius * std::sin(angle);
        m_vertices.append(QPointF(x, y));
    }
    
    emit figureChanged(); // Используем правильный сигнал
}