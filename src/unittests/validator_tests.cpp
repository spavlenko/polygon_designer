#include "polygon_designer_lib/validator.h"

#include <gtest/gtest.h>

TEST(ValidatorTests, FigureValidityTests)
{
    const auto validator = std::make_unique<PolygonValidator>();

    const Polygon emptyPolygon({});

    ASSERT_FALSE(validator->isValid(emptyPolygon));

    const Polygon triangle({{0, 0}, {1, 1}, {2, 2}} );
    ASSERT_TRUE(validator->isValid(triangle));

    const Polygon selfIntersecting({{0, 0}, {0, 1}, {1, 0}, {1, 1}});
    
    ASSERT_FALSE(validator->isValid(selfIntersecting));
    
    ASSERT_TRUE(validator->isAllovedEdgePosition(selfIntersecting,  {0, 1}));
    ASSERT_TRUE(validator->isAllovedEdgePosition(selfIntersecting,  {2, 3}));
    ASSERT_FALSE(validator->isAllovedEdgePosition(selfIntersecting, {1, 2}));
    ASSERT_FALSE(validator->isAllovedEdgePosition(selfIntersecting, {3, 0}));
}