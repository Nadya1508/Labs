#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "PolygonFigure.h"

class Quadrilateral : public PolygonFigure
{
    Q_OBJECT

public:
    explicit Quadrilateral(QObject *parent = nullptr);
    
    QString type() const override { return "Quadrilateral"; }
    
    virtual void setPoints(const QPointF &p1, const QPointF &p2, 
                          const QPointF &p3, const QPointF &p4);
    QVector<QPointF> getPoints() const;
};

#endif // QUADRILATERAL_H