#pragma once

#include <initializer_list>

#include "MatrixN.h"
#include "../vector/Vector3.h"
#include "../scalar/Angle.h"

class Matrix3 : public MatrixN {
public:
    Matrix3();
    Matrix3(std::initializer_list<std::initializer_list<double>> values);
    explicit Matrix3(const MatrixN& matrix);

    // Scalar operations with Matrix3 result
    Matrix3 operator*(double scalar) const;
    Matrix3 operator/(double scalar) const;

    // Matrix operations with Matrix3 result
    Matrix3 operator+(const Matrix3& other) const;
    Matrix3 operator-(const Matrix3& other) const;
    Matrix3 operator*(const Matrix3& other) const;

    Vector3 operator*(const Vector3& vector) const;

    // Matrix operations with Matrix3 result
    Matrix3 inverse() const;
    Matrix3 transpose() const;

    // Special Matrix3 operations (e.g., rotation matrices)
    static Matrix3 rotationX(const Angle& angle);
    static Matrix3 rotationY(const Angle& angle);
    static Matrix3 rotationZ(const Angle& angle);

    static Matrix3 fromEulerXYZ(
        const Angle& X,
        const Angle& Y,
        const Angle& Z
    );

    // Bool operations with Matrix3 result
    bool isRotationMatrix() const;

    // Make other MatrixN overloads visible
    using MatrixN::operator+;
    using MatrixN::operator-;
    using MatrixN::operator*;
    using MatrixN::operator/;
};