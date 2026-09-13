#pragma once

#include "VectorN.h"

class Vector4 : public VectorN {
    public:
        Vector4(double x, double y, double z, double w);

        double x() const;
        double y() const;
        double z() const;
        double w() const;

        double dot(const Vector4& other) const;

        Vector4 operator+(const Vector4& other) const;
        Vector4 operator-(const Vector4& other) const;
        Vector4 operator*(double scalar) const;
        Vector4 operator/(double scalar) const;
};