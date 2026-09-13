#pragma once

#include "VectorN.h"

class Vector2 : public VectorN {
    public:
        Vector2(double x, double y);

        double x() const;
        double y() const;

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(double scalar) const;
        Vector2 operator/(double scalar) const;

        double dot(const Vector2& other) const;
};