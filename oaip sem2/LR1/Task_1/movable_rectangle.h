#ifndef MOVABLE_RECTANGLE_H
#define MOVABLE_RECTANGLE_H

#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QRect>
#include <QString>
#include <QDataStream>
#include <stdexcept>

struct RectangleState {
    QPoint position;
    int width;
    int height;
    QColor color;
    float speedX;
    float speedY;
    
    void serialize(QDataStream &stream) const {
        stream << position << width << height << color << speedX << speedY;
    }
    
    void deserialize(QDataStream &stream) {
        stream >> position >> width >> height >> color >> speedX >> speedY;
    }
    
    QString toString() const {
        return QString("Rect[Pos:(%1,%2) Size:%3x%4 Color:%5 Speed:(%6,%7)]")
            .arg(position.x()).arg(position.y())
            .arg(width).arg(height)
            .arg(color.name())
            .arg(speedX).arg(speedY);
    }
};

class MovableRectangle : public QObject
{
    Q_OBJECT

public:
    explicit MovableRectangle(QObject *parent = nullptr);
    MovableRectangle(const QPoint &pos, int w, int h, const QColor &col, 
                     QObject *parent = nullptr);
    virtual ~MovableRectangle() = default;
    
    virtual void draw(QPainter &painter);
    virtual void move();
    virtual void setSpeed(float dx, float dy);
    virtual void setPosition(const QPoint &pos);
    virtual void setColor(const QColor &col);
    virtual void setSize(int w, int h);
    
    virtual bool loadFromFile(const QString &filename);
    virtual bool saveToFile(const QString &filename) const;
    virtual RectangleState getState() const;
    virtual void setState(const RectangleState &state);
    
    QPoint getPosition() const { return m_state.position; }
    int getWidth() const { return m_state.width; }
    int getHeight() const { return m_state.height; }
    QColor getColor() const { return m_state.color; }
    float getSpeedX() const { return m_state.speedX; }
    float getSpeedY() const { return m_state.speedY; }
    
    virtual bool contains(const QPoint &point) const;
    virtual QRect getBoundingRect() const;
    virtual bool isValid() const;
    
    class InvalidSizeException : public std::runtime_error {
    public:
        InvalidSizeException() : std::runtime_error("Invalid size: width and height must be positive") {}
    };
    
    class InvalidPositionException : public std::runtime_error {
    public:
        InvalidPositionException() : std::runtime_error("Invalid position") {}
    };
    
    class FileIOException : public std::runtime_error {
    public:
        FileIOException(const QString &message) : std::runtime_error(message.toStdString()) {}
    };

signals:
    void positionChanged(const QPoint &newPos);
    void sizeChanged(int newWidth, int newHeight);
    void colorChanged(const QColor &newColor);
    void speedChanged(float newSpeedX, float newSpeedY);
    void stateChanged();
    void errorOccurred(const QString &errorMessage);

protected:
    RectangleState m_state;
    void emitError(const QString &message) const;

private:
    void validateState() const;
};

#endif // MOVABLE_RECTANGLE_H