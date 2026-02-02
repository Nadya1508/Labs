#include "Triangle.h"

Triangle::Triangle(QObject *parent) 
    : PolygonFigure(parent)
{
    setPoints(QPointF(0, 0), QPointF(50, 100), QPointF(100, 0));
}

Triangle::Triangle(const QPointF &p1, const QPointF &p2, const QPointF &p3, QObject *parent)
    : PolygonFigure(parent)
{
    setPoints(p1, p2, p3);
}

QString Triangle::type() const 
{ 
    return "Triangle"; 
}

void Triangle::setPoints(const QPointF &p1, const QPointF &p2, const QPointF &p3)
{
    m_vertices = {p1, p2, p3};
    emit figureChanged();
}

QVector<QPointF> Triangle::getPoints() const
{
    return m_vertices;
}