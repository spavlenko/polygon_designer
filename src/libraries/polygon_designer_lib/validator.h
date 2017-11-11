#pragma once
#include "polygon.h"

#include <memory>

class PolygonValidator
{
public:
    using Ptr = std::unique_ptr<PolygonValidator>;

public:
    bool isValid(const Polygon& polygon) const;
    bool isAllovedEdgePosition(const Polygon& polygon, const Edge& edge) const;
};

