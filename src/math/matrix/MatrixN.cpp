#include "MatrixN.h"
#include "../scalar/Tolerance.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

//==================================
// Matrix constructors and checks
//==================================

// Check for valid matrix dimensions
MatrixN::MatrixN(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
    data_.assign(rows, std::vector<double>(cols, 0.0));
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

VectorN MatrixN::operator*(const VectorN& vector) const {
    if (cols() != vector.dimension()) {
        throw std::invalid_argument(
            "Matrix and vector dimensions must match for multiplication");
    }

    VectorN result(rows());
    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < cols(); ++column) {
            result[row] += (*this)(row, column) * vector[column];
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
    MatrixN copy(*this);
    double determinant = 1.0;
    const int size = rows();

    for (int pivotColumn = 0; pivotColumn < size; ++pivotColumn) {
        int pivotRow = pivotColumn;
        for (int row = pivotColumn + 1; row < size; ++row) {
            if (std::abs(copy(row, pivotColumn)) >
                std::abs(copy(pivotRow, pivotColumn))) {
                pivotRow = row;
            }
        }

        if (Tolerance::approximatelyEqual(copy(pivotRow, pivotColumn), 0.0)) {
            return 0.0;
        }

        if (pivotRow != pivotColumn) {
            std::swap(copy.data_[pivotRow], copy.data_[pivotColumn]);
            determinant = -determinant;
        }

        const double pivot = copy(pivotColumn, pivotColumn);
        determinant *= pivot;
        for (int row = pivotColumn + 1; row < size; ++row) {
            const double factor = copy(row, pivotColumn) / pivot;
            for (int column = pivotColumn + 1; column < size; ++column) {
                copy(row, column) -= factor * copy(pivotColumn, column);
            }
        }
    }

    return determinant;
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
    if (!isSquare()) {
        throw std::invalid_argument("Only square matrices can be inverted");
    }
    int n = rows();
    MatrixN result(n, n);
    MatrixN copy(*this);

    // Initialize result as the identity matrix
    for (int i = 0; i < n; ++i) {
        result(i, i) = 1.0;
    }

    for (int pivotColumn = 0; pivotColumn < n; ++pivotColumn) {
        int pivotRow = pivotColumn;
        for (int row = pivotColumn + 1; row < n; ++row) {
            if (std::abs(copy(row, pivotColumn)) >
                std::abs(copy(pivotRow, pivotColumn))) {
                pivotRow = row;
            }
        }

        if (Tolerance::approximatelyEqual(copy(pivotRow, pivotColumn), 0.0)) {
            throw std::invalid_argument("Matrix is not invertible");
        }

        if (pivotRow != pivotColumn) {
            std::swap(copy.data_[pivotRow], copy.data_[pivotColumn]);
            std::swap(result.data_[pivotRow], result.data_[pivotColumn]);
        }

        const double pivot = copy(pivotColumn, pivotColumn);
        for (int column = 0; column < n; ++column) {
            copy(pivotColumn, column) /= pivot;
            result(pivotColumn, column) /= pivot;
        }

        for (int row = 0; row < n; ++row) {
            if (row == pivotColumn) {
                continue;
            }
            const double factor = copy(row, pivotColumn);
            for (int column = 0; column < n; ++column) {
                copy(row, column) -= factor * copy(pivotColumn, column);
                result(row, column) -= factor * result(pivotColumn, column);
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
            if (i == j && !Tolerance::approximatelyEqual((*this)(i, j), 1.0)) {
                return false;
            } else if (i != j && !Tolerance::approximatelyEqual((*this)(i, j), 0.0)) {
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
            if (!Tolerance::approximatelyEqual((*this)(i, j), (*this)(j, i))) {
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

bool MatrixN::isFinite() const {
    for (int row = 0; row < rows(); ++row) {
        for (int column = 0; column < cols(); ++column) {
            if (!Tolerance::isFinite((*this)(row, column))) {
                return false;
            }
        }
    }
    return true;
}
