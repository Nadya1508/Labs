#ifndef POLYGON_H
#define POLYGON_H

#include "PolygonFigure.h"

class Polygon : public PolygonFigure
{
    Q_OBJECT

public:
    explicit Polygon(QObject *parent = nullptr);
    Polygon(const QPointF &center, double radius, int sides, QObject *parent = nullptr);
    
    QString type() const override;
    
    int sides() const;
    double radius() const;
    
    void setSides(int sides);
    void setRadius(double radius);
    void setRegularPolygon(const QPointF &center, double radius, int sides);

private:
    int m_sides;
};

#endif 