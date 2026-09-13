#include "VectorN.h"
#include "../scalar/Tolerance.h"

#include <cmath>
#include <stdexcept>

VectorN::VectorN(int dimension) : data_(dimension, 0.0) {
    if (dimension <= 0) {
        throw std::invalid_argument("Dimension must be positive");
    }
}

int VectorN::dimension() const {
    return static_cast<int>(data_.size());
}

double& VectorN::operator[](int index) {
    if (index < 0 || index >= dimension()) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

const double& VectorN::operator[](int index) const {
    if (index < 0 || index >= dimension()) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

VectorN VectorN::operator+(const VectorN& other) const {
    if (dimension() != other.dimension()) {
        throw std::invalid_argument("Dimensions must match for addition");
    }
    VectorN result(dimension());
    for (int i = 0; i < dimension(); ++i) {
        result[i] = data_[i] + other[i];
    }
    return result;
}

VectorN VectorN::operator-(const VectorN& other) const {
    if (dimension() != other.dimension()) {
        throw std::invalid_argument("Dimensions must match for subtraction");
    }
    VectorN result(dimension());
    for (int i = 0; i < dimension(); ++i) {
        result[i] = data_[i] - other[i];
    }
    return result;
}

VectorN VectorN::operator*(double scalar) const {
    VectorN result(dimension());
    for (int i = 0; i < dimension(); ++i) {
        result[i] = data_[i] * scalar;
    }
    return result;
}

VectorN VectorN::operator/(double scalar) const {
    if (scalar == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    VectorN result(dimension());
    for (int i = 0; i < dimension(); ++i) {
        result[i] = data_[i] / scalar;
    }
    return result;
}

double VectorN::dot(const VectorN& other) const {
    if (dimension() != other.dimension()) {
        throw std::invalid_argument("Dimensions must match for dot product");
    }
    double result = 0.0;
    for (int i = 0; i < dimension(); ++i) {
        result += data_[i] * other[i];
    }
    return result;
}

VectorN VectorN::normalized() const {
    double len = length();
    if (Tolerance::approximatelyZero(len)) {
        throw std::invalid_argument("Cannot normalize zero-length vector");
    }
    return (*this) / len;
}

double VectorN::distance(const VectorN& other) const {
    return ((*this) - other).length();
}

double VectorN::squaredLength() const {
    return dot(*this);
}

double VectorN::length() const {
    return std::sqrt(squaredLength());
}

VectorN operator*(double scalar, const VectorN& vector) {
    return vector * scalar;
}