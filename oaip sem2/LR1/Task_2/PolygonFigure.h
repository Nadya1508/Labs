#ifndef POLYGONFIGURE_H
#define POLYGONFIGURE_H

#include "Figure.h"
#include <QList>
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
    
    QList<QList<QPointF>> triangulate() const override;
    
    virtual void setVertices(const QList<QPointF> &vertices);
    virtual void setVertex(int index, const QPointF &point);
    QList<QPointF> getVertices() const;
    int vertexCount() const;
    
    // Сделаем эту функцию виртуальной без реализации по умолчанию
    virtual void updateFromVertices() { emit figureChanged(); }

protected:
    void transform(const QTransform &transform) override;
    
protected:
    QList<QPointF> m_vertices;
    
private:
    double triangleArea(const QPointF &a, const QPointF &b, const QPointF &c) const;
};

#endif // POLYGONFIGURE_H