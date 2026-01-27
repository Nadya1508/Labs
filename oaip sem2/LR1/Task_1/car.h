#ifndef CAR_H
#define CAR_H

#include "movable_rectangle.h"
#include <QPainter>
#include <QTransform>

// Состояния автомобиля
enum CarState {
    CAR_STOPPED,
    CAR_MOVING,
    CAR_PARKED
};

// Структура состояния автомобиля
struct CarStateRecord {
    RectangleState rectState;
    bool leftDoorOpen;
    bool rightDoorOpen;
    bool headlightsOn;
    CarState state;
    QColor bodyColor;
    QColor wheelColor;
    int doorAngle;
    
    void serialize(QDataStream &stream) const {
        rectState.serialize(stream);
        stream << leftDoorOpen << rightDoorOpen << headlightsOn 
               << static_cast<int>(state) << bodyColor << wheelColor << doorAngle;
    }
    
    void deserialize(QDataStream &stream) {
        rectState.deserialize(stream);
        int stateInt;
        stream >> leftDoorOpen >> rightDoorOpen >> headlightsOn 
               >> stateInt >> bodyColor >> wheelColor >> doorAngle;
        state = static_cast<CarState>(stateInt);
    }
    
    QString toString() const {
        return QString("Car[%1, Doors: L%2 R%3, Lights: %4, State: %5]")
            .arg(rectState.toString())
            .arg(leftDoorOpen ? "Open" : "Closed")
            .arg(rightDoorOpen ? "Open" : "Closed")
            .arg(headlightsOn ? "On" : "Off")
            .arg(state == CAR_MOVING ? "Moving" : state == CAR_PARKED ? "Parked" : "Stopped");
    }
};

class Car : public MovableRectangle
{
    Q_OBJECT

public:
    explicit Car(QObject *parent = nullptr);
    Car(const QPoint &pos, int w, int h, const QColor &bodyColor, QObject *parent = nullptr);
    virtual ~Car() = default;
    
    // Переопределенные методы
    virtual void draw(QPainter &painter) override;
    virtual void move() override;
    virtual bool loadFromFile(const QString &filename) override;
    virtual bool saveToFile(const QString &filename) const override;
    
    // Новые методы для автомобиля
    void toggleLeftDoor();
    void toggleRightDoor();
    void toggleHeadlights();
    void openAllDoors();
    void closeAllDoors();
    void startEngine();
    void stopEngine();
    void park();
    
    void setBodyColor(const QColor &color);
    void setWheelColor(const QColor &color);
    void setCarState(CarState newState);
    
    // Геттеры
    bool isLeftDoorOpen() const { return m_carState.leftDoorOpen; }
    bool isRightDoorOpen() const { return m_carState.rightDoorOpen; }
    bool areHeadlightsOn() const { return m_carState.headlightsOn; }
    CarState getCarState() const { return m_carState.state; }
    QColor getBodyColor() const { return m_carState.bodyColor; }
    CarStateRecord getCarStateRecord() const { return m_carState; }
    
    // Анимация
    void updateAnimation();

signals:
    void doorStateChanged(bool leftOpen, bool rightOpen);
    void headlightsStateChanged(bool on);
    void engineStateChanged(bool running);
    void carStateChanged(CarState newState);

private:
    CarStateRecord m_carState;
    
    void drawCarBody(QPainter &painter);
    void drawWheels(QPainter &painter);
    void drawWindows(QPainter &painter);
    void drawDoors(QPainter &painter);
    void drawHeadlights(QPainter &painter);
    void drawDetails(QPainter &painter);
    
    void validateCarState() const;
};

#endif // CAR_H