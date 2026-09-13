#pragma once

#include "Scalar.h"

namespace constants{
    constexpr Scalar PI = 3.14159265358979323846;
    constexpr Scalar TWO_PI = 2.0 * PI;
    constexpr Scalar HALF_PI = 0.5 * PI;
    constexpr Scalar DEGREES_TO_RADIANS = PI / 180.0;
    constexpr Scalar RADIANS_TO_DEGREES = 180.0 / PI;

    constexpr Scalar GRAVITY = 9.80665;
    constexpr Scalar EPSILON = 1e-10;
}