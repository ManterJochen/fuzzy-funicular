#pragma once

#include "VectorN.h"
#include "../scalar/Angle.h"

class Vector3 : public VectorN {
    public:
        Vector3(double x, double y, double z);

        double x() const;
        double y() const;
        double z() const;

        double dot(const Vector3& other) const;
        Vector3 cross(const Vector3& other) const;
        Angle angle(const Vector3& other) const;

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(double scalar) const;
        Vector3 operator/(double scalar) const;


        Vector3 projection(const Vector3& other) const;
        Vector3 rejection(const Vector3& other) const;
        Vector3 reflection(const Vector3& normal) const;
};
