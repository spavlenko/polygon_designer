#include "renderer.h"
#include <QPen>
#include <QPolygon>
#include <QPainter>

PolygonRenderer::PolygonRenderer(const Polygon& polygon)
    : m_polygonToRender(polygon)
{
}

void PolygonRenderer::draw(QPainter& painter) const
{
    QPolygon poly;

    const auto vertexCount = m_polygonToRender.getVertexCount();
    for(std::size_t i = 0; i < vertexCount; ++i)
    {
        poly << m_polygonToRender.getVertex(i);
    }

    QPen pen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);

    QPainterPath path;
    path.addPolygon(poly);

    painter.setPen(pen);
    // Draw polygon
    painter.drawPolygon(poly);
    painter.fillPath(path, brush);
}



