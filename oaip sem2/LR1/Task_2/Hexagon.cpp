#include "Hexagon.h"
#include <cmath>

Hexagon::Hexagon(QObject *parent) 
    : PolygonFigure(parent)
{
    setHexagon(QPointF(50, 50), 50);
}

Hexagon::Hexagon(const QPointF &center, double radius, QObject *parent)
    : PolygonFigure(parent)
{
    setHexagon(center, radius);
}

void Hexagon::setHexagon(const QPointF &center, double radius)
{
    m_vertices.clear();
    
    for (int i = 0; i < 6; i++)
    {
        double angle = 2 * M_PI * i / 6;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        m_vertices.append(QPointF(x, y));
    }
    
    emit figureChanged();
}

double Hexagon::radius() const
{
    if (m_vertices.isEmpty())
        return 0.0;
    
    QPointF center = centerOfMass();
    return QLineF(center, m_vertices[0]).length();
}

void Hexagon::setRadius(double radius)
{
    QPointF center = centerOfMass();
    setHexagon(center, radius);
}