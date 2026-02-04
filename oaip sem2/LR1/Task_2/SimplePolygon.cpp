#include "SimplePolygon.h"
#include <cmath>
#include <QDebug>

SimplePolygon::SimplePolygon(QObject *parent) 
    : PolygonFigure(parent)
    , m_sides(7)
{
    qDebug() << "SimplePolygon constructor";
    setPolygon(QPointF(100, 100), 50, 7);
}

SimplePolygon::SimplePolygon(const QPointF &center, double radius, int sides, QObject *parent)
    : PolygonFigure(parent)
    , m_sides(sides)
{
    qDebug() << "SimplePolygon constructor with params";
    setPolygon(center, radius, sides);
}

SimplePolygon::~SimplePolygon()
{
    qDebug() << "SimplePolygon destructor";
}

QString SimplePolygon::type() const 
{ 
    return "Многоугольник"; 
}

void SimplePolygon::setPolygon(const QPointF &center, double radius, int sides)
{
    m_sides = qMax(3, sides);
    
    QList<QPointF> vertices;
    for (int i = 0; i < m_sides; i++)
    {
        double angle = 2 * M_PI * i / m_sides;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        vertices.append(QPointF(x, y));
    }
    
    setVertices(vertices);
}

double SimplePolygon::radius() const
{
    if (getVertices().isEmpty())
        return 0.0;
    
    QPointF center = centerOfMass();
    QPointF firstVertex = getVertices().first();
    return sqrt(pow(firstVertex.x() - center.x(), 2) + pow(firstVertex.y() - center.y(), 2));
}

int SimplePolygon::sides() const
{
    return m_sides;
}

void SimplePolygon::setRadius(double radius)
{
    QPointF center = centerOfMass();
    setPolygon(center, radius, m_sides);
}

void SimplePolygon::setSides(int sides)
{
    QPointF center = centerOfMass();
    double currentRadius = radius();
    setPolygon(center, currentRadius, sides);
}