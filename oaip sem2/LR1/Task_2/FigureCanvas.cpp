#include "FigureCanvas.h"
#include <QPainter>
#include <QMouseEvent>

FigureCanvas::FigureCanvas(QWidget *parent)
    : QWidget(parent)
    , m_gridEnabled(true)
    , m_showCenters(true)
    , m_selectedFigure(nullptr)
    , m_isDragging(false)
{
    setMinimumSize(600, 400);
    setMouseTracking(true);
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

void FigureCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Очистка фона
    painter.fillRect(rect(), Qt::white);
    
    // Рисуем сетку
    if (m_gridEnabled)
    {
        drawGrid(painter);
    }
    
    // Рисуем все фигуры
    for (Figure *figure : m_figures)
    {
        figure->draw(&painter);
    }
}

void FigureCanvas::drawGrid(QPainter &painter)
{
    painter.save();
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));
    
    int gridSize = 20;
    
    // Вертикальные линии
    for (int x = 0; x < width(); x += gridSize)
    {
        painter.drawLine(x, 0, x, height());
    }
    
    // Горизонтальные линии
    for (int y = 0; y < height(); y += gridSize)
    {
        painter.drawLine(0, y, width(), y);
    }
    
    painter.restore();
}

void FigureCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->position();
        
        // Ищем фигуру, по которой кликнули
        for (Figure *figure : m_figures)
        {
            if (figure->boundingRect().contains(pos))
            {
                m_selectedFigure = figure;
                m_lastMousePos = pos;
                m_isDragging = true;
                break;
            }
        }
    }
}

void FigureCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging && m_selectedFigure)
    {
        QPointF currentPos = event->position();
        QPointF offset = currentPos - m_lastMousePos;
        
        m_selectedFigure->move(offset);
        m_lastMousePos = currentPos;
    }
}

void FigureCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    
    if (event->button() == Qt::LeftButton)
    {
        m_isDragging = false;
        m_selectedFigure = nullptr;
    }
}