using namespace std;
#include <vector>
#include <iostream>

class ListMatrix {
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

    int findIndex(size_t i, size_t j) const {
        for (size_t idx = 0; idx < data_.size(); ++idx) {
            if (data_[idx].row == i && data_[idx].col == j)
                return static_cast<int>(idx);
        }
        return -1;
    }

    void set(size_t i, size_t j, double val) {
        if (i >= rows_ || j >= cols_)
            throw out_of_range("Matrix index out of range");
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

    double sum() const {
        double s = 0.0;
        for (const auto& e : data_)
            s += e.value;
        return s;
    }

public:
    // Конструкторы и деструктор
    ListMatrix();
    ListMatrix(size_t rows, size_t cols);
    ListMatrix(const ListMatrix& other);
    ~ListMatrix() = default;

    // Присваивание
    ListMatrix& operator=(const ListMatrix& other);

    // Доступ к элементам
    double operator()(size_t i, size_t j) const;

    // Установка значения
    void setValue(size_t i, size_t j, double val);

    // Проверки
    bool can_multiply(const ListMatrix& other) const;
    bool equal_size(const ListMatrix& other) const;

    // Бинарные операторы: Matrix с матрицей
    ListMatrix operator+(const ListMatrix& other) const;
    ListMatrix operator-(const ListMatrix& other) const;
    ListMatrix operator*(const ListMatrix& other) const;

    // Бинарные операторы: Matrix со скаляром
    ListMatrix operator+(double scalar) const;
    ListMatrix operator-(double scalar) const;
    ListMatrix operator*(double scalar) const;
    ListMatrix operator/(double scalar) const;

    // Арифметика с накоплением
    ListMatrix& operator+=(const ListMatrix& other);
    ListMatrix& operator-=(const ListMatrix& other);
    ListMatrix& operator+=(double scalar);
    ListMatrix& operator-=(double scalar);

    // Унарные операторы
    ListMatrix& operator++();
    ListMatrix operator++(int);
    ListMatrix& operator--();
    ListMatrix operator--(int);

    // Логические операторы
    bool operator==(const ListMatrix& other) const;
    bool operator!=(const ListMatrix& other) const;
    bool operator<(const ListMatrix& other) const;
    bool operator>(const ListMatrix& other) const;

    // Преобразование к double
    operator double() const;

    // Вывод
    void print() const;

    // Дружественные функции
    friend ListMatrix operator+(double scalar, const ListMatrix& mat);
    friend ListMatrix operator-(double scalar, const ListMatrix& mat);
    friend ListMatrix operator*(double scalar, const ListMatrix& mat);
    friend ostream& operator<<(ostream& os, const ListMatrix& mat);
};

// Реализация методов

ListMatrix::ListMatrix() : rows_(0), cols_(0) {}

ListMatrix::ListMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    if (rows == 0 || cols == 0)
        throw invalid_argument("Matrix dimensions must be positive");
}

ListMatrix::ListMatrix(const ListMatrix& other)
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

ListMatrix& ListMatrix::operator=(const ListMatrix& other) {
    if (this != &other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;
    }
    return *this;
}

double ListMatrix::operator()(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_)
        throw out_of_range("Matrix index out of range");
    int idx = findIndex(i, j);
    return (idx == -1) ? 0.0 : data_[idx].value;
}

void ListMatrix::setValue(size_t i, size_t j, double val) {
    set(i, j, val);
}

bool ListMatrix::can_multiply(const ListMatrix& other) const {
    return cols_ == other.rows_;
}

bool ListMatrix::equal_size(const ListMatrix& other) const {
    return (rows_ == other.rows_) && (cols_ == other.cols_);
}

ListMatrix ListMatrix::operator*(const ListMatrix& other) const {
    if (!can_multiply(other))
        throw invalid_argument("Incompatible matrix dimensions for multiplication");

    ListMatrix result(rows_, other.cols_);

    vector<vector<pair<size_t, double>>> b_rows(other.rows_);
    for (const auto& e : other.data_) {
        b_rows[e.row].emplace_back(e.col, e.value);
    }

    for (const auto& a_elem : data_) {
        size_t i = a_elem.row;
        size_t j = a_elem.col;
        double a_val = a_elem.value;

        for (const auto& [k, b_val] : b_rows[j]) {
            double product = a_val * b_val;
            if (product != 0.0) {
                double current = result(i, k);
                result.setValue(i, k, current + product);
            }
        }
    }

    return result;
}

ListMatrix ListMatrix::operator+(const ListMatrix& other) const {
    if (!equal_size(other))
        throw invalid_argument("Matrices must have equal dimensions");
    ListMatrix result(rows_, cols_);
    for (const auto& e : data_) {
        double val = e.value + other(e.row, e.col);
        if (val != 0.0) result.set(e.row, e.col, val);
    }
    for (const auto& e : other.data_) {
        if (findIndex(e.row, e.col) == -1) {
            if (e.value != 0.0) result.set(e.row, e.col, e.value);
        }
    }
    return result;
}

ListMatrix ListMatrix::operator-(const ListMatrix& other) const {
    if (!equal_size(other))
        throw invalid_argument("Matrices must have equal dimensions");
    ListMatrix result(rows_, cols_);
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

ListMatrix ListMatrix::operator+(double scalar) const {
    ListMatrix result(*this);
    for (auto& e : result.data_) e.value += scalar;
    return result;
}

ListMatrix ListMatrix::operator-(double scalar) const {
    ListMatrix result(*this);
    for (auto& e : result.data_) e.value -= scalar;
    return result;
}

ListMatrix ListMatrix::operator*(double scalar) const {
    ListMatrix result(rows_, cols_);
    for (const auto& e : data_) {
        double val = e.value * scalar;
        if (val != 0.0) result.set(e.row, e.col, val);
    }
    return result;
}

ListMatrix ListMatrix::operator/(double scalar) const {
    if (scalar == 0.0)
        throw invalid_argument("Division by zero");
    return (*this) * (1.0 / scalar);
}

ListMatrix& ListMatrix::operator+=(const ListMatrix& other) {
    *this = *this + other;
    return *this;
}

ListMatrix& ListMatrix::operator-=(const ListMatrix& other) {
    *this = *this - other;
    return *this;
}

ListMatrix& ListMatrix::operator+=(double scalar) {
    for (auto& e : data_) e.value += scalar;
    return *this;
}

ListMatrix& ListMatrix::operator-=(double scalar) {
    for (auto& e : data_) e.value -= scalar;
    return *this;
}

ListMatrix& ListMatrix::operator++() {
    for (auto& e : data_) ++e.value;
    return *this;
}

ListMatrix ListMatrix::operator++(int) {
    ListMatrix tmp(*this);
    ++(*this);
    return tmp;
}

ListMatrix& ListMatrix::operator--() {
    for (auto& e : data_) --e.value;
    return *this;
}

ListMatrix ListMatrix::operator--(int) {
    ListMatrix tmp(*this);
    --(*this);
    return tmp;
}

bool ListMatrix::operator==(const ListMatrix& other) const {
    if (!equal_size(other)) return false;
    if (data_.size() != other.data_.size()) return false;
    for (const auto& e : data_) {
        if (other(e.row, e.col) != e.value)
            return false;
    }
    return true;
}

bool ListMatrix::operator!=(const ListMatrix& other) const {
    return !(*this == other);
}

bool ListMatrix::operator<(const ListMatrix& other) const {
    return sum() < other.sum();
}

bool ListMatrix::operator>(const ListMatrix& other) const {
    return sum() > other.sum();
}

ListMatrix::operator double() const {
    return sum();
}

void ListMatrix::print() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            cout << (*this)(i, j) << "\t";
        }
        cout << "\n";
    }
}

ListMatrix operator+(double scalar, const ListMatrix& mat) {
    return mat + scalar;
}

ListMatrix operator-(double scalar, const ListMatrix& mat) {
    ListMatrix result(mat.rows_, mat.cols_);
    for (size_t i = 0; i < mat.rows_; ++i) {
        for (size_t j = 0; j < mat.cols_; ++j) {
            double val = scalar - mat(i, j);
            if (val != 0.0) result.setValue(i, j, val);
        }
    }
    return result;
}

ListMatrix operator*(double scalar, const ListMatrix& mat) {
    return mat * scalar;
}

ostream& operator<<(ostream& os, const ListMatrix& mat) {
    for (size_t i = 0; i < mat.rows_; ++i) {
        for (size_t j = 0; j < mat.cols_; ++j) {
            os << mat(i, j) << "\t";
        }
        os << "\n";
    }
    return os;
}