#include "Circle.h"
#include <QPainter>
#include <cmath>

Circle::Circle(QObject *parent) 
    : Figure(parent)
    , m_center(50, 50)
    , m_radius(40)
{
}

Circle::Circle(const QPointF &center, double radius, QObject *parent)
    : Figure(parent)
    , m_center(center)
    , m_radius(radius)
{
}

double Circle::area() const
{
    return M_PI * m_radius * m_radius;
}

double Circle::perimeter() const
{
    return 2 * M_PI * m_radius;
}

QPointF Circle::centerOfMass() const
{
    return m_center;
}

QRectF Circle::boundingRect() const
{
    return QRectF(m_center.x() - m_radius, m_center.y() - m_radius,
                 2 * m_radius, 2 * m_radius);
}

void Circle::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(QPen(m_color, 2));
    painter->setBrush(QBrush(m_color.lighter(150)));
    painter->drawEllipse(m_center, m_radius, m_radius);
    
    // Рисуем центр масс
    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    painter->drawEllipse(m_center, 3, 3);
    
    painter->restore();
}

void Circle::setCircle(const QPointF &center, double radius)
{
    m_center = center;
    m_radius = radius;
    emit figureChanged();
}

double Circle::radius() const
{
    return m_radius;
}

void Circle::setRadius(double radius)
{
    m_radius = radius;
    emit figureChanged();
}

void Circle::transform(const QTransform &transform)
{
    m_center = transform.map(m_center);
    
    // Для масштабирования радиуса
    QPointF radiusPoint = m_center + QPointF(m_radius, 0);
    radiusPoint = transform.map(radiusPoint);
    m_radius = QLineF(m_center, radiusPoint).length();
}