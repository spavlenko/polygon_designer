#include <gtest/gtest.h>
#include "polygon_designer_lib/polygon.cpp"

TEST(PolygonUtils, ConvexityCheckTest)
{
	Polygon p({ {0, 0}, {0, 1}, {1, 1}, {1, 0} });
	
	ASSERT_TRUE(isConvex(p));
}