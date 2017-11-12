#pragma once

#include "polygon.h"
#include "rendering_strategy.h"

#include <memory>

class QPainter;

class Renderer
{
public:
    using Ptr = std::unique_ptr<Renderer>;

public:
    Renderer() = default;
    virtual ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator = (const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator = (Renderer&&) = delete;

public:
    virtual void draw(QPainter& painter) const = 0;
};

class PolygonRenderer final: public Renderer
{
public:
    PolygonRenderer(const Polygon& polygon, IPolygonRenderingStrategy::Ptr strategy );

    virtual void draw(QPainter& painter) const override;

private:
    const Polygon&                 m_polygonToRender;
    IPolygonRenderingStrategy::Ptr m_renderingStrategy;
};


