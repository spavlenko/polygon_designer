#include <utils.h>
#include <algorithm>

namespace Utils
{
    namespace
    {
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
        // Find the four orientations needed for general and
        // special cases
        const auto o1 = orientation(p1, q1, p2);
        const auto o2 = orientation(p1, q1, q2);
        const auto o3 = orientation(p2, q2, p1);
        const auto o4 = orientation(p2, q2, q1);

        // General case
        if (o1 != o2 && o3 != o4)
            return true;

        // Special Cases
        // p1, q1 and p2 are colinear and p2 lies on segment p1q1
        if (o1 == Orientation::Colinear && isPointOnSegment(p1, p2, q1))
            return true;

        // p1, q1 and p2 are colinear and q2 lies on segment p1q1
        if (o2 == Orientation::Colinear && isPointOnSegment(p1, q2, q1))
            return true;

        // p2, q2 and p1 are colinear and p1 lies on segment p2q2
        if (o3 == Orientation::Colinear && isPointOnSegment(p2, p1, q2))
            return true;

        // p2, q2 and q1 are colinear and q1 lies on segment p2q2
        if (o4 == Orientation::Colinear && isPointOnSegment(p2, q1, q2))
            return true;

        return false; // Doesn't fall in any of the above cases
    }
}
