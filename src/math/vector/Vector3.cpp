#include "Vector3.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

Vector3::Vector3(double x, double y, double z)
    : VectorN(3)
    {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

// accessors for x, y, z components
double Vector3::x() const {
    return data_[0];
}

double Vector3::y() const {
    return data_[1];
}

double Vector3::z() const {
    return data_[2];
}

// addition
Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x() + other.x(), y() + other.y(), z() + other.z());
}

// subtraction
Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x() - other.x(), y() - other.y(), z() - other.z());
}

// scalar multiplication
Vector3 Vector3::operator*(double scalar) const {
    return Vector3(x() * scalar, y() * scalar, z() * scalar);
}

// scalar division
Vector3 Vector3::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::runtime_error("Cannot divide by zero");
    }
    return Vector3(x() / scalar, y() / scalar, z() / scalar);
}

// dot product
double Vector3::dot(const Vector3& other) const {
    return x() * other.x() +
           y() * other.y() +
           z() * other.z();
}

// cross product
Vector3 Vector3::cross(const Vector3& other) const {
    return Vector3(
        y() * other.z() - z() * other.y(),
        z() * other.x() - x() * other.z(),
        x() * other.y() - y() * other.x()
    );
}

// Angle between two vectors
Angle Vector3::angle(const Vector3& other) const {
    double denominator = length() * other.length();
    if (denominator == 0){
        throw std::runtime_error("Cannot calculate angle with zero-length vector");
    }

    double value = dot(other) / denominator;
    value = std::clamp(value, -1.0, 1.0);
    return Angle::fromRadians(std::acos(value));
}

// Projection of this vector onto another vector
Vector3 Vector3::projection(const Vector3& other) const {
    double denominator = other.squaredLength();

    if (denominator == 0) {
        throw std::runtime_error("Cannot project onto zero-length vector");
    }
    double factor = dot(other) / denominator;

    return other * factor;
}

// Rejection of this vector from another vector
Vector3 Vector3::rejection(const Vector3& other) const {
    return *this - projection(other);
}

// Reflection of this vector about a normal vector
Vector3 Vector3::reflection(const Vector3& normal) const {
    return *this - normal * (2 * dot(normal));
}