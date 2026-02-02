#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QVector>
#include <QRectF>
#include <QTimer>
#include <QColor>
#include <QTransform>
#include <cmath>

class Figure : public QObject
{
    Q_OBJECT

public:
    explicit Figure(QObject *parent = nullptr);
    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual QPointF centerOfMass() const = 0;
    virtual QRectF boundingRect() const = 0;
    virtual void draw(QPainter *painter) const = 0;
    virtual QString type() const = 0;
    
    virtual QVector<QVector<QPointF>> triangulate() const { return {}; }

    void move(const QPointF &offset);
    void rotate(double angle, const QPointF &center);
    void scale(double factor, const QPointF &center);
    
    void animateMove(const QPointF &target, int duration = 1000);
    void animateRotate(double angle, const QPointF &center, int duration = 1000);
    void animateScale(double factor, const QPointF &center, int duration = 1000);
    
    void moveCenterTo(const QPointF &newCenter);
    void setCenter(const QPointF &center) { moveCenterTo(center); }
    QPointF getCenter() const { return centerOfMass(); }
    
    void setColor(const QColor &color);
    QColor getColor() const;
    
    void setLineWidth(int width);
    int lineWidth() const;
    
    void setFillColor(const QColor &color);
    QColor fillColor() const;

signals:
    void figureChanged();
    void animationProgress(double progress);
    void animationFinished();

protected:
    virtual void transform(const QTransform &transform) = 0;
    
protected slots:
    void updateAnimation();

protected:
    QColor m_color;
    QColor m_fillColor;
    int m_lineWidth;
    QTimer *m_timer;
    
    struct Animation
    {
        enum Type { Move, Rotate, Scale };
        Type type;
        QPointF startCenter;
        QPointF targetCenter;
        double startValue;
        double targetValue;
        QPointF animationCenter;
        int duration;
        int elapsed;
    } m_currentAnimation;
};

#endif // FIGURE_H