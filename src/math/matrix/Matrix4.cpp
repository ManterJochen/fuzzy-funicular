#include "Matrix4.h"


#include "../scalar/Tolerance.h"
#include "../scalar/Angle.h"

#include <cmath>
#include <stdexcept>

//====================================
// Constructors
//====================================
Matrix4::Matrix4()
    : MatrixN(4, 4)
{
}

Matrix4::Matrix4(
    std::initializer_list<std::initializer_list<double>> values)
    : MatrixN(4, 4)
{
    if (values.size() != 4) {
        throw std::invalid_argument("Matrix4 requires 4 rows");
    }

    int row = 0;
    for (const auto& valuesRow : values) {
        if (valuesRow.size() != 4) {
            throw std::invalid_argument("Matrix4 requires 4 columns");
        }

        int column = 0;
        for (double value : valuesRow) {
            data_[row][column] = value;
            ++column;
        }
        ++row;
    }
}

Matrix4::Matrix4(const MatrixN& matrix)
    : MatrixN(matrix)
{
    if (matrix.rows() != 4 || matrix.cols() != 4)
    {
        throw std::invalid_argument(
            "Matrix4 must be 4x4");
    }
}

Matrix4 Matrix4::operator*(double scalar) const {
    return Matrix4(MatrixN::operator*(scalar));
}
Matrix4 Matrix4::operator/(double scalar) const {
    return Matrix4(MatrixN::operator/(scalar));
}
Matrix4 Matrix4::operator+(const Matrix4& other) const {
    return Matrix4(MatrixN::operator+(other));
}
Matrix4 Matrix4::operator-(const Matrix4& other) const {
    return Matrix4(MatrixN::operator-(other));
}
Matrix4 Matrix4::operator*(const Matrix4& other) const {
    return Matrix4(MatrixN::operator*(other));
}

Vector4 Matrix4::operator*(const Vector4& vector) const {
    const std::vector<double> result = MatrixN::operator*(
        std::vector<double>{vector.x(), vector.y(), vector.z(), vector.w()});
    return Vector4(result[0], result[1], result[2], result[3]);
}

Matrix4 Matrix4::transpose() const {
    return Matrix4(MatrixN::transpose());
}
Matrix4 Matrix4::inverse() const {
    return Matrix4(MatrixN::inverse());
}

//====================================
// Matrix4 Operations (specials)
//====================================
// Translation
Matrix4 Matrix4::translation(double x, double y, double z) {
    return Matrix4({
        {1.0, 0.0, 0.0, x},
        {0.0, 1.0, 0.0, y},
        {0.0, 0.0, 1.0, z},
        {0.0, 0.0, 0.0, 1.0}
    });
}

Matrix4 Matrix4::translation(const Vector3& translation) {
    return Matrix4::translation(translation.x(), translation.y(), translation.z());
}

// Rotation
Matrix4 Matrix4::rotation(const Matrix3& rotation) {
    return Matrix4({
        {rotation(0, 0), rotation(0, 1), rotation(0, 2), 0.0},
        {rotation(1, 0), rotation(1, 1), rotation(1, 2), 0.0},
        {rotation(2, 0), rotation(2, 1), rotation(2, 2), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    });
}
Matrix4 Matrix4::rotationX(const Angle& angle){
    return Matrix4::rotation(Matrix3::rotationX(angle));
}
Matrix4 Matrix4::rotationY(const Angle& angle){
    return Matrix4::rotation(Matrix3::rotationY(angle));
}
Matrix4 Matrix4::rotationZ(const Angle& angle){
    return Matrix4::rotation(Matrix3::rotationZ(angle));
}

// Transformation
Matrix4 Matrix4::transform(const Matrix3& rotation, const Vector3& translation) {
    return Matrix4::translation(translation) * Matrix4::rotation(rotation);
}

// Helper functions
Matrix3 Matrix4::rotation() const {
    return Matrix3({
        {(*this)(0, 0), (*this)(0, 1), (*this)(0, 2)},
        {(*this)(1, 0), (*this)(1, 1), (*this)(1, 2)},
        {(*this)(2, 0), (*this)(2, 1), (*this)(2, 2)}
    });
}

Vector3 Matrix4::translation() const {
    return Vector3((*this)(0, 3), (*this)(1, 3), (*this)(2, 3));
}

Vector3 Matrix4::transform(const Vector3& point) const {
    Vector4 homogenous_point(point.x(), point.y(), point.z(), 1.0);
    Vector4 transformed_point = (*this) * homogenous_point;
    return Vector3(transformed_point.x(), transformed_point.y(), transformed_point.z());
}

// Check for transformation matrix
bool Matrix4::isTransformationMatrix() const {
    if (!rotation().isRotationMatrix()){
        return false;
    }
    if (!Tolerance::approximatelyEqual((*this)(3, 0), 0.0) ||
        !Tolerance::approximatelyEqual((*this)(3, 1), 0.0) ||
        !Tolerance::approximatelyEqual((*this)(3, 2), 0.0) ||
        !Tolerance::approximatelyEqual((*this)(3, 3), 1.0)) {
        return false;
    }
    return true;
}