#include "polygon.h"
#include "utils.h"

#include <cassert>


namespace
{
    long long crossProduction(const QPoint& lh, const QPoint& rh)
    {
        return static_cast<long long>(lh.x()) * rh.y() - static_cast<long long>(lh.y()) * rh.x();
    }
}
namespace Error
{
    Base::Base(char const* const message)
        : std::exception(message)
    {
    }

    InvalidVertexIndex::InvalidVertexIndex()
        : Base("invalid vertex index")
    {
    }
}

Polygon::Polygon(const VertexList& vertexes)
    : m_vertexes(vertexes)
{
}

Polygon::Polygon(const Polygon& p)
    : m_vertexes(p.m_vertexes)
{
}

std::size_t Polygon::getVertexCount() const
{
    return m_vertexes.size();
}

const Vertex& Polygon::getVertex(const std::size_t id) const
{
    if (getVertexCount() <= id)
        throw Error::InvalidVertexIndex();

    return m_vertexes[id];
}

EdgesList Polygon::getEdgesList() const
{
    EdgesList res;

    const auto vertexCount = getVertexCount();

    if (vertexCount < 2)
        return res;

    res.push_back({ Polygon::firstPointIndex, Polygon::firstPointIndex  + 1});

    if(vertexCount >= Polygon::minPointsRequired)
    {
        for (size_t i = 1; i < vertexCount; ++i)
            res.push_back({i % vertexCount, (i + 1) % vertexCount });
    }

    return res;
}

void Polygon::setVertexPosition(const std::size_t id, const Vertex& newPosition)
{
    if (getVertexCount() <= id)
        throw Error::InvalidVertexIndex();

    m_vertexes[id] = newPosition;

    emit changed();
}

void Polygon::pushVertex(const Vertex& newVertex)
{
    m_vertexes.push_back(newVertex);

    emit changed();
}

void Polygon::popVertex()
{
    if(m_vertexes.empty())
        throw Error::InvalidVertexIndex();

    m_vertexes.erase(std::prev(m_vertexes.end()));

    emit changed();
}

bool Polygon::doEdgesIntersects(const Edge& rhs, const Edge& lhs) const
{
    if (rhs == lhs)
        return false;

    if (rhs.first == lhs.first || rhs.first == lhs.second
        || rhs.second == lhs.first || rhs.second == lhs.second)
        return false;

    const auto& rhsStart = getVertex(rhs.first);
    const auto& rhsEnd = getVertex(rhs.first);

    //todo: check
    return Utils::doLinesIntersect(getVertex(rhs.first), getVertex(rhs.second)
        , getVertex(lhs.first), getVertex(lhs.second));
}
