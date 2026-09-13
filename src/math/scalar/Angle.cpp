#include <cmath>
#include "Angle.h"
#include "Constants.h"

// Implementation of the Angle class
Angle::Angle(double radians)
    :radians_(radians)
{
}


// ================================
// Conversion functions
// ================================

Angle Angle::fromDegrees(double degrees)
{
    return Angle(degrees * constants::DEGREES_TO_RADIANS);
}

Angle Angle::fromRadians(double radians)
{
    return Angle(radians);
}

// Returns the angle in radians
double Angle::radians() const
{
    return radians_;
}

// Returns the angle in degrees
double Angle::degrees() const
{
    return radians_ * constants::RADIANS_TO_DEGREES;
}

// sin of the angle
double Angle::sin() const
{
    return std::sin(radians_);
}

// cos of the angle
double Angle::cos() const
{
    return std::cos(radians_);
}

// tan of the angle
double Angle::tan() const
{
    return std::tan(radians_);
}