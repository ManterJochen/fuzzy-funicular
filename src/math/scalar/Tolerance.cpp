#include "Tolerance.h"
#include "Constants.h"

#include <algorithm>
#include <cmath>

namespace Tolerance {
    bool approximatelyEqual(
        double a,
        double b,
        double absoluteTolerance,
        double relativeTolerance)
    {
        double difference = std::abs(a - b);

        if (difference <= absoluteTolerance) {
            return true;
        }
        double largest = std::max(std::abs(a), std::abs(b));

        return difference <= largest * relativeTolerance;
    }
}