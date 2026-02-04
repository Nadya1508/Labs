#include "Ellipse.h"
#include <QPainter>
#include <QTransform>
#include <cmath>

Ellipse::Ellipse(QObject *parent) 
    : Figure(parent)
    , m_center(50, 50)
    , m_radiusX(60)
    , m_radiusY(40)
{
}

Ellipse::Ellipse(const QPointF &center, double radiusX, double radiusY, QObject *parent)
    : Figure(parent)
    , m_center(center)
    , m_radiusX(radiusX)
    , m_radiusY(radiusY)
{
}

QString Ellipse::type() const 
{ 
    return "Ellipse"; 
}

double Ellipse::area() const
{
    return M_PI * m_radiusX * m_radiusY;
}

double Ellipse::perimeter() const
{
    // Приближенная формула периметра эллипса (формула Рамануджана)
    double h = pow((m_radiusX - m_radiusY) / (m_radiusX + m_radiusY), 2);
    return M_PI * (m_radiusX + m_radiusY) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
}

QPointF Ellipse::centerOfMass() const
{
    return m_center;
}

QRectF Ellipse::boundingRect() const
{
    return QRectF(m_center.x() - m_radiusX, m_center.y() - m_radiusY,
                 2 * m_radiusX, 2 * m_radiusY);
}

void Ellipse::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(QPen(m_color, m_lineWidth));
    painter->setBrush(QBrush(m_fillColor));
    painter->drawEllipse(m_center, m_radiusX, m_radiusY);
    painter->restore();
}

void Ellipse::setEllipse(const QPointF &center, double radiusX, double radiusY)
{
    m_center = center;
    m_radiusX = radiusX;
    m_radiusY = radiusY;
    emit figureChanged();
}

double Ellipse::radiusX() const
{
    return m_radiusX;
}

double Ellipse::radiusY() const
{
    return m_radiusY;
}

void Ellipse::setRadiusX(double radius)
{
    m_radiusX = radius;
    emit figureChanged();
}

void Ellipse::setRadiusY(double radius)
{
    m_radiusY = radius;
    emit figureChanged();
}

void Ellipse::transform(const QTransform &transform)
{
    m_center = transform.map(m_center);
    
    // Для масштабирования радиусов
    if (m_radiusX > 0 && m_radiusY > 0) {
        QPointF radiusXPoint = m_center + QPointF(m_radiusX, 0);
        QPointF radiusYPoint = m_center + QPointF(0, m_radiusY);
        
        radiusXPoint = transform.map(radiusXPoint);
        radiusYPoint = transform.map(radiusYPoint);
        
        m_radiusX = QLineF(m_center, radiusXPoint).length();
        m_radiusY = QLineF(m_center, radiusYPoint).length();
    }
    emit figureChanged();
}