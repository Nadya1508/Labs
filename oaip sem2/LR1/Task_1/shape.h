#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPainter>
#include <QRect>
#include <QColor>

class Shape : public QObject
{
    Q_OBJECT

protected:
    int x, y;
    QColor color;
    bool isValidPosition;
    bool isValidColor;

public:
    explicit Shape(QObject *parent = nullptr);
    virtual ~Shape() = default;

    virtual void draw(QPainter *painter) = 0;
    virtual void move(int dx, int dy);
    virtual void setPosition(int newX, int newY);
    virtual void setColor(const QColor &newColor);
    virtual QRect getBounds() const = 0;
    virtual QString getInfo() const = 0;
    virtual bool containsPoint(const QPoint &point) const = 0;

    int getX() const { return x; }
    int getY() const { return y; }
    QColor getColor() const { return color; }
    bool getIsValidPosition() const { return isValidPosition; }
    bool getIsValidColor() const { return isValidColor; }

    virtual bool validatePosition(int x, int y);
    virtual bool validateColor(const QColor &color);

signals:
    void positionChanged(int x, int y);
    void colorChanged(const QColor &color);
    void validationError(const QString &message);
};

#endif 