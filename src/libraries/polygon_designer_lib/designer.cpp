#include "designer.h"
#include "defines.h"

#include <QDebug>


Designer::Designer()
    : m_validator( std::make_unique<PolygonValidator>())
{
    QObject::connect(&m_polygon, &Polygon::changed, this, &Designer::validateFigure);
}

void Designer::setPendingPointPosition(const QPoint& pos)
{
    if (!m_pendingVertexIndex.has_value())
    {
        m_pendingVertexIndex = m_polygon.getVertexCount();
        m_polygon.pushVertex(pos);

        emit pendingPointIndexChanged(m_pendingVertexIndex);
    }
    else
    {
        m_polygon.setVertexPosition(*m_pendingVertexIndex, pos);
    }
}

void Designer::discardPendingPoint()
{
    if (!m_pendingVertexIndex.has_value())
        return;

    m_pendingVertexIndex.reset();
    m_polygon.popVertex();

    emit pendingPointIndexChanged(m_pendingVertexIndex);
}

void Designer::acceptPendingPoint()
{
    if(!m_isPendingPointAcceptable)
        return;

    PD_ASSERT(m_pendingVertexIndex.has_value());
    m_pendingVertexIndex.reset();

    emit pendingPointIndexChanged(m_pendingVertexIndex);
}

const Polygon& Designer::getDrawingFigure() const
{
    return m_polygon;
}

void Designer::validateFigure()
{
    const auto figureValidity = m_validator->isValid(m_polygon);

    if(!m_pendingVertexIndex.has_value() || *m_pendingVertexIndex < 3)
    {
        emit figureChanged(figureValidity, true);
        return;
    }

    const Edge pendignEdge = { *m_pendingVertexIndex - 1, *m_pendingVertexIndex };
    m_isPendingPointAcceptable = m_validator->isAllovedEdgePosition(m_polygon, pendignEdge);

    emit figureChanged(figureValidity, m_isPendingPointAcceptable);
}

