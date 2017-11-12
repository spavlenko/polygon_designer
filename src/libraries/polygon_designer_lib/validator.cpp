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
    if(polygon.getVertexCount() < Const::minVertexConunt)
        return false;

    const auto edges = polygon.getEdgesList();

    for(const auto& edge : edges)
    {
        for (const auto edgeToCheck : edges)
        {
            if (polygon.doEdgesIntersects(edgeToCheck, edge))
                return false;
        }
    }

    return true;
}


bool PolygonValidator::isAllovedEdgePosition(const Polygon& polygon, const Edge& edge) const
{
    const auto edges = polygon.getEdgesList();

    for(const auto edgeToCheck : edges)
    {
        if (polygon.doEdgesIntersects(edgeToCheck, edge))
            return false;
    }

    return true;
}
