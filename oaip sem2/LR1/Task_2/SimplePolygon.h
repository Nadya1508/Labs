#ifndef SIMPLEPOLYGON_H
#define SIMPLEPOLYGON_H

#include "PolygonFigure.h"
#include <QObject>

class SimplePolygon : public PolygonFigure
{
    Q_OBJECT

public:
    explicit SimplePolygon(QObject *parent = nullptr);
    SimplePolygon(const QPointF &center, double radius, int sides = 7, QObject *parent = nullptr);
    
    QString type() const override { return "Polygon"; }
    
    void setPolygon(const QPointF &center, double radius, int sides);
    double radius() const;
    int sides() const;
    
    void setRadius(double radius);
    void setSides(int sides);

private:
    int m_sides;
};

#endif 