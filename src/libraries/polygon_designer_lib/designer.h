#pragma once

#include "polygon.h"
#include "validator.h"

#include  <optional/optional.hpp>

#include <QPoint>
#include <QObject>


class Designer : public QObject
{
    Q_OBJECT;

public:
    Designer();

    void setPendingPointPosition(const QPoint& pos);
    void discardPendingPoint();
    void acceptPendingPoint();

    const Polygon& getDrawingFigure() const;

signals:
    void figureAcceptable(const bool isAcceptable) const;
    void pendingPointPositionAcceptable(const bool isAcceptable) const;

private:
    void validateFigure() const;

private:
    std::experimental::optional<std::size_t> m_pendingVertexIndex;

    Polygon m_polygon;
    PolygonValidator::Ptr m_validator;
};
