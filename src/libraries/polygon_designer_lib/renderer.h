#pragma once

#include "polygon.h"

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
	explicit PolygonRenderer(const Polygon& polygon);

	void setPolygon(const Polygon& polygon);

	virtual void draw(QPainter& painter) const override;

private:
	Polygon m_polygonToRender;
};






