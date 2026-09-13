#pragma once

#include "MatrixN.h"
#include "../vector/Vector2.h"

class Matrix2 : public MatrixN {
public:
    Matrix2();
    explicit Matrix2(const MatrixN& matrix);

    // Scalar operations with Matrix2 result
    Matrix2 operator*(double scalar) const;
    Matrix2 operator/(double scalar) const;

    // Matrix operations with Matrix2 result
    Matrix2 operator+(const Matrix2& other) const;
    Matrix2 operator-(const Matrix2& other) const;
    Matrix2 operator*(const Matrix2& other) const;

    Vector2 operator*(const Vector2& vector) const;

    // Matrix operations with Matrix2 result
    Matrix2 inverse() const;
    Matrix2 transpose() const;

    // Make other MatrixN overloads visible
    using MatrixN::operator+;
    using MatrixN::operator-;
    using MatrixN::operator*;
    using MatrixN::operator/;
};