#include "PolygonFigure.h"
#include <QPainterPath>
#include <QPainter>

PolygonFigure::PolygonFigure(QObject *parent) 
    : Figure(parent)
{
}

double PolygonFigure::triangleArea(const QPointF &a, const QPointF &b, const QPointF &c) const
{
    return qAbs((a.x()*(b.y()-c.y()) + b.x()*(c.y()-a.y()) + c.x()*(a.y()-b.y())) / 2.0);
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
    
    if (m_vertices.size() == 1)
        return m_vertices[0];
    
    if (m_vertices.size() == 2)
        return (m_vertices[0] + m_vertices[1]) / 2;
    
    // Используем формулу для центра масс многоугольника через триангуляцию
    double totalArea = 0.0;
    double cx = 0.0;
    double cy = 0.0;
    
    QList<QList<QPointF>> triangles = triangulate();
    
    for (const auto &triangle : triangles)
    {
        if (triangle.size() == 3)
        {
            double triangleArea = this->triangleArea(triangle[0], triangle[1], triangle[2]);
            QPointF triangleCenter = (triangle[0] + triangle[1] + triangle[2]) / 3;
            
            totalArea += triangleArea;
            cx += triangleCenter.x() * triangleArea;
            cy += triangleCenter.y() * triangleArea;
        }
    }
    
    if (totalArea == 0.0)
    {
        // Если площадь нулевая (все точки на одной линии), возвращаем среднее арифметическое
        double sumX = 0.0, sumY = 0.0;
        for (const QPointF &vertex : m_vertices)
        {
            sumX += vertex.x();
            sumY += vertex.y();
        }
        return QPointF(sumX / m_vertices.size(), sumY / m_vertices.size());
    }
    
    return QPointF(cx / totalArea, cy / totalArea);
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
    
    // Добавим небольшой отступ
    rect.adjust(-5, -5, 5, 5);
    return rect;
}

void PolygonFigure::draw(QPainter *painter) const
{
    if (m_vertices.size() < 2)
        return;
    
    painter->save();
    painter->setPen(QPen(m_color, m_lineWidth));
    painter->setBrush(QBrush(m_fillColor));
    
    QPainterPath path;
    path.moveTo(m_vertices.first());
    
    for (int i = 1; i < m_vertices.size(); i++)
    {
        path.lineTo(m_vertices[i]);
    }
    
    if (m_vertices.size() > 2)
    {
        path.closeSubpath();
    }
    
    painter->drawPath(path);
    painter->restore();
}

QList<QList<QPointF>> PolygonFigure::triangulate() const
{
    QList<QList<QPointF>> triangles;
    
    if (m_vertices.size() < 3)
        return triangles;
    
    // Простая триангуляция для выпуклых полигонов (метод веера)
    QPointF center;
    for (const QPointF &vertex : m_vertices)
    {
        center += vertex;
    }
    center /= m_vertices.size();
    
    for (int i = 0; i < m_vertices.size(); i++)
    {
        int next = (i + 1) % m_vertices.size();
        triangles.append({center, m_vertices[i], m_vertices[next]});
    }
    
    return triangles;
}

void PolygonFigure::setVertices(const QList<QPointF> &vertices)
{
    m_vertices = vertices;
    updateFromVertices();
    emit figureChanged();
}

void PolygonFigure::setVertex(int index, const QPointF &point)
{
    if (index >= 0 && index < m_vertices.size())
    {
        m_vertices[index] = point;
        updateFromVertices();
        emit figureChanged();
    }
}

QList<QPointF> PolygonFigure::getVertices() const
{
    return m_vertices;
}

int PolygonFigure::vertexCount() const
{
    return m_vertices.size();
}

void PolygonFigure::transform(const QTransform &transform)
{
    for (QPointF &vertex : m_vertices)
    {
        vertex = transform.map(vertex);
    }
}