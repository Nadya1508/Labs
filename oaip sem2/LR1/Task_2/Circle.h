#ifndef CIRCLE_H
#define CIRCLE_H

#include "Figure.h"

class Circle : public Figure
{
    Q_OBJECT

public:
    explicit Circle(QObject *parent = nullptr);
    Circle(const QPointF &center, double radius, QObject *parent = nullptr);
    
    // Реализация абстрактных методов
    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    QRectF boundingRect() const override;
    void draw(QPainter *painter) const override;
    QString type() const override { return "Circle"; }
    
    // Специфичные методы
    void setCircle(const QPointF &center, double radius);
    double radius() const;
    void setRadius(double radius);

protected:
    void transform(const QTransform &transform) override;
    
private:
    QPointF m_center;
    double m_radius;
};

#endif // CIRCLE_H