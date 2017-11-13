#include "polygon_designer_lib/polygon.h"

#include <gtest/gtest.h>

TEST(PolygonTest, AccessToVertexTest)
{
    Vertex v({1, 1});
    Polygon p({{0, 0}, v,{2, 2}});

    EXPECT_THROW(p.getVertex(p.getVertexCount()), Error::InvalidVertexIndex);

    EXPECT_EQ(v, p.getVertex(1));
}

TEST(PolygonTest, AddRemoveVertextTest)
{
    Polygon p;
    EXPECT_THROW(p.popVertex(), Error::InvalidVertexIndex);

    Vertex v({ 1, 1 });
    p.pushVertex(v);
    EXPECT_EQ(1, p.getVertexCount());

    EXPECT_EQ(v, p.getVertex(p.getVertexCount() - 1));

    p.popVertex();
    EXPECT_EQ(0, p.getVertexCount());
}

TEST(PolygonTest, EdgesListTest)
{
    const Vertex v0 = {0, 0}, v1 = {0, 1}, v2 = {1, 1};
    const Polygon p0({v0, v1, v2});

    const Edge e0 = {0, 1}, e1 = {1, 2}, e2 = {2, 0};

    const auto edgesP0 = p0.getEdgesList();

    EXPECT_EQ(3, edgesP0.size());

    ASSERT_EQ(e0, edgesP0[0]);
    ASSERT_EQ(e1, edgesP0[1]);
    ASSERT_EQ(e2, edgesP0[2]);

    const Polygon p1({ v0, v1 });
    const auto edgesP1 = p1.getEdgesList();

    EXPECT_EQ(1, edgesP1.size());
    ASSERT_EQ(e0, edgesP1.front());
}
