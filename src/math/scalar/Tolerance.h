#pragma once

#include "Constants.h"

namespace Tolerance {
    bool approximatelyEqual(
        double a,
        double b,
        double absoluteTolerance = constants::EPSILON,
        double relativeTolerance = constants::EPSILON);
}