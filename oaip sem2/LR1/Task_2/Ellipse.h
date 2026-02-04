#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Figure.h"

class Ellipse : public Figure
{
    Q_OBJECT

public:
    explicit Ellipse(QObject *parent = nullptr);
    Ellipse(const QPointF &center, double radiusX, double radiusY, QObject *parent = nullptr);
    
    double area() const override;
    double perimeter() const override;
    QPointF centerOfMass() const override;
    QRectF boundingRect() const override;
    void draw(QPainter *painter) const override;
    QString type() const override;
    
    void setEllipse(const QPointF &center, double radiusX, double radiusY);
    double radiusX() const;
    double radiusY() const;
    
    void setRadiusX(double radius);
    void setRadiusY(double radius);

protected:
    void transform(const QTransform &transform) override;
    
private:
    QPointF m_center;
    double m_radiusX;
    double m_radiusY;
};

#endif // ELLIPSE_H