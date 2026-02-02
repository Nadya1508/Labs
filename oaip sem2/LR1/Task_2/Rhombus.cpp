#include "Rhombus.h"
#include <cmath>

Rhombus::Rhombus(QObject *parent) 
    : Quadrilateral(parent)
{
    setRhombus(QPointF(50, 50), 80, 60);
}

Rhombus::Rhombus(const QPointF &center, double diagonal1, double diagonal2, QObject *parent)
    : Quadrilateral(parent)
{
    setRhombus(center, diagonal1, diagonal2);
}

QString Rhombus::type() const 
{ 
    return "Rhombus"; 
}

void Rhombus::setRhombus(const QPointF &center, double diagonal1, double diagonal2)
{
    QPointF p1 = center + QPointF(0, -diagonal2 / 2);
    QPointF p2 = center + QPointF(diagonal1 / 2, 0);
    QPointF p3 = center + QPointF(0, diagonal2 / 2);
    QPointF p4 = center + QPointF(-diagonal1 / 2, 0);
    
    setPoints(p1, p2, p3, p4);
}

double Rhombus::diagonal1() const
{
    if (m_vertices.size() < 2)
        return 0.0;
    
    return QLineF(m_vertices[1], m_vertices[3]).length();
}

double Rhombus::diagonal2() const
{
    if (m_vertices.size() < 3)
        return 0.0;
    
    return QLineF(m_vertices[0], m_vertices[2]).length();
}

void Rhombus::setDiagonal1(double d1)
{
    QPointF center = centerOfMass();
    double currentD2 = diagonal2();
    setRhombus(center, d1, currentD2);
}

void Rhombus::setDiagonal2(double d2)
{
    QPointF center = centerOfMass();
    double currentD1 = diagonal1();
    setRhombus(center, currentD1, d2);
}