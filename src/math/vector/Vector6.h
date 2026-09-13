#pragma once
#include "VectorN.h"

class Vector6 : public VectorN {
    public:
        Vector6(double x1, double x2, double x3, double x4, double x5, double x6);

        double x1() const;
        double x2() const;
        double x3() const;
        double x4() const;
        double x5() const;
        double x6() const;

        double dot(const Vector6& other) const;

        Vector6 operator+(const Vector6& other) const;
        Vector6 operator-(const Vector6& other) const;
        Vector6 operator*(double scalar) const;
        Vector6 operator/(double scalar) const;
};