#pragma once

#include "Constants.h"

namespace Tolerance {
    bool approximatelyEqual(
        double a,
        double b,
        double absoluteTolerance = constants::EPSILON,
        double relativeTolerance = constants::EPSILON);

    bool approximatelyZero(
        double value,
        double absoluteTolerance = constants::EPSILON);

    bool isFinite(double value);
    bool isNaN(double value);
}