#include "Vector6.h"
#include <stdexcept>

Vector6::Vector6(double x1, double x2, double x3, double x4, double x5, double x6)
    : VectorN(6)
{
    data_[0] = x1;
    data_[1] = x2;
    data_[2] = x3;
    data_[3] = x4;
    data_[4] = x5;
    data_[5] = x6;
}

double Vector6::x1() const {
    return data_[0];
}

double Vector6::x2() const {
    return data_[1];
}

double Vector6::x3() const {
    return data_[2];
}

double Vector6::x4() const {
    return data_[3];
}

double Vector6::x5() const {
    return data_[4];
}

double Vector6::x6() const {
    return data_[5];
}

double Vector6::dot(const Vector6& other) const {
    return x1() * other.x1() +
           x2() * other.x2() +
           x3() * other.x3() +
           x4() * other.x4() +
           x5() * other.x5() +
           x6() * other.x6();
}

Vector6 Vector6::operator+(const Vector6& other) const {
    return Vector6(x1() + other.x1(), x2() + other.x2(), x3() + other.x3(), x4() + other.x4(), x5() + other.x5(), x6() + other.x6());
}

Vector6 Vector6::operator-(const Vector6& other) const {
    return Vector6(x1() - other.x1(), x2() - other.x2(), x3() - other.x3(), x4() - other.x4(), x5() - other.x5(), x6() - other.x6());
}

Vector6 Vector6::operator*(double scalar) const {
    return Vector6(x1() * scalar, x2() * scalar, x3() * scalar, x4() * scalar, x5() * scalar, x6() * scalar);
}

Vector6 Vector6::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::runtime_error("Cannot divide by zero");
    }
    return Vector6(x1() / scalar, x2() / scalar, x3() / scalar, x4() / scalar, x5() / scalar, x6() / scalar);
}