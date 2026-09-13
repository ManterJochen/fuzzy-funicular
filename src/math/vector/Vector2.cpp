#include "Vector2.h"

#include <stdexcept>

Vector2::Vector2(double x, double y) : VectorN(2) {
    data_[0] = x;
    data_[1] = y;
}

double Vector2::x() const {
    return data_[0];
}

double Vector2::y() const {
    return data_[1];
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x() + other.x(), y() + other.y());
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x() - other.x(), y() - other.y());
}

Vector2 Vector2::operator*(double scalar) const {
    return Vector2(x() * scalar, y() * scalar);
}

Vector2 Vector2::operator/(double scalar) const {
    if (scalar == 0.0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    return Vector2(x() / scalar, y() / scalar);
}

double Vector2::dot(const Vector2& other) const {
    return x() * other.x() + y() * other.y();
}