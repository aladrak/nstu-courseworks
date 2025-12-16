using namespace std;
#include <vector>
#include <iostream>
#include <iomanip>

class Matrix {
private:
    size_t rows_;
    size_t cols_;
    vector<vector<double>> data_;

public:
    // Конструкторы
    Matrix() : rows_(0), cols_(0), data_() {}

    Matrix(size_t rows, size_t cols, double value = 0.0)
        : rows_(rows), cols_(cols) {
        if (rows == 0 || cols == 0) {
            throw invalid_argument("Matrix dimensions must be positive integers.");
        }
        data_.resize(rows_, vector<double>(cols_, value));
    }

    Matrix(const Matrix& other)
        : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

    // Деструктор
    ~Matrix() = default;

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = other.data_;
        }
        return *this;
    }

    // Сложение
    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw invalid_argument("Matrix addition: dimensions must match.");
        }
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }

    // Вычитание
    Matrix operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw invalid_argument("Matrix subtraction: dimensions must match.");
        }
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] - other.data_[i][j];
            }
        }
        return result;
    }

    // Умножение матриц
    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw invalid_argument(
                "Matrix multiplication: inner dimensions must agree (A.cols == B.rows)."
            );
        }
        Matrix result(rows_, other.cols_, 0.0);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t k = 0; k < cols_; ++k) {
                if (data_[i][k] == 0.0) continue; // оптимизация для разреженных данных
                for (size_t j = 0; j < other.cols_; ++j) {
                    result.data_[i][j] += data_[i][k] * other.data_[k][j];
                }
            }
        }
        return result;
    }

    // Умножение матрицы на скаляр
    Matrix operator*(double scalar) const {
        Matrix result(*this);
        for (auto& row : result.data_) {
            for (auto& val : row) {
                val *= scalar;
            }
        }
        return result;
    }

    // Деление матрицы на скаляр
    Matrix operator/(double scalar) const {
        if (scalar == 0.0) {
            throw invalid_argument("Division by zero in matrix/scalar operation.");
        }
        Matrix result(*this);
        for (auto& row : result.data_) {
            for (auto& val : row) {
                val /= scalar;
            }
        }
        return result;
    }

    // Скаляр * Matrix (дружественная функция)
    friend Matrix operator*(double scalar, const Matrix& mat) {
        return mat * scalar;
    }

    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        *this = *this - other;
        return *this;
    }

    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    Matrix& operator*=(double scalar) {
        *this = *this * scalar;
        return *this;
    }

    Matrix& operator/=(double scalar) {
        *this = *this / scalar;
        return *this;
    }
    // Префиксный инкремент: увеличивает каждый элемент на 1
    Matrix& operator++() {
        for (auto& row : data_) {
            for (auto& val : row) {
                ++val;
            }
        }
        return *this;
    }

    // Постфиксный инкремент
    Matrix operator++(int) {
        Matrix temp(*this);
        ++(*this);
        return temp;
    }

    // Префиксный декремент
    Matrix& operator--() {
        for (auto& row : data_) {
            for (auto& val : row) {
                --val;
            }
        }
        return *this;
    }

    // Постфиксный декремент
    Matrix operator--(int) {
        Matrix temp(*this);
        --(*this);
        return temp;
    }

    bool operator==(const Matrix& other) const {
        return rows_ == other.rows_ && cols_ == other.cols_ && data_ == other.data_;
    }
    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }
    bool operator<(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw logic_error("Cannot compare matrices of different dimensions.");
        }
        return data_ < other.data_;
    }
    bool operator>(const Matrix& other) const {
        return other < *this;
    }

    double& operator()(size_t i, size_t j) {
        if (i >= rows_ || j >= cols_) {
            throw out_of_range("Matrix index out of range.");
        }
        return data_[i][j];
    }
    const double& operator()(size_t i, size_t j) const {
        if (i >= rows_ || j >= cols_) {
            throw out_of_range("Matrix index out of range.");
        }
        return data_[i][j];
    }

    explicit operator double() const {
        double sum = 0.0;
        for (const auto& row : data_) {
            for (double val : row) {
                sum += val;
            }
        }
        return sum;
    }
    explicit operator bool() const {
        for (const auto& row : data_) {
            for (double val : row) {
                if (val != 0.0) return true;
            }
        }
        return false;
    }

    size_t rows() const noexcept { return rows_; }
    size_t cols() const noexcept { return cols_; }

    void print(ostream& os = cout, int width = 10, int precision = 4) const {
        if (rows_ == 0 || cols_ == 0) {
            os << "[empty matrix]\n";
            return;
        }
        os << fixed << setprecision(precision);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                os << setw(width) << data_[i][j] << ' ';
            }
            os << '\n';
        }
    }
};