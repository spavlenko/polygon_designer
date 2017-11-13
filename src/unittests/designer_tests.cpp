#include "polygon_designer_lib/validator.h"
#include "polygon_designer_lib/designer.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


namespace Mocs
{
    class PolygonValidatorMock final: public IPolygonValidator
    {
    public:
        MOCK_CONST_METHOD1(isValid, bool(const Polygon&));
        MOCK_CONST_METHOD2(isAllovedEdgePosition, bool(const Polygon&, const Edge&));
    };
}

TEST(Designer, HappyFlowTest)
{
    auto validator = std::make_unique<Mocs::PolygonValidatorMock>();
    
    EXPECT_CALL(*validator, isValid(testing::_)).Times(5).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*validator, isAllovedEdgePosition(testing::_, testing::_)).Times(1).WillRepeatedly(testing::Return(true));

    Designer d(std::move(validator));

    const Vertex firstPoint = {0, 0};
    d.setPendingPointPosition(firstPoint);
    d.acceptPendingPoint();
    EXPECT_EQ(1, d.getDrawingFigure().getVertexCount());
    ASSERT_EQ(firstPoint, d.getDrawingFigure().getVertex(Polygon::firstPointIndex));

    d.setPendingPointPosition({1, 1});
    d.acceptPendingPoint();

    d.setPendingPointPosition({0, 2});
    d.acceptPendingPoint();
    EXPECT_EQ(3, d.getDrawingFigure().getVertexCount());
    
    d.setPendingPointPosition({ 0, 1 });
    EXPECT_EQ(4, d.getDrawingFigure().getVertexCount());
    
    d.discardPendingPoint();
    EXPECT_EQ(3, d.getDrawingFigure().getVertexCount());

    d.discardPendingPoint();
    EXPECT_EQ(3, d.getDrawingFigure().getVertexCount());
}
