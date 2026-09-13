#pragma once

#include <vector>

class VectorN {
    protected:
        std::vector<double> data_;
    public:
        explicit VectorN(int dimension);
        int dimension() const;
        // Access element by index
        double& operator[](int index);
        const double& operator[](int index) const;

        // normal operations
        VectorN operator+(const VectorN& other) const;
        VectorN operator-(const VectorN& other) const;
        VectorN operator*(double scalar) const;
        VectorN operator/(double scalar) const;

        // Dot product
        double dot(const VectorN& other) const;
        

        // Length of the vector & squared length of the vector
        double length() const;
        double squaredLength() const;

        // Normalize the vector
        VectorN normalized() const;

        // Distance between two vectors
        double distance(const VectorN& other) const;
};