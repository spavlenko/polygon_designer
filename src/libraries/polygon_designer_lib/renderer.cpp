#include "renderer.h"

#include <QPen>
#include <QPolygon>
#include <QPainter>

namespace
{
    namespace Const
    {
        const auto vertexDiameter = 5;
    }

    void drawVertex(QPainter& painter, const Vertex& vertex)
    {
        QRadialGradient gradient(vertex, Const::vertexDiameter / 2);
        gradient.setColorAt(0, Qt::gray);
        gradient.setColorAt(0.8, Qt::darkGray);
        gradient.setColorAt(1, Qt::black);

        painter.setBrush(gradient);
        painter.setPen(QPen(Qt::black));
        painter.drawEllipse(vertex, Const::vertexDiameter, Const::vertexDiameter);
    }

    void drawEdge(QPainter& painter, const QPen& pen, const Edge& edge, const Polygon& polygon)
    {
        painter.setPen(pen);
        painter.drawLine(polygon.getVertex(edge.first), polygon.getVertex(edge.second));
    }
}

PolygonRenderer::PolygonRenderer(const Polygon& polygon, IPolygonRenderingStrategy::Ptr strategy)
    : m_polygonToRender(polygon)
    , m_renderingStrategy(std::move(strategy))
{
}

void PolygonRenderer::draw(QPainter& painter) const
{
    const auto vertexCount = m_polygonToRender.getVertexCount();

    const auto fillBrush = m_renderingStrategy->getFillBrush();

    if(fillBrush.style() != Qt::NoBrush)
    {
        QPolygon poly;

        for(std::size_t i = 0; i < vertexCount; ++i)
            poly << m_polygonToRender.getVertex(i);

        QPainterPath path;
        path.addPolygon(poly);

        painter.drawPolygon(poly);
        painter.fillPath(path, fillBrush);
    }

    const auto edges = m_polygonToRender.getEdgesList();

    for(const auto& edge : edges)
    {
        const auto pen = m_renderingStrategy->getEdgePen(edge, m_polygonToRender);

        drawEdge(painter, pen, edge, m_polygonToRender);
    }

    for (std::size_t i = 0; i < vertexCount; ++i)
    {
        drawVertex(painter, m_polygonToRender.getVertex(i));
    }
}



