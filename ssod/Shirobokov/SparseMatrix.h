// g++ main.cpp -o SparseMartix.exe
using namespace std;
#include <vector>
#include <iostream>
#include <numeric>

class SparseMatrix {
private:
    struct Element {
        size_t row;
        size_t col;
        double value;
        Element(size_t r, size_t c, double v) : row(r), col(c), value(v) {}
    };

    size_t rows_;
    size_t cols_;
    vector<Element> data_;

    // Вспомогательная функция: поиск индекса элемента по (i, j)
    int findIndex(size_t i, size_t j) const {
        for (size_t idx = 0; idx < data_.size(); ++idx) {
            if (data_[idx].row == i && data_[idx].col == j)
                return static_cast<int>(idx);
        }
        return -1;
    }

    // Внутренняя установка значения (с проверкой)
    void set(size_t i, size_t j, double val) {
        if (i >= rows_ || j >= cols_)
            throw out_of_range("Index out of bounds.");
        int idx = findIndex(i, j);
        if (val == 0.0) {
            if (idx != -1)
                data_.erase(data_.begin() + idx);
        } else {
            if (idx != -1)
                data_[idx].value = val;
            else
                data_.emplace_back(i, j, val);
        }
    }

    // Вспомогательная функция для суммы (используется в сравнении и приведении)
    double sum() const {
        double s = 0.0;
        for (const auto& e : data_)
            s += e.value;
        return s;
    }

public:
    //  Конструкторы и деструктор 

    SparseMatrix() : rows_(0), cols_(0) {}

    SparseMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        if (rows == 0 || cols == 0)
            throw invalid_argument("Matrix dimensions must be positive.");
    }

    SparseMatrix(const SparseMatrix& other)
        : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

    ~SparseMatrix() = default;

    //  Оператор присваивания 

    SparseMatrix& operator=(const SparseMatrix& other) {
        if (this != &other) {
            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = other.data_;
        }
        return *this;
    }

    //  Доступ к элементам 

    double operator()(size_t i, size_t j) const {
        if (i >= rows_ || j >= cols_)
            throw out_of_range("Index out of bounds.");
        int idx = findIndex(i, j);
        return (idx == -1) ? 0.0 : data_[idx].value;
    }

    //  Установка значения 

    void setValue(size_t i, size_t j, double val) {
        set(i, j, val);
    }

    //  Проверки 

    bool can_multiply(const SparseMatrix& other) const {
        return cols_ == other.rows_;
    }

    bool equal_size(const SparseMatrix& other) const {
        return (rows_ == other.rows_) && (cols_ == other.cols_);
    }

    //  Умножение матриц 

    SparseMatrix operator*(const SparseMatrix& other) const {
        if (!can_multiply(other))
            throw invalid_argument("Matrix dimensions incompatible for multiplication.");

        SparseMatrix result(rows_, other.cols_);

        // Группируем элементы правой матрицы по строкам для быстрого доступа
        vector<vector<pair<size_t, double>>> b_by_row(other.rows_);
        for (const auto& e : other.data_) {
            b_by_row[e.row].emplace_back(e.col, e.value);
        }

        // Перемножаем: для каждого ненулевого a[i][j] и b[j][k] → добавляем в c[i][k]
        for (const auto& a_elem : data_) {
            size_t i = a_elem.row;
            size_t j = a_elem.col;
            double a_val = a_elem.value;

            for (const auto& [k, b_val] : b_by_row[j]) {
                double product = a_val * b_val;
                if (product != 0.0) {
                    double current = result(i, k);
                    result.setValue(i, k, current + product);
                }
            }
        }

        return result;
    }

    //  Сложение и вычитание 

    SparseMatrix operator+(const SparseMatrix& other) const {
        if (!equal_size(other))
            throw invalid_argument("Matrix dimensions must match for addition.");
        SparseMatrix result(rows_, cols_);
        for (const auto& e : data_) {
            double val = e.value + other(e.row, e.col);
            if (val != 0.0) result.set(e.row, e.col, val);
        }
        for (const auto& e : other.data_) {
            if (findIndex(e.row, e.col) == -1) {
                double val = e.value;
                if (val != 0.0) result.set(e.row, e.col, val);
            }
        }
        return result;
    }

    SparseMatrix operator-(const SparseMatrix& other) const {
        if (!equal_size(other))
            throw invalid_argument("Matrix dimensions must match for subtraction.");
        SparseMatrix result(rows_, cols_);
        for (const auto& e : data_) {
            double val = e.value - other(e.row, e.col);
            if (val != 0.0) result.set(e.row, e.col, val);
        }
        for (const auto& e : other.data_) {
            if (findIndex(e.row, e.col) == -1) {
                double val = -e.value;
                if (val != 0.0) result.set(e.row, e.col, val);
            }
        }
        return result;
    }

    //  Арифметика с накоплением 

    SparseMatrix& operator+=(const SparseMatrix& other) {
        *this = *this + other;
        return *this;
    }

    SparseMatrix& operator-=(const SparseMatrix& other) {
        *this = *this - other;
        return *this;
    }

    //  Умножение и деление на скаляр 

    SparseMatrix operator*(double scalar) const {
        SparseMatrix res(rows_, cols_);
        for (const auto& e : data_) {
            double val = e.value * scalar;
            if (val != 0.0) res.set(e.row, e.col, val);
        }
        return res;
    }

    SparseMatrix operator/(double scalar) const {
        if (scalar == 0.0)
            throw invalid_argument("Division by zero.");
        return (*this) * (1.0 / scalar);
    }

    friend SparseMatrix operator*(double scalar, const SparseMatrix& mat) {
        return mat * scalar;
    }

    //  +=, -= со скаляром (только для ненулевых) 

    SparseMatrix& operator+=(double scalar) {
        for (auto& e : data_) e.value += scalar;
        return *this;
    }

    SparseMatrix& operator-=(double scalar) {
        for (auto& e : data_) e.value -= scalar;
        return *this;
    }

    //  Унарные операторы 

    SparseMatrix& operator++() { // префикс
        for (auto& e : data_) ++e.value;
        return *this;
    }

    SparseMatrix operator++(int) { // постфикс
        SparseMatrix tmp(*this);
        ++(*this);
        return tmp;
    }

    SparseMatrix& operator--() {
        for (auto& e : data_) --e.value;
        return *this;
    }

    SparseMatrix operator--(int) {
        SparseMatrix tmp(*this);
        --(*this);
        return tmp;
    }

    //  Логические операторы 

    bool operator==(const SparseMatrix& other) const {
        if (!equal_size(other)) return false;
        if (data_.size() != other.data_.size()) return false;
        for (const auto& e : data_) {
            if (other(e.row, e.col) != e.value)
                return false;
        }
        return true;
    }

    bool operator!=(const SparseMatrix& other) const {
        return !(*this == other);
    }

    bool operator<(const SparseMatrix& other) const {
        return sum() < other.sum();
    }

    bool operator>(const SparseMatrix& other) const {
        return sum() > other.sum();
    }

    //  Преобразование к базовому типу 

    operator double() const {
        return sum();
    }

    //  Вывод 

    void print() const {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                cout << (*this)(i, j) << "\t";
            }
            cout << "\n";
        }
    }
};