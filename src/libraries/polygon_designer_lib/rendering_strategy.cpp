#include "rendering_strategy.h"

namespace
{
    namespace Const
    {
        const auto edgeWidth = 3;
    }
}

QBrush PolygonDefaultRenderingStrategy::getFillBrush() const
{
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);

    return brush;
}

QPen PolygonDefaultRenderingStrategy::getEdgePen(const Edge& edge, const Polygon& polygon) const
{
    Q_UNUSED(edge);
    return QPen(Qt::black, Const::edgeWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

QBrush EditingPolygonRenderingStrategy::getFillBrush() const
{
    return QBrush(Qt::NoBrush);
}

QPen EditingPolygonRenderingStrategy::getEdgePen(const Edge& edge, const Polygon& polygon) const
{
    const bool isLastEdge = edge.second == 0;
    const auto style = isLastEdge ? Qt::DashLine : Qt::SolidLine;

    QPen pattern(Qt::black, Const::edgeWidth, style, Qt::RoundCap, Qt::RoundJoin);

    //todo: const
    if (polygon.getVertexCount() < 3)
        return pattern;

    const bool isPendingEdge = m_pendingVertex.has_value() &&
        (edge.first == m_pendingVertex.value() || edge.second == m_pendingVertex.value());

    auto color = isLastEdge || isPendingEdge ? Qt::green : Qt::black;

    if (isPendingEdge && !m_isPendingEdgeAcceptable)
        color = Qt::red;

    if (isLastEdge && !m_isPolygonAcceptable)
        color = Qt::red;

    pattern.setColor(color);

    return pattern;
}

void EditingPolygonRenderingStrategy::setPendingVertex(const std::experimental::optional<std::size_t>& pendingVertex)
{
    m_pendingVertex = pendingVertex;
}

void EditingPolygonRenderingStrategy::polygonCnahged(const bool isAcceptable, const bool isPendingEdgeAcceptable)
{
    m_isPendingEdgeAcceptable = isPendingEdgeAcceptable;
    m_isPolygonAcceptable     = isAcceptable;
}


