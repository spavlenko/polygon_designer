#pragma once
#include <QGraphicsView>

class DrawingArea: public QWidget
{
	using Parent = QWidget;

	Q_OBJECT;

public: 
	explicit DrawingArea(QWidget *parent);
	
signals:
	void mouseMoved(const QPoint& pos) const;
	void mousePressed(const QPoint& pos) const;
	void mouseLeft() const;

protected:
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;


};