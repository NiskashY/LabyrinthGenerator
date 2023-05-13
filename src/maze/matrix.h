#pragma once

#include <iostream>
#include <vector>

class Matrix { 
public:
    Matrix() = default;

    explicit Matrix(size_t, size_t);

    auto show() -> void;
    auto resize(size_t, size_t) -> void;
    auto getRows() const -> size_t;
    auto getColumns() const -> size_t;
    auto setWall(size_t, size_t) -> bool;    // if i or j is larger than grid sizes -> return false, else -> true
    auto removeWall(size_t, size_t) -> bool;    // if i or j is larger than grid sizes -> return false, else -> true
    auto isWallExist(size_t, size_t) -> bool;
    auto assignBorderVertical() -> void;
    auto assignBorderHorizontal() -> void;

private:    // functions
    auto isBordersCorrect(size_t, size_t) const -> bool;

private:    // variables
    std::vector<std::vector<char>> walls;
    size_t rows_count = 0;
    size_t columns_count = 0;
};
