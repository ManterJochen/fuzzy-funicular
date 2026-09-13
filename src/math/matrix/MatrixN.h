#pragma once

#include <vector>

#include "../vector/VectorN.h"

class MatrixN
{
protected:
    std::vector<std::vector<double>> data_;

public:
    MatrixN(int rows, int cols);

    int rows() const;
    int cols() const;

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;

    // Matrix with Matrix operations
    MatrixN operator+(const MatrixN& other) const;
    MatrixN operator-(const MatrixN& other) const;
    MatrixN operator*(const MatrixN& other) const;

    // Matrix * Vector
    std::vector<double> operator*(
        const std::vector<double>& vec) const;
    VectorN operator*(const VectorN& vector) const;

    // Matrix special operations
    double determinant() const;
    MatrixN transpose() const;
    MatrixN inverse() const;
    double norm() const;

    // Matrix with Scalar operations
    MatrixN operator*(double scalar) const;
    MatrixN operator/(double scalar) const;

    // Factory functions
    static MatrixN identity(int size);
    static MatrixN zero(int rows, int cols);

    // Properties
    bool isSquare() const;
    bool isIdentity() const;
    bool isSymmetric() const;
    bool isInvertible() const;
    bool isFinite() const;
};