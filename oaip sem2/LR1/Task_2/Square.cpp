#include "Square.h"

Square::Square(QObject *parent) 
    : Rectangle(parent)
{
    setSquare(QPointF(0, 0), 80);
}

Square::Square(const QPointF &topLeft, double side, QObject *parent)
    : Rectangle(parent)
{
    setSquare(topLeft, side);
}

QString Square::type() const 
{ 
    return "Square"; 
}

void Square::setSquare(const QPointF &topLeft, double side)
{
    setRectangle(topLeft, side, side);
}

double Square::side() const
{
    return width();
}

void Square::setSide(double side)
{
    QPointF topLeft = m_vertices[0];
    setSquare(topLeft, side);
}