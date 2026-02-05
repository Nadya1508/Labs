#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

class Square : public Rectangle
{
    Q_OBJECT

public:
    explicit Square(QObject *parent = nullptr);
    Square(const QPointF &topLeft, double side, QObject *parent = nullptr);
    
    QString type() const override;
    
    void setSquare(const QPointF &topLeft, double side);
    double side() const;
    void setSide(double side);
};

#endif 