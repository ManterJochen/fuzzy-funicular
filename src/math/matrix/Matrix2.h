#pragma once

#include <initializer_list>

#include "MatrixN.h"
#include "../vector/Vector2.h"

class Matrix2 : public MatrixN {
public:
    Matrix2();
    Matrix2(std::initializer_list<std::initializer_list<double>> values);
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