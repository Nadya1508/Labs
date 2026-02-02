#include "Rectangle.h"

Rectangle::Rectangle(QObject *parent) 
    : Quadrilateral(parent)
{
    setRectangle(QPointF(0, 0), 100, 80);
}

Rectangle::Rectangle(const QPointF &topLeft, double width, double height, QObject *parent)
    : Quadrilateral(parent)
{
    setRectangle(topLeft, width, height);
}

QString Rectangle::type() const 
{ 
    return "Rectangle"; 
}

void Rectangle::setRectangle(const QPointF &topLeft, double width, double height)
{
    QPointF p1 = topLeft;
    QPointF p2 = topLeft + QPointF(width, 0);
    QPointF p3 = topLeft + QPointF(width, height);
    QPointF p4 = topLeft + QPointF(0, height);
    
    setPoints(p1, p2, p3, p4);
}

double Rectangle::width() const
{
    if (m_vertices.size() < 2)
        return 0.0;
    
    return QLineF(m_vertices[0], m_vertices[1]).length();
}

double Rectangle::height() const
{
    if (m_vertices.size() < 3)
        return 0.0;
    
    return QLineF(m_vertices[1], m_vertices[2]).length();
}

void Rectangle::setWidth(double width)
{
    double currentHeight = height();
    QPointF topLeft = m_vertices[0];
    setRectangle(topLeft, width, currentHeight);
}

void Rectangle::setHeight(double height)
{
    double currentWidth = width();
    QPointF topLeft = m_vertices[0];
    setRectangle(topLeft, currentWidth, height);
}