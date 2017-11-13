#pragma once
#include "polygon.h"

#include <memory>

class IPolygonValidator
{
public:
    using Ptr = std::unique_ptr<IPolygonValidator>;

public:
    IPolygonValidator() = default;
    virtual ~IPolygonValidator() = default;
    virtual bool isValid(const Polygon& polygon) const = 0;
    virtual bool isAllovedEdgePosition(const Polygon& polygon, const Edge& edge) const = 0;
};

class PolygonValidator final: public IPolygonValidator
{
public:
    virtual bool isValid(const Polygon& polygon) const override;
    virtual bool isAllovedEdgePosition(const Polygon& polygon, const Edge& edge) const override;
};

