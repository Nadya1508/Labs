#ifndef STAR_H
#define STAR_H

#include "PolygonFigure.h"

class Star : public PolygonFigure
{
    Q_OBJECT

public:
    enum StarType { FivePointed = 5, SixPointed = 6, EightPointed = 8 };
    
    explicit Star(QObject *parent = nullptr);
    Star(const QPointF &center, double outerRadius, double innerRadius, 
         StarType type = FivePointed, QObject *parent = nullptr);
    
    QString type() const override { return "Star"; }
    
    void setStar(const QPointF &center, double outerRadius, double innerRadius, StarType type);
    double outerRadius() const;
    double innerRadius() const;
    StarType starType() const;
    
    void setOuterRadius(double radius);
    void setInnerRadius(double radius);
    void setStarType(StarType type);

private:
    StarType m_type;
};

#endif // STAR_H