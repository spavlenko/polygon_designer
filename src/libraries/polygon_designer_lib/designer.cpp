#include  "designer.h"

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
    }
    else
    {
        m_polygon.setVertexPosition(*m_pendingVertexIndex, pos);
    }

    validateFigure();
}

void Designer::discardPendingPoint()
{
    if (!m_pendingVertexIndex.has_value())
        return;

    try
    {
        m_pendingVertexIndex.reset();
        m_polygon.popVertex();
    }
    catch(const Error::Base& err)
    {
        Q_UNUSED(err);
        qDebug() << "Unable to discard pending vertex. Inconsistent data.";
    }

    validateFigure();
}

void Designer::acceptPendingPoint()
{
    assert(m_pendingVertexIndex.has_value());
    m_pendingVertexIndex.reset();
}

const Polygon& Designer::getDrawingFigure() const
{
    return m_polygon;
}

void Designer::validateFigure() const
{
    emit figureAcceptable(m_validator->isValid(m_polygon));

    if(!m_pendingVertexIndex.has_value() || *m_pendingVertexIndex < 3)
        return;

    const auto& pendingVertex = m_polygon.getVertex(*m_pendingVertexIndex);

    const Edge edge1 = { m_polygon.getVertex(0), pendingVertex };
    const Edge edge2 = { m_polygon.getVertex(*m_pendingVertexIndex - 1), pendingVertex };

    const auto isAllowed = m_validator->isAllovedEdgePosition(m_polygon, edge1)
        && m_validator->isAllovedEdgePosition(m_polygon, edge2);

    emit pendingPointPositionAcceptable(isAllowed);
}

