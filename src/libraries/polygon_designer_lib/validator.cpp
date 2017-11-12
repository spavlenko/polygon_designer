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
    const auto edges = polygon.getEdgesList();

    for(const auto edgeToCheck : edges)
    {
        if (edgeToCheck == edge)
            continue;

        if (polygon.doEdgesIntersects(edgeToCheck, edge))
            return true;
    }

    return false;
}
