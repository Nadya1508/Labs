#ifndef CUSTOMFIGURE_H
#define CUSTOMFIGURE_H

#include "PolygonFigure.h"

class CustomFigure : public PolygonFigure
{
    Q_OBJECT

public:
    explicit CustomFigure(QObject *parent = nullptr);
    CustomFigure(const QPointF &center, double radius, int sides = 7, QObject *parent = nullptr);
    
    QString type() const override;
    
    void setPolygon(const QPointF &center, double radius, int sides);
    double radius() const;
    int sides() const;
    
    void setRadius(double radius);
    void setSides(int sides);

private:
    int m_sides;
};

#endif // CUSTOMFIGURE_H