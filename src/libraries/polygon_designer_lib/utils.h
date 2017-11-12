#pragma once

#include <QPoint>

class Polygon;

namespace Utils
{
    bool   doLinesIntersect(const QPoint& p1, const QPoint& q1, const QPoint& p2, const QPoint& q2);
    double calculateArea(const Polygon& polygon);
    bool   isConvex(const Polygon& polygon);
}
