#include "Star.h"
#include <cmath>

Star::Star(QObject *parent) 
    : PolygonFigure(parent)
    , m_type(FivePointed)
{
    setStar(QPointF(50, 50), 50, 25, FivePointed);
}

Star::Star(const QPointF &center, double outerRadius, double innerRadius, StarType type, QObject *parent)
    : PolygonFigure(parent)
    , m_type(type)
{
    setStar(center, outerRadius, innerRadius, type);
}

void Star::setStar(const QPointF &center, double outerRadius, double innerRadius, StarType type)
{
    m_type = type;
    m_vertices.clear();
    
    int points = static_cast<int>(type);
    
    for (int i = 0; i < points * 2; i++)
    {
        double radius = (i % 2 == 0) ? outerRadius : innerRadius;
        double angle = 2 * M_PI * i / (points * 2);
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        m_vertices.append(QPointF(x, y));
    }
    
    emit figureChanged();
}

double Star::outerRadius() const
{
    if (m_vertices.isEmpty())
        return 0.0;
    
    QPointF center = centerOfMass();
    return QLineF(center, m_vertices[0]).length();
}

double Star::innerRadius() const
{
    if (m_vertices.size() < 2)
        return 0.0;
    
    QPointF center = centerOfMass();
    return QLineF(center, m_vertices[1]).length();
}

Star::StarType Star::starType() const
{
    return m_type;
}

void Star::setOuterRadius(double radius)
{
    QPointF center = centerOfMass();
    double currentInner = innerRadius();
    setStar(center, radius, currentInner, m_type);
}

void Star::setInnerRadius(double radius)
{
    QPointF center = centerOfMass();
    double currentOuter = outerRadius();
    setStar(center, currentOuter, radius, m_type);
}

void Star::setStarType(StarType type)
{
    QPointF center = centerOfMass();
    double currentOuter = outerRadius();
    double currentInner = innerRadius();
    setStar(center, currentOuter, currentInner, type);
}