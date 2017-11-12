#include "utils.h"
#include "polygon.h"

#include <algorithm>
#include <cassert>

namespace Utils
{
    namespace
    {
        long long crossProduction(const QPoint& lh, const QPoint& rh)
        {
            return static_cast<long long>(lh.x()) * rh.y() - static_cast<long long>(lh.y()) * rh.x();
        }

        bool isPointOnSegment(const QPoint& start, const QPoint& end, const QPoint& point)
        {
            if (end.x() <= std::max(start.x(), point.x()) && end.x() >= std::min(start.x(), point.x()) &&
                end.y() <= std::max(start.y(), point.y()) && end.y() >= std::min(start.y(), point.y()))
                return true;

            return false;
        }

        enum class Orientation
        {
            Colinear,
            Clockwise,
            Counterclockwise
        };

        Orientation orientation(const QPoint& p, const QPoint& q, const QPoint& r)
        {
            const auto val = (q.y() - p.y()) * (r.x() - q.x()) -
                (q.x() - p.x()) * (r.y() - q.y());

            if (0 == val)
                return Orientation::Colinear;

            return (val > 0) ? Orientation::Clockwise : Orientation::Counterclockwise;
        }
    }

    bool doLinesIntersect(const QPoint& p1, const QPoint& q1, const QPoint& p2, const QPoint& q2)
    {
        const auto o1 = orientation(p1, q1, p2);
        const auto o2 = orientation(p1, q1, q2);
        const auto o3 = orientation(p2, q2, p1);
        const auto o4 = orientation(p2, q2, q1);

        // General case
        if (o1 != o2 && o3 != o4)
            return true;

        if (o1 == Orientation::Colinear && isPointOnSegment(p1, p2, q1))
            return true;

        if (o2 == Orientation::Colinear && isPointOnSegment(p1, q2, q1))
            return true;

        if (o3 == Orientation::Colinear && isPointOnSegment(p2, p1, q2))
            return true;

        if (o4 == Orientation::Colinear && isPointOnSegment(p2, q1, q2))
            return true;

        return false;
    }


    double calculateArea(const Polygon& polygon)
    {
        const auto vertexesCount = polygon.getVertexCount();

        double area = .0;

        if (vertexesCount < Polygon::minPointsRequired)
            return area;

        size_t i = vertexesCount - 1;

        for (std::size_t j = 0; j < vertexesCount; ++j)
        {
            const auto pi = polygon.getVertex(i);
            const auto pj = polygon.getVertex(j);

            area += static_cast<double>((static_cast<long long>(pi.x()) + pj.x())
                * (static_cast<long long>(pi.y()) - pj.y()));

            i = j;
        }

        return std::abs(area / 2);
    }

    bool isConvex(const Polygon& polygon)
    {
        const auto vertexesCount = polygon.getVertexCount();

        if(vertexesCount < Polygon::minPointsRequired)
            return false;

        bool sign = false;

        for (std::size_t i = 0; i < vertexesCount; ++i)
        {
            const auto& v1Start = polygon.getVertex((i + 2) % vertexesCount);
            const auto& v1End = polygon.getVertex((i + 1) % vertexesCount);

            const QPoint v1 = v1End - v1Start;

            const auto& v2Start = polygon.getVertex((i + 1) % vertexesCount);
            const auto& v2End = polygon.getVertex((i + 0) % vertexesCount);

            const QPoint v2 = v2End - v2Start;

            const auto product = crossProduction(v1, v2);

            if (0 == i)
                sign = product > 0;
            else if (sign != product > 0)
                return false;
        }

        return true;
    }

}
