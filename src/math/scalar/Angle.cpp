#include <cmath>
#include "Angle.h"

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
    return Angle(degrees * 3.141592653589793 / 180.0);
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
    return radians_ * 180.0 / 3.141592653589793;
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