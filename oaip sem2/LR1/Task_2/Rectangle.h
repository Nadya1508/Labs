#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Quadrilateral.h"

class Rectangle : public Quadrilateral
{
    Q_OBJECT

public:
    explicit Rectangle(QObject *parent = nullptr);
    Rectangle(const QPointF &topLeft, double width, double height, QObject *parent = nullptr);
    
    QString type() const override { return "Rectangle"; }
    
    void setRectangle(const QPointF &topLeft, double width, double height);
    double width() const;
    double height() const;
    
    void setWidth(double width);
    void setHeight(double height);
};

#endif // RECTANGLE_H