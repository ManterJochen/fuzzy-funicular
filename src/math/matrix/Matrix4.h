#pragma once

#include <initializer_list>

#include "MatrixN.h"
#include "Matrix3.h"
#include "../vector/Vector4.h"
#include "../vector/Vector3.h"
#include "../scalar/Angle.h"

class Matrix4 : public MatrixN {
public:
    Matrix4();
    Matrix4(std::initializer_list<std::initializer_list<double>> values);
    explicit Matrix4(const MatrixN& matrix);

    // Scalar operations with Matrix4 result
    Matrix4 operator*(double scalar) const;
    Matrix4 operator/(double scalar) const;

    // Matrix operations with Matrix4 result
    Matrix4 operator+(const Matrix4& other) const;
    Matrix4 operator-(const Matrix4& other) const;
    Matrix4 operator*(const Matrix4& other) const;

    Vector4 operator*(const Vector4& vector) const;

    // Matrix operations
    Matrix4 inverse() const;
    Matrix4 transpose() const;

    // Special Matrix4 operations (e.g., rotation matrices)
    // Translation matrix
    static Matrix4 translation(double x, double y, double z);
    static Matrix4 translation(const Vector3& translation);

    // rotation matrices
    static Matrix4 rotation(const Matrix3& rotation);
    static Matrix4 rotationX(const Angle& angle);
    static Matrix4 rotationY(const Angle& angle);
    static Matrix4 rotationZ(const Angle& angle);

    // transformation
    static Matrix4 transform(
        const Matrix3& rotation,
        const Vector3& translation
    );

    Matrix3 rotation() const;
    Vector3 translation() const;

    Vector3 transform(const Vector3& point) const;

    bool isTransformationMatrix() const;


    // Make other MatrixN overloads visible
    using MatrixN::operator+;
    using MatrixN::operator-;
    using MatrixN::operator*;
    using MatrixN::operator/;
};
