#include "Matrix3.h"
#include "../scalar/Tolerance.h"

#include <cmath>
#include <stdexcept>


//====================================
// Constructors
//====================================

Matrix3::Matrix3() : MatrixN(3, 3) {}

Matrix3::Matrix3(
    std::initializer_list<std::initializer_list<double>> values)
    : MatrixN(3, 3) {
    if (values.size() != 3) {
        throw std::invalid_argument("Matrix3 requires 3 rows");
    }

    int row = 0;
    for (const auto& valuesRow : values) {
        if (valuesRow.size() != 3) {
            throw std::invalid_argument("Matrix3 requires 3 columns");
        }

        int column = 0;
        for (double value : valuesRow) {
            data_[row][column] = value;
            ++column;
        }
        ++row;
    }
}

Matrix3::Matrix3(const MatrixN& matrix) : MatrixN(matrix) {
    if (matrix.rows() != 3 || matrix.cols() != 3) {
        throw std::invalid_argument("Matrix must be 3x3");
    }
}

Matrix3 Matrix3::operator*(double scalar) const {
    return Matrix3(MatrixN::operator*(scalar));
}

Matrix3 Matrix3::operator/(double scalar) const {
    return Matrix3(MatrixN::operator/(scalar));
}

Matrix3 Matrix3::operator+(const Matrix3& other) const {
    return Matrix3(MatrixN::operator+(other));
}

Matrix3 Matrix3::operator-(const Matrix3& other) const {
    return Matrix3(MatrixN::operator-(other));
}

Matrix3 Matrix3::operator*(const Matrix3& other) const {
    return Matrix3(MatrixN::operator*(other));
}

Vector3 Matrix3::operator*(const Vector3& vector) const {
    const std::vector<double> result = MatrixN::operator*(
        std::vector<double>{vector.x(), vector.y(), vector.z()});
    return Vector3(result[0], result[1], result[2]);
}

Matrix3 Matrix3::transpose() const {
    return Matrix3(MatrixN::transpose());
}

Matrix3 Matrix3::inverse() const {
    return Matrix3(MatrixN::inverse());
}

//====================================
// Matrix3 Operations (specials)
//====================================

// Rotation matrices
Matrix3 Matrix3::rotationX(const Angle& angle) {
    double c = std::cos(angle.radians());
    double s = std::sin(angle.radians());
    Matrix3 result({
        {1, 0, 0},
        {0, c, -s},
        {0, s, c}
    });
    return result;
}

Matrix3 Matrix3::rotationY(const Angle& angle) {
    double c = std::cos(angle.radians());
    double s = std::sin(angle.radians());
    return Matrix3({
        {c, 0, s},
        {0, 1, 0},
        {-s, 0, c}
    });
}

Matrix3 Matrix3::rotationZ(const Angle& angle) {
    double c = std::cos(angle.radians());
    double s = std::sin(angle.radians());
    return Matrix3({
        {c, -s, 0},
        {s, c, 0},
        {0, 0, 1}
    });
}

// Euler angles to rotation matrix
// Euler XYZ angles
// Convention:
// R = Rz(Z) * Ry(Y) * Rx(X)
Matrix3 Matrix3::fromEulerXYZ(
    const Angle& X,
    const Angle& Y,
    const Angle& Z)
{
    double alpha = Z.radians();
    double beta = Y.radians();
    double gamma = X.radians();

    double ca = std::cos(alpha);
    double sa = std::sin(alpha);
    double cb = std::cos(beta);
    double sb = std::sin(beta);
    double cg = std::cos(gamma);
    double sg = std::sin(gamma);

    return Matrix3({
        {cb * cg, -cb * sg, sb},
        {sa * sb * cg + ca * sg, -sa * sb * sg + ca * cg, -sa * cb},
        {-ca * sb * cg + sa * sg, ca * sb * sg + sa * cg, ca * cb}
    });
}

// check if a matrix is a rotation matrix
bool Matrix3::isRotationMatrix() const {
    Matrix3 Rt = this->transpose();
    Matrix3 shouldBeIdentity = Rt * (*this);
    Matrix3 I({
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    });
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!Tolerance::approximatelyEqual(shouldBeIdentity(i, j), I(i, j))) {
                return false;
            }
        }
    }
    return Tolerance::approximatelyEqual(determinant(), 1.0);
}