#include "car.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

Car::Car(QObject *parent)
    : MovableRectangle(parent)
{
    m_carState = {
        getState(),
        false, false, false,
        CAR_STOPPED,
        Qt::red,
        Qt::black,
        0
    };
}

Car::Car(const QPoint &pos, int w, int h, const QColor &bodyColor, QObject *parent)
    : MovableRectangle(pos, w, h, bodyColor, parent)
{
    m_carState = {
        getState(),
        false, false, false,
        CAR_STOPPED,
        bodyColor,
        Qt::black,
        0
    };
}

void Car::validateCarState() const
{
    if (m_carState.doorAngle < 0 || m_carState.doorAngle > 90) {
        throw std::runtime_error("Invalid door angle");
    }
}

void Car::draw(QPainter &painter)
{
    try {
        painter.save();
        
        drawCarBody(painter);
        drawWheels(painter);
        drawWindows(painter);
        drawDoors(painter);
        drawHeadlights(painter);
        drawDetails(painter);
        
        painter.setPen(QPen(Qt::white, 1));
        painter.setFont(QFont("Arial", 8));
        
        QString info = QString("Speed: %1\nState: %2\nDoors: %3%4\nLights: %5")
            .arg(qAbs(getSpeedX() * 10), 0, 'f', 1)
            .arg(m_carState.state == CAR_MOVING ? "Moving" : 
                 m_carState.state == CAR_PARKED ? "Parked" : "Stopped")
            .arg(m_carState.leftDoorOpen ? "L-" : "L+")
            .arg(m_carState.rightDoorOpen ? "R-" : "R+")
            .arg(m_carState.headlightsOn ? "ON" : "OFF");
        
        painter.drawText(getPosition().x() + getWidth() + 10, 
                        getPosition().y() + 20, 
                        info);
        
        painter.restore();
    } catch (const std::exception &e) {
        emitError(QString("Car drawing error: %1").arg(e.what()));
    }
}

void Car::move()
{
    try {
        MovableRectangle::move();
        
        if (getSpeedX() != 0 && !m_carState.headlightsOn) {
            static int counter = 0;
            if (counter++ % 50 == 0) {
                toggleHeadlights();
            }
        }
        
        if (getSpeedX() == 0 && getSpeedY() == 0) {
            m_carState.state = CAR_STOPPED;
        } else {
            m_carState.state = CAR_MOVING;
        }
        
        emit carStateChanged(m_carState.state);
        emit stateChanged();
        
    } catch (const std::exception &e) {
        emitError(QString("Car move error: %1").arg(e.what()));
    }
}

void Car::toggleLeftDoor()
{
    try {
        m_carState.leftDoorOpen = !m_carState.leftDoorOpen;
        validateCarState();
        emit doorStateChanged(m_carState.leftDoorOpen, m_carState.rightDoorOpen);
        emit stateChanged();
        
        qDebug() << "Left door:" << (m_carState.leftDoorOpen ? "opened" : "closed");
    } catch (const std::exception &e) {
        emitError(QString("Toggle left door error: %1").arg(e.what()));
    }
}

void Car::toggleRightDoor()
{
    try {
        m_carState.rightDoorOpen = !m_carState.rightDoorOpen;
        validateCarState();
        emit doorStateChanged(m_carState.leftDoorOpen, m_carState.rightDoorOpen);
        emit stateChanged();
        
        qDebug() << "Right door:" << (m_carState.rightDoorOpen ? "opened" : "closed");
    } catch (const std::exception &e) {
        emitError(QString("Toggle right door error: %1").arg(e.what()));
    }
}

void Car::toggleHeadlights()
{
    try {
        m_carState.headlightsOn = !m_carState.headlightsOn;
        emit headlightsStateChanged(m_carState.headlightsOn);
        emit stateChanged();
        
        qDebug() << "Headlights:" << (m_carState.headlightsOn ? "on" : "off");
    } catch (const std::exception &e) {
        emitError(QString("Toggle headlights error: %1").arg(e.what()));
    }
}

void Car::openAllDoors()
{
    try {
        m_carState.leftDoorOpen = true;
        m_carState.rightDoorOpen = true;
        m_carState.doorAngle = 45;
        validateCarState();
        emit doorStateChanged(true, true);
        emit stateChanged();
        
        qDebug() << "All doors opened";
    } catch (const std::exception &e) {
        emitError(QString("Open all doors error: %1").arg(e.what()));
    }
}

void Car::closeAllDoors()
{
    try {
        m_carState.leftDoorOpen = false;
        m_carState.rightDoorOpen = false;
        m_carState.doorAngle = 0;
        validateCarState();
        emit doorStateChanged(false, false);
        emit stateChanged();
        
        qDebug() << "All doors closed";
    } catch (const std::exception &e) {
        emitError(QString("Close all doors error: %1").arg(e.what()));
    }
}

void Car::startEngine()
{
    try {
        if (m_carState.state == CAR_STOPPED) {
            m_carState.state = CAR_MOVING;
            // Устанавливаем небольшую скорость для демонстрации
            setSpeed(2, 0);
            emit engineStateChanged(true);
            emit carStateChanged(CAR_MOVING);
            emit stateChanged();
            
            qDebug() << "Engine started";
        }
    } catch (const std::exception &e) {
        emitError(QString("Start engine error: %1").arg(e.what()));
    }
}

void Car::stopEngine()
{
    try {
        if (m_carState.state == CAR_MOVING) {
            m_carState.state = CAR_STOPPED;
            setSpeed(0, 0);
            emit engineStateChanged(false);
            emit carStateChanged(CAR_STOPPED);
            emit stateChanged();
            
            qDebug() << "Engine stopped";
        }
    } catch (const std::exception &e) {
        emitError(QString("Stop engine error: %1").arg(e.what()));
    }
}

void Car::park()
{
    try {
        m_carState.state = CAR_PARKED;
        setSpeed(0, 0);
        closeAllDoors();
        // Выключаем фары при парковке
        if (m_carState.headlightsOn) {
            m_carState.headlightsOn = false;
            emit headlightsStateChanged(false);
        }
        emit carStateChanged(CAR_PARKED);
        emit stateChanged();
        
        qDebug() << "Car parked";
    } catch (const std::exception &e) {
        emitError(QString("Park car error: %1").arg(e.what()));
    }
}

void Car::setBodyColor(const QColor &color)
{
    try {
        if (!color.isValid()) {
            throw std::runtime_error("Invalid body color");
        }
        m_carState.bodyColor = color;
        setColor(color);
        emit stateChanged();
        
        qDebug() << "Body color changed to:" << color.name();
    } catch (const std::exception &e) {
        emitError(QString("Set body color error: %1").arg(e.what()));
    }
}

void Car::setWheelColor(const QColor &color)
{
    try {
        if (!color.isValid()) {
            throw std::runtime_error("Invalid wheel color");
        }
        m_carState.wheelColor = color;
        emit stateChanged();
        
        qDebug() << "Wheel color changed to:" << color.name();
    } catch (const std::exception &e) {
        emitError(QString("Set wheel color error: %1").arg(e.what()));
    }
}

void Car::setCarState(CarState newState)
{
    try {
        m_carState.state = newState;
        validateCarState();
        emit carStateChanged(newState);
        emit stateChanged();
    } catch (const std::exception &e) {
        emitError(QString("Set car state error: %1").arg(e.what()));
    }
}

void Car::updateAnimation()
{
    try {
        if ((m_carState.leftDoorOpen || m_carState.rightDoorOpen) && 
            m_carState.doorAngle < 60) {
            m_carState.doorAngle += 3;
        } else if (!m_carState.leftDoorOpen && !m_carState.rightDoorOpen && 
                   m_carState.doorAngle > 0) {
            m_carState.doorAngle -= 3;
        }
        
        if (m_carState.doorAngle > 60) m_carState.doorAngle = 60;
        if (m_carState.doorAngle < 0) m_carState.doorAngle = 0;
        
        validateCarState();
    } catch (const std::exception &e) {
        emitError(QString("Animation error: %1").arg(e.what()));
    }
}

bool Car::loadFromFile(const QString &filename)
{
    try {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            throw FileIOException(QString("Cannot open file: %1").arg(filename));
        }
        
        QDataStream stream(&file);
        m_carState.deserialize(stream);
        
        // ВАЖНО: обновляем состояние родительского класса
        setState(m_carState.rectState);
        
        validateCarState();
        emit stateChanged();
        
        qDebug() << "Loaded car from:" << filename;
        return true;
    } catch (const std::exception &e) {
        emitError(QString("Load car error: %1").arg(e.what()));
        return false;
    }
}

bool Car::saveToFile(const QString &filename) const
{
    try {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            throw FileIOException(QString("Cannot create file: %1").arg(filename));
        }
        
        QDataStream stream(&file);
        m_carState.serialize(stream);
        
        qDebug() << "Saved car to:" << filename;
        return true;
    } catch (const std::exception &e) {
        emitError(QString("Save car error: %1").arg(e.what()));
        return false;
    }
}

void Car::drawCarBody(QPainter &painter)
{
    QPoint pos = getPosition();
    int w = getWidth();
    int h = getHeight();
    
    painter.setBrush(QBrush(m_carState.bodyColor));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRoundedRect(pos.x(), pos.y(), w, h, 15, 15);
    
    painter.setBrush(QBrush(m_carState.bodyColor.darker(120)));
    painter.drawRect(pos.x() + w * 0.7, pos.y() + h * 0.2, w * 0.3, h * 0.3);
    painter.drawRect(pos.x(), pos.y() + h * 0.2, w * 0.3, h * 0.3);
}

void Car::drawWheels(QPainter &painter)
{
    QPoint pos = getPosition();
    int w = getWidth();
    int h = getHeight();
    int wheelRadius = h / 4;
    
    painter.setBrush(QBrush(m_carState.wheelColor));
    painter.setPen(QPen(Qt::darkGray, 2));
    painter.drawEllipse(pos.x() + w * 0.2 - wheelRadius/2, 
                       pos.y() + h - wheelRadius, 
                       wheelRadius, wheelRadius);
    
    painter.drawEllipse(pos.x() + w * 0.8 - wheelRadius/2, 
                       pos.y() + h - wheelRadius, 
                       wheelRadius, wheelRadius);
    
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(pos.x() + w * 0.2 - wheelRadius/4, 
                       pos.y() + h - wheelRadius/2, 
                       wheelRadius/2, wheelRadius/2);
    
    painter.drawEllipse(pos.x() + w * 0.8 - wheelRadius/4, 
                       pos.y() + h - wheelRadius/2, 
                       wheelRadius/2, wheelRadius/2);
}

void Car::drawWindows(QPainter &painter)
{
    QPoint pos = getPosition();
    int w = getWidth();
    int h = getHeight();
    
    painter.setBrush(QBrush(QColor(200, 230, 255, 180)));
    painter.setPen(QPen(Qt::black, 1));
    
    painter.drawRect(pos.x() + w * 0.3, pos.y() + h * 0.1, w * 0.4, h * 0.2);
    painter.drawRect(pos.x() + w * 0.1, pos.y() + h * 0.3, w * 0.3, h * 0.2);
    painter.drawRect(pos.x() + w * 0.6, pos.y() + h * 0.3, w * 0.3, h * 0.2);
}

void Car::drawDoors(QPainter &painter)
{
    QPoint pos = getPosition();
    int w = getWidth();
    int h = getHeight();
    
    painter.save();
    
    if (m_carState.leftDoorOpen) {
        painter.translate(pos.x() + w * 0.3, pos.y() + h * 0.5);
        painter.rotate(-m_carState.doorAngle);
        painter.translate(-(pos.x() + w * 0.3), -(pos.y() + h * 0.5));
    }
    
    painter.setBrush(QBrush(m_carState.bodyColor.darker(120)));
    painter.setPen(QPen(Qt::black, 1));
    // Дверь БЕЗ окна - простой прямоугольник
    painter.drawRect(pos.x() + w * 0.3, pos.y() + h * 0.3, w * 0.2, h * 0.4);
    
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(pos.x() + w * 0.45, pos.y() + h * 0.5, 5, 5);
    
    painter.restore();
    
    painter.save();
    
    if (m_carState.rightDoorOpen) {
        painter.translate(pos.x() + w * 0.7, pos.y() + h * 0.5);
        painter.rotate(m_carState.doorAngle);
        painter.translate(-(pos.x() + w * 0.7), -(pos.y() + h * 0.5));
    }
    
    painter.setBrush(QBrush(m_carState.bodyColor.darker(120)));
    painter.setPen(QPen(Qt::black, 1));
    // Дверь БЕЗ окна - простой прямоугольник
    painter.drawRect(pos.x() + w * 0.5, pos.y() + h * 0.3, w * 0.2, h * 0.4);
    
    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawEllipse(pos.x() + w * 0.65, pos.y() + h * 0.5, 5, 5);
    
    painter.restore();
}

void Car::drawHeadlights(QPainter &painter)
{
    QPoint pos = getPosition();
    int w = getWidth();
    int h = getHeight();
    
    if (m_carState.headlightsOn) {
        painter.setBrush(QBrush(Qt::yellow));
        painter.setPen(Qt::NoPen);
        
        painter.drawEllipse(pos.x() + w - 10, pos.y() + h * 0.3, 15, 10);
        painter.drawEllipse(pos.x() + w - 10, pos.y() + h * 0.6, 15, 10);
        
        painter.setBrush(QBrush(Qt::red));
        painter.drawEllipse(pos.x() - 5, pos.y() + h * 0.3, 10, 10);
        painter.drawEllipse(pos.x() - 5, pos.y() + h * 0.6, 10, 10);
        
        painter.setPen(QPen(Qt::yellow, 1, Qt::DotLine));
        for (int i = 0; i < 3; ++i) {
            painter.drawLine(pos.x() + w, pos.y() + h * 0.35 + i * 5,
                            pos.x() + w + 30, pos.y() + h * 0.3 + i * 10);
            painter.drawLine(pos.x() + w, pos.y() + h * 0.65 + i * 5,
                            pos.x() + w + 30, pos.y() + h * 0.6 + i * 10);
        }
    } else {
        painter.setBrush(QBrush(Qt::gray));
        painter.setPen(QPen(Qt::black, 1));
        
        painter.drawEllipse(pos.x() + w - 10, pos.y() + h * 0.3, 15, 10);
        painter.drawEllipse(pos.x() + w - 10, pos.y() + h * 0.6, 15, 10);
        
        painter.drawEllipse(pos.x() - 5, pos.y() + h * 0.3, 10, 10);
        painter.drawEllipse(pos.x() - 5, pos.y() + h * 0.6, 10, 10);
    }
}

void Car::drawDetails(QPainter &painter)
{
    QPoint pos = getPosition();
    int w = getWidth();
    int h = getHeight();
    
    painter.setPen(QPen(Qt::black, 1));
    for (int i = 0; i < 5; ++i) {
        painter.drawLine(pos.x() + w - 20, 
                        pos.y() + h * 0.4 + i * 3,
                        pos.x() + w - 5, 
                        pos.y() + h * 0.4 + i * 3);
    }
    
    painter.setBrush(QBrush(Qt::darkGray));
    painter.setPen(Qt::NoPen);
    painter.drawRect(pos.x() + w * 0.1, pos.y() + h - 5, w * 0.8, 5);
    
    painter.setBrush(Qt::white);
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(pos.x() + w * 0.4, pos.y() + h - 10, w * 0.2, 8);
    painter.setPen(Qt::black);
    painter.drawText(pos.x() + w * 0.41, pos.y() + h - 3, "A 777 AA");
}