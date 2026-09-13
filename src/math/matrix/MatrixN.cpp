#include "MatrixN.h"
#include "../scalar/Tolerance.h"

#include <cmath>
#include <stdexcept>

//==================================
// Matrix constructors and checks
//==================================

// Check for valid matrix dimensions
MatrixN::MatrixN(int rows, int cols) : data_(rows, std::vector<double>(cols, 0.0)){
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
}

// Return the number of rows in the matrix
int MatrixN::rows() const {
    return static_cast<int>(data_.size());
}

// Return the number of columns in the matrix (If the matrix is empty, return 0)
int MatrixN::cols() const {
    return static_cast<int>(data_.empty() ? 0 : data_[0].size());
}

// Access element at (row, col) with bounds checking
double& MatrixN::operator()(int row, int col) {
    if (row < 0 || row >= rows() || col < 0 || col >= cols()) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data_[row][col];
}

// Access element at (row, col) with bounds checking (const version)
const double& MatrixN::operator()(int row, int col) const {
    if (row < 0 || row >= rows() || col < 0 || col >= cols()) {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data_[row][col];
}

//==========================
// Matrix arithmetic operations
//==========================

// Matrix with Matrix addition
MatrixN MatrixN::operator+(const MatrixN& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    MatrixN result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

// Matrix with Matrix subtraction
MatrixN MatrixN::operator-(const MatrixN& other) const {
    if (rows() != other.rows() || cols() != other.cols()) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    MatrixN result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

// Matrix with Matrix multiplication
MatrixN MatrixN::operator*(const MatrixN& other) const {
    if (cols() != other.rows()){
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }
    MatrixN result(rows(), other.cols());
    for (int i = 0; i < rows(); ++i){
        for (int j = 0; j < other.cols(); ++j){
            for (int k = 0; k < cols(); ++k){
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}


//==========================
// Matrix with Vector multiplication
//==========================

// Matrix with Vector multiplication
std::vector<double> MatrixN::operator*(const std::vector<double>& vec) const {
    if (cols() != static_cast<int>(vec.size())) {
        throw std::invalid_argument("Matrix and vector dimensions must match for multiplication");
    }
    std::vector<double> result(rows(), 0.0);
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result[i] += (*this)(i, j) * vec[j];
        }
    }
    return result;
}

//==========================
// Matrix special operations
//==========================

// determinant of the matrix
double MatrixN::determinant() const {
    if (!isSquare()) {
        throw std::invalid_argument("Determinant is defined only for square matrices");
    }
    // Base case for 1x1 matrix
    if (rows() == 1) {
        return (*this)(0, 0);
    }
    // Base case for 2x2 matrix
    if (rows() == 2) {
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    }
    // Recursive case for NxN matrix
    double det = 0.0;
    for (int j = 0; j < cols(); ++j) {
        MatrixN subMatrix(rows() - 1, cols() - 1);
        for (int i = 1; i < rows(); ++i) {
            int subCol = 0;
            for (int k = 0; k < cols(); ++k) {
                if (k == j) continue;
                subMatrix(i - 1, subCol) = (*this)(i, k);
                ++subCol;
            }
        }
        det += (j % 2 == 0 ? 1 : -1) * (*this)(0, j) * subMatrix.determinant();
    }
    return det;
}

// transpose of the matrix
MatrixN MatrixN::transpose() const {
    MatrixN result(cols(), rows());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

// inverse of the matrix
MatrixN MatrixN::inverse() const {
    if (!isInvertible()) {
        throw std::invalid_argument("Matrix is not invertible");
    }
    int n = rows();
    MatrixN result(n, n);
    MatrixN copy(*this);

    // Initialize result as the identity matrix
    for (int i = 0; i < n; ++i) {
        result(i, i) = 1.0;
    }

    // Perform Gaussian elimination
    for (int i = 0; i < n; ++i) {
        // Find the pivot
        double pivot = copy(i, i);
        if (Tolerance::approximatelyEqual(pivot, 0.0)) {
            throw std::runtime_error("Numerical instability encountered during inversion");
        }
        for (int j = 0; j < n; ++j) {
            copy(i, j) /= pivot;
            result(i, j) /= pivot;
        }
        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = copy(k, i);
            for (int j = 0; j < n; ++j) {
                copy(k, j) -= factor * copy(i, j);
                result(k, j) -= factor * result(i, j);
            }
        }
    }
    return result;
}

// norm of the matrix
double MatrixN::norm() const {
    double sum = 0.0;
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            sum += (*this)(i, j) * (*this)(i, j);
        }
    }
    return std::sqrt(sum);
}

//==================================
// Matrix with scalar operations
//==================================

// multiply the matrix by a scalar
MatrixN MatrixN::operator*(double scalar) const {
    MatrixN result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }
    return result;
}

// divide the matrix by a scalar
MatrixN MatrixN::operator/(double scalar) const {
    if (Tolerance::approximatelyEqual(scalar, 0.0)) {
        throw std::invalid_argument("Division by zero");
    }
    MatrixN result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result(i, j) = (*this)(i, j) / scalar;
        }
    }
    return result;
}

//==================================
// Matrix factorization functions
//==================================

// Identity matrix
MatrixN MatrixN::identity(int size) {
    MatrixN result(size, size);
    for (int i = 0; i < size; ++i) {
        result(i, i) = 1.0;
    }
    return result;
}

// zero matrix
MatrixN MatrixN::zero(int rows, int cols) {
    MatrixN result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = 0.0;
        }
    }
    return result;
}

//==================================
// Matrix property checks
//==================================


// check if the matrix is square
bool MatrixN::isSquare() const {
    return rows() == cols();
}

// check if the matrix is an identity matrix
bool MatrixN::isIdentity() const {
    if (!isSquare()) {
        return false;
    }
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            if (i == j && (*this)(i, j) != 1.0) {
                return false;
            } else if (i != j && (*this)(i, j) != 0.0) {
                return false;
            }
        }
    }
    return true;
}

// check if the matrix is Symmetric
bool MatrixN::isSymmetric() const {
    if (!isSquare()) {
        return false;
    }
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            if ((*this)(i, j) != (*this)(j, i)) {
                return false;
            }
        }
    }
    return true;
}

// check if the matrix is invertible
bool MatrixN::isInvertible() const {
    if (!isSquare()) {
        return false;
    }
    return !Tolerance::approximatelyEqual(determinant(), 0.0);
}
