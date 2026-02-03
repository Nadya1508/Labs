#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "PolygonFigure.h"

class Triangle : public PolygonFigure
{
    Q_OBJECT

public:
    explicit Triangle(QObject *parent = nullptr);
    Triangle(const QPointF &p1, const QPointF &p2, const QPointF &p3, QObject *parent = nullptr);
    
    QString type() const override;
    
    void setPoints(const QPointF &p1, const QPointF &p2, const QPointF &p3);
    QList<QPointF> getPoints() const;
};

#endif // TRIANGLE_H