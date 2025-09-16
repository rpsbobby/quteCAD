//
// Created by robert on 16/09/2025.
//

#include <QPointF>

#include "catch2/catch_test_macros.hpp"
#include "utils/common.h"

TEST_CASE("Should return euclidian distance")
{
    // given
    constexpr QPointF a{0.0, 0.0};
    constexpr QPointF b{3.0, 4.0};
    // when
    const double distance = getEuclideanDistance2d(a, b);
    // then
    REQUIRE(distance == 5.0);
}
