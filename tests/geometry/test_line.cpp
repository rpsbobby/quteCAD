//
// Created by robert on 15/09/2025.
//
#include <catch2/catch_test_macros.hpp>

#include "geometry/Line.h"
#include "utils/common.h"

TEST_CASE("Example")
{
    // given
    Point a = {0.0, 0.0};
    Point b = {1.0, 1.0};
    // when
    auto line = Line(a, b);
}