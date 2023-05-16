#pragma once

#include <iostream>
#include <random>
#include <vector>

class Matrix { 
public:
    Matrix() = default;

    explicit Matrix(size_t, size_t);

    auto show() const -> void;
    auto resize(size_t, size_t, int = 0) -> void;

    auto setData(std::vector<std::vector<int>>) -> void;
    auto getData() const -> std::vector<std::vector<int>>;
    auto getRows() const -> size_t;
    auto getColumns() const -> size_t;

    auto setWall(size_t, size_t) -> bool;       // if i or j is larger than grid sizes -> return false, else -> true
    auto removeWall(size_t, size_t) -> bool;    // if i or j is larger than grid sizes -> return false, else -> true
    auto isWallExist(size_t, size_t) const -> bool;

    virtual auto assignBorder() -> void = 0;

private:    // functions
    auto isBordersCorrect(size_t, size_t) const -> bool;

protected:    // variables
    std::vector<std::vector<int>> walls;
    size_t rows_count = 0;
    size_t columns_count = 0;
};

class HorizontalMatrix : public Matrix {
public:
    HorizontalMatrix() : Matrix() {};

    explicit HorizontalMatrix(size_t, size_t);

    auto assignBorder() -> void override;
};

class VerticalMatrix : public Matrix {
public:
    VerticalMatrix() : Matrix() {};

    explicit VerticalMatrix(size_t, size_t);

    auto assignBorder() -> void override;
};

std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
