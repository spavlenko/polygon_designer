#include "validator.h"

namespace
{
    namespace Const
    {
        const auto minVertexConunt = 3;
    }
}

bool PolygonValidator::isValid(const Polygon& polygon) const
{
    return polygon.getVertexCount() >= Const::minVertexConunt;
}

bool PolygonValidator::isAllovedEdgePosition(const Polygon& polygon, const Edge& edge) const
{
    const auto vertexCount = polygon.getVertexCount();

    for (size_t i = 0; i < vertexCount; ++i)
    {
        const Edge edgeToCheck{ polygon.getVertex((i + 1) % vertexCount)
            , polygon.getVertex((i + 2) % vertexCount) };

        if(edgeToCheck == edge)
            continue;

        if (doEdgesIntersects(edgeToCheck, edge))
            return true;
    }

    return false;
}
