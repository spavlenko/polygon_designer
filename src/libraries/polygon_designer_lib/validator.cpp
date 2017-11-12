#include "validator.h"

bool PolygonValidator::isValid(const Polygon& polygon) const
{
    if(polygon.getVertexCount() < Polygon::minPointsRequired)
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
