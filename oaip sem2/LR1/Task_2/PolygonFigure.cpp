#include "PolygonFigure.h"
#include <QPainterPath>

PolygonFigure::PolygonFigure(QObject *parent) 
    : Figure(parent)
{
}

double PolygonFigure::area() const
{
    if (m_vertices.size() < 3)
        return 0.0;
    
    double area = 0.0;
    int n = m_vertices.size();
    
    for (int i = 0; i < n; i++)
    {
        const QPointF &p1 = m_vertices[i];
        const QPointF &p2 = m_vertices[(i + 1) % n];
        area += p1.x() * p2.y() - p2.x() * p1.y();
    }
    
    return qAbs(area) / 2.0;
}

double PolygonFigure::perimeter() const
{
    if (m_vertices.size() < 2)
        return 0.0;
    
    double perimeter = 0.0;
    int n = m_vertices.size();
    
    for (int i = 0; i < n; i++)
    {
        const QPointF &p1 = m_vertices[i];
        const QPointF &p2 = m_vertices[(i + 1) % n];
        perimeter += QLineF(p1, p2).length();
    }
    
    return perimeter;
}

QPointF PolygonFigure::centerOfMass() const
{
    if (m_vertices.isEmpty())
        return QPointF();
    
    double area = 0.0;
    double cx = 0.0;
    double cy = 0.0;
    int n = m_vertices.size();
    
    for (int i = 0; i < n; i++)
    {
        const QPointF &p1 = m_vertices[i];
        const QPointF &p2 = m_vertices[(i + 1) % n];
        
        double cross = p1.x() * p2.y() - p2.x() * p1.y();
        area += cross;
        cx += (p1.x() + p2.x()) * cross;
        cy += (p1.y() + p2.y()) * cross;
    }
    
    area /= 2.0;
    double factor = 1.0 / (6.0 * area);
    
    cx *= factor;
    cy *= factor;
    
    return QPointF(cx, cy);
}

QRectF PolygonFigure::boundingRect() const
{
    if (m_vertices.isEmpty())
        return QRectF();
    
    QRectF rect(m_vertices.first(), m_vertices.first());
    
    for (const QPointF &point : m_vertices)
    {
        rect.setLeft(qMin(rect.left(), point.x()));
        rect.setRight(qMax(rect.right(), point.x()));
        rect.setTop(qMin(rect.top(), point.y()));
        rect.setBottom(qMax(rect.bottom(), point.y()));
    }
    
    return rect;
}

void PolygonFigure::draw(QPainter *painter) const
{
    if (m_vertices.size() < 2)
        return;
    
    painter->save();
    painter->setPen(QPen(m_color, 2));
    painter->setBrush(QBrush(m_color.lighter(150)));
    
    QPainterPath path;
    path.moveTo(m_vertices.first());
    
    for (int i = 1; i < m_vertices.size(); i++)
    {
        path.lineTo(m_vertices[i]);
    }
    
    path.closeSubpath();
    painter->drawPath(path);
    
    // Рисуем центр масс
    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    QPointF center = centerOfMass();
    painter->drawEllipse(center, 3, 3);
    
    painter->restore();
}

void PolygonFigure::setVertices(const QVector<QPointF> &vertices)
{
    m_vertices = vertices;
    emit figureChanged();
}

QVector<QPointF> PolygonFigure::getVertices() const
{
    return m_vertices;
}

QVector<QVector<QPointF>> PolygonFigure::triangulate() const
{
    QVector<QVector<QPointF>> triangles;
    
    if (m_vertices.size() < 3)
        return triangles;
    
    // Простая триангуляция для выпуклых многоугольников
    for (int i = 1; i < m_vertices.size() - 1; i++)
    {
        triangles.append({m_vertices[0], m_vertices[i], m_vertices[i + 1]});
    }
    
    return triangles;
}

void PolygonFigure::transform(const QTransform &transform)
{
    for (QPointF &vertex : m_vertices)
    {
        vertex = transform.map(vertex);
    }
}