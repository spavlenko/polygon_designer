#include "polygon_designer_lib/polygon.cpp"

#include <gtest/gtest.h>
#include <limits>
#include "polygon_designer_lib/utils.h"


TEST(PolygonTest, AccessToVertexTest)
{
	Vertex v({ 1, 1 });
	Polygon p( {{0, 0}, v, {2, 2}} );

	EXPECT_THROW(p.getVertex(p.getVertextCount()), Error::InvalidVertexIndex);

	EXPECT_EQ(v, p.getVertex(1));
}

TEST(PolygonUtils, ConvexityCheckTest)
{
	const Polygon p0({ {0, 0}, {0, 1}, {1, 1}, {1, 0} });
	
	ASSERT_TRUE(isConvex(p0));

	const Polygon p1({ {0, 0}, {0, 2}, {3, 7}, {4, 4}, {2, 2}, {2, 4} });
	ASSERT_FALSE(isConvex(p1));

	const Polygon p2({ {0, 0}, {1, 1}, {0, 1}, {1, 0} });
	ASSERT_FALSE(isConvex(p2));

	const Polygon p3({ {1, 1}
		, { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() }
		, { std::numeric_limits<int>::max() / 2, std::numeric_limits<int>::max() / 2 }
		, {10, 10} });
	
	ASSERT_TRUE(isConvex(p3));
}

TEST(PolygonUtils, AreaCheckTest)
{
	const Polygon p0({ {0, 0}, {0, 2}, {2, 2}, {2, 0} });
	
	const auto val = calculateArea(p0);
	
	ASSERT_EQ(4.0, val);
}

TEST(Utils, LineIntersectionCheckTest)
{	
	ASSERT_FALSE(Utils::doLinesIntersect({1, 1}, {10, 1}, {1, 2}, {10, 2}));
	ASSERT_TRUE(Utils::doLinesIntersect({10, 0}, {0, 10}, {0, 0}, {10, 10}));	
}

