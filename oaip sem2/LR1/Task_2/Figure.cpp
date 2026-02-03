#include "Figure.h"
#include <QPainter>

Figure::Figure(QObject *parent) 
    : QObject(parent)
    , m_color(Qt::blue)
    , m_fillColor(Qt::lightGray)
    , m_lineWidth(2)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(16); // ~60 FPS
    connect(m_timer, &QTimer::timeout, this, &Figure::updateAnimation);
}

void Figure::move(const QPointF &offset)
{
    QTransform transform;
    transform.translate(offset.x(), offset.y());
    this->transform(transform);
    emit figureChanged();
}

void Figure::rotate(double angle, const QPointF &center)
{
    QTransform transform;
    transform.translate(center.x(), center.y());
    transform.rotate(angle);
    transform.translate(-center.x(), -center.y());
    this->transform(transform);
    emit figureChanged();
}

void Figure::scale(double factor, const QPointF &center)
{
    QTransform transform;
    transform.translate(center.x(), center.y());
    transform.scale(factor, factor);
    transform.translate(-center.x(), -center.y());
    this->transform(transform);
    emit figureChanged();
}

void Figure::animateMove(const QPointF &target, int duration)
{
    m_currentAnimation.type = Animation::Move;
    m_currentAnimation.startCenter = getCenter();
    m_currentAnimation.targetCenter = target;
    m_currentAnimation.duration = duration;
    m_currentAnimation.elapsed = 0;
    
    m_timer->start();
    emit animationProgress(0);
}

void Figure::animateRotate(double angle, const QPointF &center, int duration)
{
    m_currentAnimation.type = Animation::Rotate;
    m_currentAnimation.startValue = 0;
    m_currentAnimation.targetValue = angle;
    m_currentAnimation.animationCenter = center;
    m_currentAnimation.duration = duration;
    m_currentAnimation.elapsed = 0;
    
    m_timer->start();
    emit animationProgress(0);
}

void Figure::animateScale(double factor, const QPointF &center, int duration)
{
    m_currentAnimation.type = Animation::Scale;
    m_currentAnimation.startValue = 1.0;
    m_currentAnimation.targetValue = factor;
    m_currentAnimation.animationCenter = center;
    m_currentAnimation.duration = duration;
    m_currentAnimation.elapsed = 0;
    
    m_timer->start();
    emit animationProgress(0);
}

void Figure::stopAnimation()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
        m_currentAnimation.type = Animation::None;
        emit animationFinished();
    }
}

void Figure::moveCenterTo(const QPointF &newCenter)
{
    QPointF currentCenter = getCenter();
    QPointF offset = newCenter - currentCenter;
    move(offset);
}

void Figure::setColor(const QColor &color)
{
    m_color = color;
    emit figureChanged();
}

QColor Figure::getColor() const
{
    return m_color;
}

void Figure::setLineWidth(int width)
{
    m_lineWidth = width;
    emit figureChanged();
}

int Figure::lineWidth() const
{
    return m_lineWidth;
}

void Figure::setFillColor(const QColor &color)
{
    m_fillColor = color;
    emit figureChanged();
}

QColor Figure::fillColor() const
{
    return m_fillColor;
}

void Figure::updateAnimation()
{
    m_currentAnimation.elapsed += m_timer->interval();
    double progress = qMin(1.0, static_cast<double>(m_currentAnimation.elapsed) / m_currentAnimation.duration);
    
    emit animationProgress(progress);
    
    switch (m_currentAnimation.type)
    {
    case Animation::Move:
    {
        QPointF newCenter = m_currentAnimation.startCenter + 
                           (m_currentAnimation.targetCenter - m_currentAnimation.startCenter) * progress;
        QPointF offset = newCenter - getCenter();
        if (!offset.isNull()) {
            move(offset);
        }
        break;
    }
    case Animation::Rotate:
    {
        double angle = m_currentAnimation.startValue + 
                      (m_currentAnimation.targetValue - m_currentAnimation.startValue) * progress;
        double angleToApply = angle - (progress > 0 ? (m_currentAnimation.startValue + 
                      (m_currentAnimation.targetValue - m_currentAnimation.startValue) * 
                      ((progress - m_timer->interval()/static_cast<double>(m_currentAnimation.duration)))) : 0);
        rotate(angleToApply, m_currentAnimation.animationCenter);
        break;
    }
    case Animation::Scale:
    {
        double factor = m_currentAnimation.startValue + 
                       (m_currentAnimation.targetValue - m_currentAnimation.startValue) * progress;
        double lastFactor = progress > 0 ? (m_currentAnimation.startValue + 
                       (m_currentAnimation.targetValue - m_currentAnimation.startValue) * 
                       ((progress - m_timer->interval()/static_cast<double>(m_currentAnimation.duration)))) : 1.0;
        double scaleToApply = factor / lastFactor;
        scale(scaleToApply, m_currentAnimation.animationCenter);
        break;
    }
    case Animation::None:
        break;
    }
    
    if (progress >= 1.0)
    {
        m_timer->stop();
        m_currentAnimation.type = Animation::None;
        emit animationFinished();
    }
}