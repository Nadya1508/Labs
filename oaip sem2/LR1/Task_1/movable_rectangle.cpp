#include "movable_rectangle.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QMessageBox>

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
        
        painter.setBrush(QBrush(m_state.color));
        painter.setPen(QPen(Qt::black, 2));
        
        painter.drawRoundedRect(m_state.position.x(), m_state.position.y(),
                               m_state.width, m_state.height, 10, 10);
        
        painter.setPen(QPen(Qt::white, 1));
        QFont font = painter.font();
        font.setPointSize(8);
        painter.setFont(font);
        
        QString info = QString("W: %1\nH: %2\nX: %3\nY: %4")
            .arg(m_state.width)
            .arg(m_state.height)
            .arg(m_state.position.x())
            .arg(m_state.position.y());
        
        painter.drawText(m_state.position.x() + 5, 
                        m_state.position.y() + 20, 
                        info);
        
        if (m_state.speedX != 0 || m_state.speedY != 0) {
            painter.setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
            QPoint center(m_state.position.x() + m_state.width / 2,
                         m_state.position.y() + m_state.height / 2);
            QPoint end(center.x() + static_cast<int>(m_state.speedX * 15),
                      center.y() + static_cast<int>(m_state.speedY * 15));
            
            painter.drawLine(center, end);
            
            painter.setBrush(Qt::yellow);
            QPolygon arrow;
            arrow << end 
                  << QPoint(end.x() - 5, end.y() - 5)
                  << QPoint(end.x() - 5, end.y() + 5);
            painter.drawPolygon(arrow);
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