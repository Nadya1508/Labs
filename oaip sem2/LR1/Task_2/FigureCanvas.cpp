#include "FigureCanvas.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <cmath>

FigureCanvas::FigureCanvas(QWidget *parent)
    : QWidget(parent)
    , m_gridEnabled(true)
    , m_showCenters(true)
    , m_showTriangulation(false)
    , m_selectedFigure(nullptr)
    , m_isDragging(false)
    , m_scale(1.0)
    , m_offset(0, 0)
{
    setMinimumSize(800, 600);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void FigureCanvas::addFigure(Figure *figure)
{
    if (figure && !m_figures.contains(figure))
    {
        m_figures.append(figure);
        connect(figure, &Figure::figureChanged, this, [this]() { update(); });
        update();
    }
}

void FigureCanvas::removeFigure(Figure *figure)
{
    if (figure)
    {
        m_figures.removeAll(figure);
        disconnect(figure, nullptr, this, nullptr);
        update();
    }
}

void FigureCanvas::clearFigures()
{
    for (Figure *figure : m_figures)
    {
        disconnect(figure, nullptr, this, nullptr);
    }
    m_figures.clear();
    update();
}

QVector<Figure*> FigureCanvas::getFigures() const
{
    return m_figures;
}

void FigureCanvas::setGridEnabled(bool enabled)
{
    m_gridEnabled = enabled;
    update();
}

bool FigureCanvas::isGridEnabled() const
{
    return m_gridEnabled;
}

void FigureCanvas::setShowCenters(bool show)
{
    m_showCenters = show;
    update();
}

bool FigureCanvas::isShowCenters() const
{
    return m_showCenters;
}

void FigureCanvas::setShowTriangulation(bool show)
{
    m_showTriangulation = show;
    update();
}

bool FigureCanvas::isShowTriangulation() const
{
    return m_showTriangulation;
}

void FigureCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Применяем масштаб и смещение
    painter.save();
    painter.translate(m_offset);
    painter.scale(m_scale, m_scale);
    
    // Очистка фона
    painter.fillRect(rect(), QColor(240, 240, 240));
    
    // Рисуем сетку
    if (m_gridEnabled)
    {
        drawGrid(painter);
    }
    
    // Рисуем все фигуры
    for (Figure *figure : m_figures)
    {
        figure->draw(&painter);
        
        // Рисуем триангуляцию, если включено
        if (m_showTriangulation)
        {
            drawTriangulation(painter, figure);
        }
        
        // Рисуем центр масс, если включено
        if (m_showCenters)
        {
            painter.save();
            painter.setBrush(Qt::red);
            painter.setPen(Qt::red);
            QPointF center = figure->centerOfMass();
            painter.drawEllipse(center, 5, 5);
            
            // Подписываем координаты центра
            painter.setPen(Qt::darkRed);
            painter.drawText(center + QPointF(10, -10), 
                           QString("(%1, %2)").arg(center.x(), 0, 'f', 0).arg(center.y(), 0, 'f', 0));
            painter.restore();
        }
    }
    
    painter.restore();
    
    // Рисуем информацию о масштабе
    painter.setPen(Qt::black);
    painter.drawText(10, 20, QString("Scale: %1x").arg(m_scale, 0, 'f', 2));
    painter.drawText(10, 40, QString("Figures: %1").arg(m_figures.size()));
}

void FigureCanvas::drawGrid(QPainter &painter)
{
    painter.save();
    painter.setPen(QPen(QColor(200, 200, 200), 1, Qt::SolidLine));
    
    int gridSize = 50;
    QRectF visibleRect = rect();
    
    // Вертикальные линии
    for (int x = static_cast<int>(visibleRect.left() - m_offset.x()); 
         x < visibleRect.right(); x += gridSize)
    {
        painter.drawLine(x, visibleRect.top(), x, visibleRect.bottom());
    }
    
    // Горизонтальные линии
    for (int y = static_cast<int>(visibleRect.top() - m_offset.y()); 
         y < visibleRect.bottom(); y += gridSize)
    {
        painter.drawLine(visibleRect.left(), y, visibleRect.right(), y);
    }
    
    // Центральные оси
    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
    painter.drawLine(visibleRect.left(), -m_offset.y(), 
                     visibleRect.right(), -m_offset.y());
    painter.drawLine(-m_offset.x(), visibleRect.top(), 
                     -m_offset.x(), visibleRect.bottom());
    
    painter.restore();
}

void FigureCanvas::drawTriangulation(QPainter &painter, Figure *figure)
{
    QVector<QVector<QPointF>> triangles = figure->triangulate();
    if (!triangles.isEmpty())
    {
        painter.save();
        painter.setPen(QPen(QColor(100, 100, 255, 150), 1, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        
        for (const auto &triangle : triangles)
        {
            if (triangle.size() == 3)
            {
                painter.drawPolygon(triangle.data(), triangle.size());
                
                // Рисуем центры треугольников
                QPointF center = (triangle[0] + triangle[1] + triangle[2]) / 3;
                painter.setBrush(QColor(255, 100, 100, 100));
                painter.drawEllipse(center, 3, 3);
            }
        }
        
        painter.restore();
    }
}

void FigureCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Преобразуем координаты с учетом масштаба и смещения
        QPointF pos = (event->position() - m_offset) / m_scale;
        
        // Ищем фигуру, по которой кликнули
        for (Figure *figure : m_figures)
        {
            if (figure->boundingRect().contains(pos))
            {
                m_selectedFigure = figure;
                m_lastMousePos = event->position();
                m_isDragging = true;
                setCursor(Qt::ClosedHandCursor);
                break;
            }
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        // Сброс масштаба и смещения
        m_scale = 1.0;
        m_offset = QPointF(0, 0);
        update();
    }
}

void FigureCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging && m_selectedFigure)
    {
        // Перемещение фигуры
        QPointF currentPos = event->position();
        QPointF offset = (currentPos - m_lastMousePos) / m_scale;
        
        m_selectedFigure->move(offset);
        m_lastMousePos = currentPos;
        update();
    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        // Прокрутка канваса
        QPointF currentPos = event->position();
        QPointF delta = currentPos - m_lastMousePos;
        m_offset += delta;
        m_lastMousePos = currentPos;
        update();
    }
}

void FigureCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isDragging = false;
        m_selectedFigure = nullptr;
        setCursor(Qt::ArrowCursor);
    }
}

void FigureCanvas::wheelEvent(QWheelEvent *event)
{
    // Масштабирование колесиком мыши
    double scaleFactor = 1.1;
    if (event->angleDelta().y() > 0)
    {
        m_scale *= scaleFactor;
    }
    else
    {
        m_scale /= scaleFactor;
    }
    
    // Ограничиваем масштаб
    m_scale = qMax(0.1, qMin(10.0, m_scale));
    
    update();
}