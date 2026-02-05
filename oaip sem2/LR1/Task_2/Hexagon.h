#ifndef HEXAGON_H
#define HEXAGON_H

#include "PolygonFigure.h"

class Hexagon : public PolygonFigure
{
    Q_OBJECT

public:
    explicit Hexagon(QObject *parent = nullptr);
    Hexagon(const QPointF &center, double radius, QObject *parent = nullptr);
    
    QString type() const override;
    
    void setHexagon(const QPointF &center, double radius);
    double radius() const;
    void setRadius(double radius);
};

#endif 