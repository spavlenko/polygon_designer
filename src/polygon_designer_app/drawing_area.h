#pragma once
#include <QGraphicsView>
#include <memory>
#include "polygon_designer_lib/renderer.h"

class DrawingArea: public QWidget
{
    using Parent = QWidget;

    Q_OBJECT;

public:
    explicit DrawingArea(QWidget *parent);

    void setRenderer(Renderer::Ptr renderer);

signals:
    void mouseMoved(const QPoint& pos) const;
    void mousePressed(const QPoint& pos) const;
    void mouseLeftArea() const;

protected:
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;

    virtual void paintEvent(QPaintEvent *event) override;

private:
    Renderer::Ptr m_renderer;
};
