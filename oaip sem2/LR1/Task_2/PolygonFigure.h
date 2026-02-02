#ifndef POLYGONFIGURE_H
#define POLYGONFIGURE_H

#include "Figure.h"
#include <QVector>
#include <QPointF>

class PolygonFigure : public Figure
{
    Q_OBJECT

public:
    explicit PolygonFigure(QObject *parent = nullptr);
    
    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    QRectF boundingRect() const override;
    void draw(QPainter *painter) const override;
    
    QVector<QVector<QPointF>> triangulate() const override;
    
    virtual void setVertices(const QVector<QPointF> &vertices);
    virtual void setVertex(int index, const QPointF &point);
    QVector<QPointF> getVertices() const;
    int vertexCount() const;
    
    virtual void updateFromVertices() {}

protected:
    void transform(const QTransform &transform) override;
    
protected:
    QVector<QPointF> m_vertices;
    
private:
    double triangleArea(const QPointF &a, const QPointF &b, const QPointF &c) const;
};

#endif // POLYGONFIGURE_H