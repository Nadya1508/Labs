#include "movable_rectangle.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QMessageBox>
#include <cmath>

MovableRectangle::MovableRectangle(QObject *parent)
    : QObject(parent)
{
    m_state = {QPoint(0, 0), 100, 50, Qt::blue, 0.0f, 0.0f};
    try {
        validateState();
    } catch (const std::exception &e) {
        emitError(QString("Initialization error: %1").arg(e.what()));
        m_state = {QPoint(0, 0), 100, 50, Qt::blue, 0.0f, 0.0f};
    }
}

MovableRectangle::MovableRectangle(const QPoint &pos, int w, int h, 
                                   const QColor &col, QObject *parent)
    : QObject(parent)
{
    m_state = {pos, w, h, col, 0.0f, 0.0f};
    try {
        validateState();
    } catch (const std::exception &e) {
        emitError(QString("Initialization error: %1").arg(e.what()));
        throw;
    }
}

void MovableRectangle::validateState() const
{
    if (m_state.width <= 0 || m_state.height <= 0) {
        throw InvalidSizeException();
    }
    if (m_state.position.x() < -1000 || m_state.position.x() > 10000 ||
        m_state.position.y() < -1000 || m_state.position.y() > 10000) {
        throw InvalidPositionException();
    }
}

void MovableRectangle::emitError(const QString &message) const
{
    qCritical() << "MovableRectangle Error:" << message;
    const_cast<MovableRectangle*>(this)->errorOccurred(message);
}

void MovableRectangle::draw(QPainter &painter)
{
    try {
        painter.save();
        
        // Рисуем прямоугольник
        painter.setBrush(QBrush(m_state.color));
        painter.setPen(QPen(Qt::black, 2));
        painter.drawRoundedRect(m_state.position.x(), m_state.position.y(),
                               m_state.width, m_state.height, 10, 10);
        
        // Информация
        painter.setPen(QPen(Qt::white, 1));
        QFont font = painter.font();
        font.setPointSize(8);
        painter.setFont(font);
        
        QString info = QString("W: %1\nH: %2\nX: %3\nY: %4\nSpeed: (%5, %6)")
            .arg(m_state.width)
            .arg(m_state.height)
            .arg(m_state.position.x())
            .arg(m_state.position.y())
            .arg(m_state.speedX, 0, 'f', 1)
            .arg(m_state.speedY, 0, 'f', 1);
        
        painter.drawText(m_state.position.x() + 5, 
                        m_state.position.y() + 20, 
                        info);
        
        // Рисуем стрелку направления движения
        if (m_state.speedX != 0 || m_state.speedY != 0) {
            painter.setPen(QPen(Qt::red, 3, Qt::SolidLine));
            
            // Центр прямоугольника
            QPoint center(m_state.position.x() + m_state.width / 2,
                         m_state.position.y() + m_state.height / 2);
            
            // Длина стрелки пропорциональна скорости
            float speed = sqrt(m_state.speedX * m_state.speedX + m_state.speedY * m_state.speedY);
            int arrowLength = qMin(50, static_cast<int>(speed * 10 + 20));
            
            // Конец стрелки
            QPoint end(center.x() + static_cast<int>(m_state.speedX * arrowLength / speed),
                      center.y() + static_cast<int>(m_state.speedY * arrowLength / speed));
            
            // Рисуем линию
            painter.drawLine(center, end);
            
            // Рисуем наконечник стрелки
            painter.setBrush(Qt::red);
            painter.setPen(Qt::NoPen);
            
            // Вычисляем угол
            double angle = atan2(m_state.speedY, m_state.speedX);
            int arrowSize = 8;
            
            // Точки треугольника
            QPoint p1 = end;
            QPoint p2(end.x() - arrowSize * cos(angle - M_PI/6),
                     end.y() - arrowSize * sin(angle - M_PI/6));
            QPoint p3(end.x() - arrowSize * cos(angle + M_PI/6),
                     end.y() - arrowSize * sin(angle + M_PI/6));
            
            QPolygon arrowHead;
            arrowHead << p1 << p2 << p3;
            painter.drawPolygon(arrowHead);
        }
        
        painter.restore();
    } catch (const std::exception &e) {
        emitError(QString("Drawing error: %1").arg(e.what()));
    }
}

void MovableRectangle::move()
{
    try {
        QPoint oldPos = m_state.position;
        m_state.position.setX(m_state.position.x() + static_cast<int>(m_state.speedX));
        m_state.position.setY(m_state.position.y() + static_cast<int>(m_state.speedY));
        
        validateState();
        
        emit positionChanged(m_state.position);
        emit stateChanged();
        
        qDebug() << "Rectangle moved from" << oldPos << "to" << m_state.position;
    } catch (const std::exception &e) {
        emitError(QString("Move error: %1").arg(e.what()));
    }
}

void MovableRectangle::setSpeed(float dx, float dy)
{
    try {
        m_state.speedX = dx;
        m_state.speedY = dy;
        emit speedChanged(dx, dy);
        emit stateChanged();
    } catch (const std::exception &e) {
        emitError(QString("Set speed error: %1").arg(e.what()));
    }
}

void MovableRectangle::setPosition(const QPoint &pos)
{
    try {
        m_state.position = pos;
        validateState();
        emit positionChanged(pos);
        emit stateChanged();
    } catch (const std::exception &e) {
        emitError(QString("Set position error: %1").arg(e.what()));
    }
}

void MovableRectangle::setColor(const QColor &col)
{
    try {
        m_state.color = col;
        if (!m_state.color.isValid()) {
            throw std::runtime_error("Invalid color");
        }
        emit colorChanged(col);
        emit stateChanged();
    } catch (const std::exception &e) {
        emitError(QString("Set color error: %1").arg(e.what()));
    }
}

void MovableRectangle::setSize(int w, int h)
{
    try {
        if (w <= 0 || h <= 0) {
            throw InvalidSizeException();
        }
        m_state.width = w;
        m_state.height = h;
        validateState();
        emit sizeChanged(w, h);
        emit stateChanged();
    } catch (const std::exception &e) {
        emitError(QString("Set size error: %1").arg(e.what()));
    }
}

bool MovableRectangle::loadFromFile(const QString &filename)
{
    try {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            throw FileIOException(QString("Cannot open file: %1").arg(filename));
        }
        
        QDataStream stream(&file);
        m_state.deserialize(stream);
        
        validateState();
        emit stateChanged();
        
        qDebug() << "Loaded rectangle from:" << filename;
        return true;
    } catch (const std::exception &e) {
        emitError(QString("Load error: %1").arg(e.what()));
        return false;
    }
}

bool MovableRectangle::saveToFile(const QString &filename) const
{
    try {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            throw FileIOException(QString("Cannot create file: %1").arg(filename));
        }
        
        QDataStream stream(&file);
        m_state.serialize(stream);
        
        qDebug() << "Saved rectangle to:" << filename;
        return true;
    } catch (const std::exception &e) {
        const_cast<MovableRectangle*>(this)->emitError(QString("Save error: %1").arg(e.what()));
        return false;
    }
}

RectangleState MovableRectangle::getState() const
{
    return m_state;
}

void MovableRectangle::setState(const RectangleState &state)
{
    try {
        m_state = state;
        validateState();
        emit stateChanged();
    } catch (const std::exception &e) {
        emitError(QString("Set state error: %1").arg(e.what()));
    }
}

bool MovableRectangle::contains(const QPoint &point) const
{
    QRect rect(m_state.position.x(), m_state.position.y(), 
               m_state.width, m_state.height);
    return rect.contains(point);
}

QRect MovableRectangle::getBoundingRect() const
{
    return QRect(m_state.position.x(), m_state.position.y(), 
                m_state.width, m_state.height);
}

bool MovableRectangle::isValid() const
{
    try {
        validateState();
        return true;
    } catch (...) {
        return false;
    }
}