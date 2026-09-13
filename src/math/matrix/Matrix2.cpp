#include "Matrix2.h"

#include <cmath>
#include <stdexcept>

//====================================
// Constructors
//====================================

Matrix2::Matrix2() : MatrixN(2, 2) {}

Matrix2::Matrix2(const MatrixN& matrix) : MatrixN(matrix) {
    if (rows() != 2 || cols() != 2) {
        throw std::invalid_argument("Matrix must be 2x2");
    }
}

Matrix2 Matrix2::operator*(double scalar) const {
    return Matrix2(MatrixN::operator*(scalar));
}

Matrix2 Matrix2::operator/(double scalar) const {
    return Matrix2(MatrixN::operator/(scalar));
}   

Matrix2 Matrix2::operator+(const Matrix2& other) const {
    return Matrix2(MatrixN::operator+(other));
}

Matrix2 Matrix2::operator-(const Matrix2& other) const {
    return Matrix2(MatrixN::operator-(other));
}

Matrix2 Matrix2::operator*(const Matrix2& other) const {
    return Matrix2(MatrixN::operator*(other));
}

Vector2 Matrix2::operator*(const Vector2& vector) const {
    const std::vector<double> result = MatrixN::operator*(
        std::vector<double>{vector.x(), vector.y()});
    return Vector2(result[0], result[1]);
}

Matrix2 Matrix2::transpose() const {
    return Matrix2(MatrixN::transpose());
}

Matrix2 Matrix2::inverse() const {
    return Matrix2(MatrixN::inverse());
}