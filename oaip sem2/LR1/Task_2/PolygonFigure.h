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
    
    // Реализация абстрактных методов
    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    QRectF boundingRect() const override;
    void draw(QPainter *painter) const override;
    
    // Методы для работы с вершинами
    virtual void setVertices(const QVector<QPointF> &vertices);
    QVector<QPointF> getVertices() const;
    
    // Триангуляция для вычисления центра масс и площади
    QVector<QVector<QPointF>> triangulate() const;

protected:
    void transform(const QTransform &transform) override;
    
protected:
    QVector<QPointF> m_vertices;
};

#endif // POLYGONFIGURE_H