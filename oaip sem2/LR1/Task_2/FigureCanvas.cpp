#include "FigureCanvas.h"
#include "PolygonFigure.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <cmath>

FigureCanvas::FigureCanvas(QWidget *parent)
    : QWidget(parent)
    , m_selectedFigure(nullptr)
    , m_drawingTool(new DrawingTool(this))
    , m_scale(1.0)
    , m_offset(0, 0)
    , m_gridEnabled(true)
    , m_showCenters(true)
    , m_showTriangulation(false)
    , m_showVertices(true)
    , m_showBoundingBox(false)
    , m_isDragging(false)
    , m_isPanning(false)
{
    setMinimumSize(600, 400);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    
    // Set background
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(250, 250, 250));
    setPalette(palette);
    setAutoFillBackground(true);
    
    // Connect drawing tool signals
    connect(m_drawingTool, &DrawingTool::figureCreated, this, [this](Figure *figure) {
        addFigure(figure);
        emit figureCreated(figure);
    });
    
    updateViewport();
}

FigureCanvas::~FigureCanvas()
{
    // QObject parent автоматически удалит m_drawingTool
}

DrawingTool::DrawingMode FigureCanvas::drawingMode() const
{
    return m_drawingTool->drawingMode();
}

Figure* FigureCanvas::selectedFigure() const
{
    return m_selectedFigure;
}

double FigureCanvas::scale() const
{
    return m_scale;
}

QPointF FigureCanvas::offset() const
{
    return m_offset;
}

void FigureCanvas::setScale(double scale)
{
    scale = qMax(0.1, qMin(20.0, scale));
    if (qFuzzyCompare(m_scale, scale))
        return;
    
    m_scale = scale;
    updateViewport();
    update();
    emit viewChanged();
}

void FigureCanvas::setOffset(const QPointF &offset)
{
    if (qFuzzyCompare(m_offset.x(), offset.x()) && qFuzzyCompare(m_offset.y(), offset.y()))
        return;
    
    m_offset = offset;
    updateViewport();
    update();
    emit viewChanged();
}

void FigureCanvas::setDrawingMode(DrawingTool::DrawingMode mode)
{
    m_drawingTool->setDrawingMode(mode);
}

void FigureCanvas::setDrawingColor(const QColor &color)
{
    m_drawingTool->setCurrentColor(color);
}

void FigureCanvas::setDrawingFillColor(const QColor &color)
{
    m_drawingTool->setCurrentFillColor(color);
}

void FigureCanvas::setDrawingLineWidth(int width)
{
    m_drawingTool->setCurrentLineWidth(width);
}

void FigureCanvas::zoomIn()
{
    zoom(1.1, QPointF(width()/2.0, height()/2.0));
}

void FigureCanvas::zoomOut()
{
    zoom(1.0/1.1, QPointF(width()/2.0, height()/2.0));
}

void FigureCanvas::zoom(double factor, const QPointF &center)
{
    QPointF mousePos = center.isNull() ? mapFromGlobal(QCursor::pos()) : center;
    QPointF scenePos = (mousePos - m_offset) / m_scale;
    
    m_scale *= factor;
    m_scale = qMax(0.1, qMin(20.0, m_scale));
    
    // Adjust offset so that the point under the mouse stays in the same place
    QPointF newScenePos = (mousePos - m_offset) / m_scale;
    QPointF delta = scenePos - newScenePos;
    m_offset -= delta * m_scale;
    
    updateViewport();
    update();
    emit viewChanged();
}

void FigureCanvas::pan(const QPointF &delta)
{
    m_offset += delta;
    updateViewport();
    update();
    emit viewChanged();
}

void FigureCanvas::resetView()
{
    m_scale = 1.0;
    m_offset = QPointF(0, 0);
    updateViewport();
    update();
    emit viewChanged();
}

void FigureCanvas::fitToView()
{
    if (m_figures.empty())
        return;
        
    // Calculate bounding box of all figures
    QRectF totalBounds;
    for (Figure *figure : m_figures)
    {
        totalBounds = totalBounds.united(figure->boundingRect());
    }
    
    if (totalBounds.isEmpty())
        return;
    
    // Add padding
    totalBounds.adjust(-50, -50, 50, 50);
    
    // Calculate scale to fit
    double widthScale = width() / totalBounds.width();
    double heightScale = height() / totalBounds.height();
    m_scale = qMin(widthScale, heightScale) * 0.9;
    
    // Center the view
    m_offset = QPointF(
        width()/2.0 - totalBounds.center().x() * m_scale,
        height()/2.0 - totalBounds.center().y() * m_scale
    );
    
    updateViewport();
    update();
    emit viewChanged();
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
        // Отключаем все соединения
        disconnect(figure, nullptr, this, nullptr);
        
        m_figures.removeAll(figure);
        
        if (m_selectedFigure == figure)
        {
            m_selectedFigure = nullptr;
            emit figureSelected(nullptr);
        }
        
        update();
    }
}

void FigureCanvas::clearFigures()
{
    // Отключаем все соединения
    for (Figure *figure : m_figures)
    {
        disconnect(figure, nullptr, this, nullptr);
    }
    
    m_figures.clear();
    m_selectedFigure = nullptr;
    emit figureSelected(nullptr);
    update();
}

QList<Figure*> FigureCanvas::getFigures() const
{
    return m_figures;
}

void FigureCanvas::setSelectedFigure(Figure *figure)
{
    if (m_selectedFigure != figure)
    {
        m_selectedFigure = figure;
        update();
        emit figureSelected(figure);
    }
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

void FigureCanvas::setShowVertices(bool show)
{
    m_showVertices = show;
    update();
}

bool FigureCanvas::isShowVertices() const
{
    return m_showVertices;
}

void FigureCanvas::setShowBoundingBox(bool show)
{
    m_showBoundingBox = show;
    update();
}

bool FigureCanvas::isShowBoundingBox() const
{
    return m_showBoundingBox;
}

void FigureCanvas::updateViewport()
{
    m_viewport = QRectF(-m_offset.x() / m_scale, 
                       -m_offset.y() / m_scale,
                       width() / m_scale,
                       height() / m_scale);
}

void FigureCanvas::drawCurrentDrawing(QPainter &painter)
{
    if (!m_drawingTool->isDrawing() || m_currentDrawingPoints.size() < 2)
        return;
    
    painter.save();
    painter.setPen(QPen(Qt::blue, 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    
    // Draw the current drawing path
    QPainterPath path;
    path.moveTo(m_currentDrawingPoints.first());
    
    for (int i = 1; i < m_currentDrawingPoints.size(); i++)
    {
        path.lineTo(m_currentDrawingPoints[i]);
    }
    
    painter.drawPath(path);
    
    // Draw temporary figure based on drawing mode
    if (m_currentDrawingPoints.size() >= 2)
    {
        QPointF start = m_currentDrawingPoints.first();
        QPointF current = m_currentDrawingPoints.last();
        
        switch (m_drawingTool->drawingMode())
        {
        case DrawingTool::DrawRectangle:
        {
            QRectF rect(start, current);
            painter.drawRect(rect.normalized());
            break;
        }
        case DrawingTool::DrawSquare:
        {
            double side = qMin(qAbs(current.x() - start.x()), qAbs(current.y() - start.y()));
            QPointF end = start + QPointF(
                current.x() > start.x() ? side : -side,
                current.y() > start.y() ? side : -side
            );
            painter.drawRect(QRectF(start, end).normalized());
            break;
        }
        case DrawingTool::DrawCircle:
        {
            double radius = QLineF(start, current).length();
            painter.drawEllipse(start, radius, radius);
            break;
        }
        case DrawingTool::DrawTriangle:
        {
            QPolygonF triangle;
            triangle << start 
                    << QPointF(current.x(), start.y())
                    << QPointF(start.x() + (current.x() - start.x()) / 2, current.y());
            painter.drawPolygon(triangle);
            break;
        }
        case DrawingTool::DrawRhombus:
        {
            QPointF center = (start + current) / 2;
            double dx = qAbs(current.x() - start.x()) / 2;
            double dy = qAbs(current.y() - start.y()) / 2;
            
            QPolygonF rhombus;
            rhombus << QPointF(center.x(), center.y() - dy)
                   << QPointF(center.x() + dx, center.y())
                   << QPointF(center.x(), center.y() + dy)
                   << QPointF(center.x() - dx, center.y());
            painter.drawPolygon(rhombus);
            break;
        }
        default:
            break;
        }
    }
    
    painter.restore();
}

void FigureCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw background
    painter.fillRect(rect(), QColor(245, 245, 245));
    
    // Apply transformation
    painter.save();
    painter.translate(m_offset);
    painter.scale(m_scale, m_scale);
    
    // Draw grid if enabled
    if (m_gridEnabled)
    {
        drawGrid(painter);
    }
    
    // Draw all figures
    for (Figure *figure : m_figures)
    {
        figure->draw(&painter);
        
        // Draw triangulation if enabled
        if (m_showTriangulation)
        {
            drawTriangulation(painter, figure);
        }
        
        // Draw center of mass if enabled
        if (m_showCenters)
        {
            painter.save();
            painter.setBrush(Qt::red);
            painter.setPen(QPen(Qt::red, 2));
            QPointF center = figure->centerOfMass();
            painter.drawEllipse(center, 4, 4);
            
            // Draw cross at center
            painter.drawLine(center - QPointF(8, 0), center + QPointF(8, 0));
            painter.drawLine(center - QPointF(0, 8), center + QPointF(0, 8));
            painter.restore();
        }
        
        // Draw bounding box if enabled
        if (m_showBoundingBox)
        {
            painter.save();
            painter.setPen(QPen(QColor(100, 100, 255, 150), 1, Qt::DashLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(figure->boundingRect());
            painter.restore();
        }
        
        // Draw vertices if enabled and figure is polygon
        if (m_showVertices)
        {
            PolygonFigure *polygon = dynamic_cast<PolygonFigure*>(figure);
            if (polygon)
            {
                painter.save();
                painter.setBrush(QColor(255, 100, 100, 200));
                painter.setPen(QPen(QColor(200, 50, 50), 1));
                
                QList<QPointF> vertices = polygon->getVertices();
                for (const QPointF &vertex : vertices)
                {
                    painter.drawEllipse(vertex, 3, 3);
                }
                painter.restore();
            }
        }
    }
    
    // Draw current drawing
    drawCurrentDrawing(painter);
    
    // Draw selection highlight
    if (m_selectedFigure)
    {
        drawSelection(painter, m_selectedFigure);
    }
    
    painter.restore();
}

void FigureCanvas::drawGrid(QPainter &painter)
{
    painter.save();
    
    // Draw major grid lines (every 100 units)
    painter.setPen(QPen(QColor(200, 200, 200), 1, Qt::SolidLine));
    
    int gridSize = 100;
    double startX = std::floor(m_viewport.left() / gridSize) * gridSize;
    double startY = std::floor(m_viewport.top() / gridSize) * gridSize;
    double endX = m_viewport.right();
    double endY = m_viewport.bottom();
    
    for (double x = startX; x <= endX; x += gridSize)
    {
        painter.drawLine(QPointF(x, m_viewport.top()), QPointF(x, m_viewport.bottom()));
    }
    
    for (double y = startY; y <= endY; y += gridSize)
    {
        painter.drawLine(QPointF(m_viewport.left(), y), QPointF(m_viewport.right(), y));
    }
    
    // Draw minor grid lines (every 25 units)
    painter.setPen(QPen(QColor(230, 230, 230), 0.5, Qt::SolidLine));
    gridSize = 25;
    startX = std::floor(m_viewport.left() / gridSize) * gridSize;
    startY = std::floor(m_viewport.top() / gridSize) * gridSize;
    
    for (double x = startX; x <= endX; x += gridSize)
    {
        painter.drawLine(QPointF(x, m_viewport.top()), QPointF(x, m_viewport.bottom()));
    }
    
    for (double y = startY; y <= endY; y += gridSize)
    {
        painter.drawLine(QPointF(m_viewport.left(), y), QPointF(m_viewport.right(), y));
    }
    
    // Draw axes
    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
    painter.drawLine(QPointF(m_viewport.left(), 0), QPointF(m_viewport.right(), 0));
    painter.drawLine(QPointF(0, m_viewport.top()), QPointF(0, m_viewport.bottom()));
    
    painter.restore();
}

void FigureCanvas::drawTriangulation(QPainter &painter, Figure *figure)
{
    QList<QList<QPointF>> triangles = figure->triangulate();
    if (!triangles.isEmpty())
    {
        painter.save();
        painter.setPen(QPen(QColor(100, 100, 255, 150), 1, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        
        for (const auto &triangle : triangles)
        {
            if (triangle.size() == 3)
            {
                painter.drawPolygon(triangle.constData(), triangle.size());
            }
        }
        
        painter.restore();
    }
}

void FigureCanvas::drawSelection(QPainter &painter, Figure *figure)
{
    painter.save();
    
    // Draw bounding box with selection color
    QRectF bounds = figure->boundingRect();
    painter.setPen(QPen(QColor(255, 100, 0, 200), 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(bounds);
    
    // Draw resize handles
    painter.setBrush(QColor(255, 100, 0));
    painter.setPen(Qt::black);
    
    QList<QPointF> handles = {
        bounds.topLeft(),
        bounds.topRight(),
        bounds.bottomRight(),
        bounds.bottomLeft(),
        QPointF(bounds.center().x(), bounds.top()),
        QPointF(bounds.right(), bounds.center().y()),
        QPointF(bounds.center().x(), bounds.bottom()),
        QPointF(bounds.left(), bounds.center().y())
    };
    
    for (const QPointF &handle : handles)
    {
        painter.drawEllipse(handle, 4, 4);
    }
    
    // Draw center of mass for selected figure
    painter.setBrush(Qt::green);
    painter.setPen(QPen(Qt::darkGreen, 1));
    QPointF center = figure->centerOfMass();
    painter.drawEllipse(center, 6, 6);
    
    painter.restore();
}

void FigureCanvas::mousePressEvent(QMouseEvent *event)
{
    QPointF pos = (event->position() - m_offset) / m_scale;
    
    // Check if we're in drawing mode
    if (m_drawingTool->drawingMode() != DrawingTool::NoDrawing)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (!m_drawingTool->isDrawing())
            {
                m_drawingTool->startDrawing(pos);
                m_currentDrawingPoints.clear();
                m_currentDrawingPoints.append(pos);
            }
            else if (m_drawingTool->drawingMode() == DrawingTool::DrawPolygon)
            {
                // For polygons, add point on click
                m_currentDrawingPoints.append(pos);
                m_drawingTool->updateDrawing(pos);
            }
        }
        else if (event->button() == Qt::RightButton && m_drawingTool->isDrawing())
        {
            // Right click to finish polygon drawing
            Figure *figure = m_drawingTool->finishDrawing();
            if (figure)
            {
                addFigure(figure);
                emit figureCreated(figure);
            }
            m_currentDrawingPoints.clear();
        }
        update();
        return;
    }
    
    if (event->button() == Qt::LeftButton)
    {
        // Check if clicking on a figure
        for (Figure *figure : m_figures)
        {
            if (figure->boundingRect().contains(pos))
            {
                m_selectedFigure = figure;
                m_lastMousePos = event->position();
                m_isDragging = true;
                setCursor(Qt::ClosedHandCursor);
                emit figureSelected(figure);
                update();
                return;
            }
        }
        
        // If no figure clicked, start panning
        m_isPanning = true;
        m_panStartPos = event->position();
        setCursor(Qt::OpenHandCursor);
    }
    else if (event->button() == Qt::RightButton)
    {
        // Deselect figure on right click
        if (m_selectedFigure)
        {
            m_selectedFigure = nullptr;
            emit figureSelected(nullptr);
            update();
        }
    }
}

void FigureCanvas::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = (event->position() - m_offset) / m_scale;
    
    if (m_drawingTool->isDrawing())
    {
        // Update current drawing
        if (m_currentDrawingPoints.size() < 2)
        {
            m_currentDrawingPoints.append(pos);
        }
        else
        {
            m_currentDrawingPoints.last() = pos;
        }
        m_drawingTool->updateDrawing(pos);
        update();
        return;
    }
    
    if (m_isDragging && m_selectedFigure)
    {
        QPointF currentPos = event->position();
        QPointF offset = (currentPos - m_lastMousePos) / m_scale;
        
        m_selectedFigure->move(offset);
        m_lastMousePos = currentPos;
        update();
    }
    else if (m_isPanning)
    {
        QPointF currentPos = event->position();
        QPointF delta = currentPos - m_panStartPos;
        m_offset += delta;
        m_panStartPos = currentPos;
        updateViewport();
        update();
    }
    
    // Emit mouse moved signal
    emit mouseMoved(pos);
}

void FigureCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_drawingTool->isDrawing())
        {
            if (m_drawingTool->drawingMode() != DrawingTool::DrawPolygon)
            {
                // For simple shapes, finish on mouse release
                Figure *figure = m_drawingTool->finishDrawing();
                if (figure)
                {
                    addFigure(figure);
                    emit figureCreated(figure);
                }
                m_currentDrawingPoints.clear();
            }
        }
        else
        {
            m_isDragging = false;
            m_isPanning = false;
            setCursor(Qt::ArrowCursor);
        }
        update();
    }
}

void FigureCanvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPointF pos = (event->position() - m_offset) / m_scale;
    
    for (Figure *figure : m_figures)
    {
        if (figure->boundingRect().contains(pos))
        {
            emit figureDoubleClicked(figure);
            break;
        }
    }
}

void FigureCanvas::wheelEvent(QWheelEvent *event)
{
    QPointF mousePos = event->position();
    double factor = 1.1;
    
    if (event->angleDelta().y() > 0)
    {
        zoom(factor, mousePos);
    }
    else
    {
        zoom(1.0/factor, mousePos);
    }
    
    event->accept();
}

void FigureCanvas::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updateViewport();
}