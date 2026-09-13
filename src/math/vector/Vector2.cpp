#include "Vector2.h"

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