#include "Vector4.h"
#include <stdexcept>

Vector4::Vector4(double x, double y, double z, double w)
    : VectorN(4)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
    data_[3] = w;
}

double Vector4::x() const {
    return data_[0];
}

double Vector4::y() const {
    return data_[1];
}

double Vector4::z() const {
    return data_[2];
}

double Vector4::w() const {
    return data_[3];
}

double Vector4::dot(const Vector4& other) const {
    return x() * other.x() +
           y() * other.y() +
           z() * other.z() +
           w() * other.w();
}

Vector4 Vector4::operator+(const Vector4& other) const {
    return Vector4(x() + other.x(), y() + other.y(), z() + other.z(), w() + other.w());
}

Vector4 Vector4::operator-(const Vector4& other) const {
    return Vector4(x() - other.x(), y() - other.y(), z() - other.z(), w() - other.w());
}

Vector4 Vector4::operator*(double scalar) const {
    return Vector4(x() * scalar, y() * scalar, z() * scalar, w() * scalar);
}

Vector4 Vector4::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::runtime_error("Cannot divide by zero");
    }
    return Vector4(x() / scalar, y() / scalar, z() / scalar, w() / scalar);
}