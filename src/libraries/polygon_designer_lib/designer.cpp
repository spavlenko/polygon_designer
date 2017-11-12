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

    try
    {
        m_pendingVertexIndex.reset();
        m_polygon.popVertex();

        emit pendingPointIndexChanged(m_pendingVertexIndex);
    }
    catch(const Error::Base& )
    {
        qDebug() << "Unable to discard pending vertex. Error: polygon is empty." ;
    }
}

void Designer::acceptPendingPoint()
{
    assert(m_pendingVertexIndex.has_value());
    m_pendingVertexIndex.reset();

    emit pendingPointIndexChanged(m_pendingVertexIndex);
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

    //todo: magic numbers
    const Edge edge1 = { 0, *m_pendingVertexIndex };
    const Edge edge2 = { *m_pendingVertexIndex - 1, *m_pendingVertexIndex };

    const auto isAllowed = m_validator->isAllovedEdgePosition(m_polygon, edge1)
        && m_validator->isAllovedEdgePosition(m_polygon, edge2);

    emit pendingPointPositionAcceptable(isAllowed);
}

