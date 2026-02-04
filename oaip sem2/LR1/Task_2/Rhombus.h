#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "PolygonFigure.h"

class Rhombus : public PolygonFigure
{
    Q_OBJECT

public:
    explicit Rhombus(QObject *parent = nullptr);
    Rhombus(const QPointF &center, double diagonal1, double diagonal2, QObject *parent = nullptr);
    
    QString type() const override;
    
    void setRhombus(const QPointF &center, double diagonal1, double diagonal2);
    double diagonal1() const;
    double diagonal2() const;
    
    void setDiagonal1(double d1);
    void setDiagonal2(double d2);
};

#endif // RHOMBUS_H