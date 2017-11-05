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
	emit mouseLeft();

	Parent::leaveEvent(event);
}
