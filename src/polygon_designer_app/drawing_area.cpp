#include "drawing_area.h"

#include <QMouseEvent>

namespace
{
	namespace Const
	{
		const auto backgroundColor = Qt::white;
	}
}

DrawingArea::DrawingArea(QWidget* parent)
	: Parent(parent)
{
	QPalette pal(palette());

	pal.setColor(QPalette::Background, Const::backgroundColor);

	setAutoFillBackground(true);
	setPalette(pal);
}

void DrawingArea::setRenderer(Renderer::Ptr renderer)
{
	m_renderer = std::move(renderer);
}

void DrawingArea::mouseMoveEvent(QMouseEvent* event)
{
	emit mouseMoved(event->pos());

	Parent::mouseMoveEvent(event);
}

void DrawingArea::mousePressEvent(QMouseEvent* event)
{
	emit mousePressed(event->pos());

	Parent::mousePressEvent(event);
} 

void DrawingArea::leaveEvent(QEvent* event)
{
	emit mouseLeftArea();

	Parent::leaveEvent(event);
}

void DrawingArea::paintEvent(QPaintEvent* event)
{
	if(!m_renderer)
		return;

	QPainter painter(this);

	m_renderer->draw(painter);
}
