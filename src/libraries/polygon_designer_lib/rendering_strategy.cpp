#include "rendering_strategy.h"

QBrush PermanentPolygonRenderingStrategy::getFillBrush() const
{
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);

    return brush;
}

QPen PermanentPolygonRenderingStrategy::getEdgePen(const Edge& edge, const Polygon& polygon) const
{
    Q_UNUSED(edge);
    return QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

QBrush EditingPolygonRenderingStrategy::getFillBrush() const
{
    return QBrush(Qt::NoBrush);
}

QPen EditingPolygonRenderingStrategy::getEdgePen(const Edge& edge, const Polygon& polygon) const
{
    QPen pattern(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    if (polygon.getVertexCount() < 3)
    {
        pattern.setStyle(Qt::DashLine);

        return pattern;
    }

    if (m_pendingVertex.has_value())
    {
        if (edge.first == m_pendingVertex.value())
        {
            pattern.setColor(Qt::green);
        }
        else if (edge.second == m_pendingVertex.value())
        {
            pattern.setStyle(Qt::DashLine);
            pattern.setColor(Qt::green);
        }

        return  pattern;
    }

    const bool isLastEdge = edge.second == 0;

    if (isLastEdge)
    {
        pattern.setStyle(Qt::DashLine);
        pattern.setColor(Qt::green);
    }

    return pattern;
}

void EditingPolygonRenderingStrategy::setPendingPoint(const std::experimental::optional<std::size_t>& pendingVertex)
{
    m_pendingVertex = pendingVertex;
}


