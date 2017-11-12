#pragma once

#include "polygon.h"

#include <QObject>
#include <QPen>
#include <QBrush>

#include <optional/optional.hpp>
#include <memory>

class IPolygonRenderingStrategy: public QObject
{
public:
    using Ptr = std::unique_ptr<IPolygonRenderingStrategy>;

public:
    IPolygonRenderingStrategy() = default;
    virtual ~IPolygonRenderingStrategy() = default;

    IPolygonRenderingStrategy(const IPolygonRenderingStrategy&) = delete;
    IPolygonRenderingStrategy& operator = (const IPolygonRenderingStrategy&) = delete;
    IPolygonRenderingStrategy(IPolygonRenderingStrategy&&) = delete;
    IPolygonRenderingStrategy& operator = (IPolygonRenderingStrategy&&) = delete;

    virtual QBrush getFillBrush() const = 0;
    virtual QPen   getEdgePen(const Edge& edge, const Polygon& polygon) const = 0;
};

class PolygonDefaultRenderingStrategy final: public IPolygonRenderingStrategy
{
public:
    virtual QBrush getFillBrush() const override;;
    virtual QPen getEdgePen(const Edge& edge, const Polygon& polygon) const override;
};

class EditingPolygonRenderingStrategy final: public IPolygonRenderingStrategy
{
public:
    virtual QBrush getFillBrush() const override;
    virtual QPen   getEdgePen(const Edge& edge, const Polygon& polygon) const override;

    void setPendingVertex(const std::experimental::optional<std::size_t>& pendingVertex);
    void polygonCnahged(const bool isAcceptable, const bool isPendingEdgeAcceptable);

public:
    std::experimental::optional<std::size_t> m_pendingVertex;
    bool m_isPolygonAcceptable     = false;
    bool m_isPendingEdgeAcceptable = false;
};