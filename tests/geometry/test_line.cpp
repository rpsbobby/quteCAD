//
// Created by robert on 15/09/2025.
//
#include <catch2/catch_test_macros.hpp>

#include "geometry/LineEntity.h"
#include "utils/common.h"


TEST_CASE("ShouldReturnLengthOfTheLine")
{
    // given
    constexpr QPointF a {0.0,0.0};
    constexpr QPointF b {3.0,4.0};
    const LineEntity line(a,b);
    // when
    const double length = line.length();
    // then
    REQUIRE(length == 5.0);
}


