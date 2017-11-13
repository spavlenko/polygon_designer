#pragma once

#include "polygon.h"
#include "validator.h"

#include <optional/optional.hpp>

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
    void figureChanged(const bool isFigureAcceptable, const bool isPendingPointAcceptable) const;
    void pendingPointIndexChanged(const std::experimental::optional<std::size_t>& index) const;

private:
    void validateFigure();

private:
    std::experimental::optional<std::size_t> m_pendingVertexIndex;

    Polygon               m_polygon;
    PolygonValidator::Ptr m_validator;

    bool m_isPendingPointAcceptable = true;
};
