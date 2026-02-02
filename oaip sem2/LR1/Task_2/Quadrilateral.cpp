#include "Quadrilateral.h"

Quadrilateral::Quadrilateral(QObject *parent) 
    : PolygonFigure(parent)
{
    setPoints(QPointF(0, 0), QPointF(100, 0), QPointF(100, 100), QPointF(0, 100));
}

QString Quadrilateral::type() const 
{ 
    return "Quadrilateral"; 
}

void Quadrilateral::setPoints(const QPointF &p1, const QPointF &p2, 
                             const QPointF &p3, const QPointF &p4)
{
    m_vertices = {p1, p2, p3, p4};
    emit figureChanged();
}

QVector<QPointF> Quadrilateral::getPoints() const
{
    return m_vertices;
}