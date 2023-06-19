#pragma once

/*
 * Matrix file
 * in matrix can be two types of walls:
 *      first  - vertical right wall    (vert)
 *      second - horizontal bottom wall (hori)
 * structure of matrix:
 *      indicator: unsigned number in binary format 0b000
 *      if vert exists -> 0b001
 *      if hori exists -> 0b010
 *      if both exist  -> 0b011
*/

#include "helpers.h"

#include <QPoint>
#include <iostream>

class Matrix { 
public:
    Matrix() = default;

    Matrix(size_t, size_t, matrix_data_t = 0);

    auto show() const -> void;
    auto resize(size_t, size_t, int = 0) -> void;

    auto set(size_t, size_t, matrix_data_t) -> void;
    auto get(size_t, size_t) const -> matrix_data_t;
    auto setData(matrix_t) -> void;
    auto getData() const -> matrix_t;
    auto getRefData() const -> const matrix_t&;
    auto getRows() const -> size_t;
    auto getColumns() const -> size_t;

    auto setVerticalWall(size_t, size_t) -> bool;       // if i or j is larger than grid sizes -> return false, else -> true
    auto setHorizontalWall(size_t, size_t) -> bool;

    auto removeVerticalWall(size_t, size_t) -> bool;    // if i or j is larger than grid sizes -> return false, else -> true
    auto removeHorizontalWall(size_t, size_t) -> bool;    // if i or j is larger than grid sizes -> return false, else -> true

    auto isVerticalWallExist(size_t, size_t) const -> bool;
    auto isHorizontalWallExist(size_t, size_t) const -> bool;

    auto isBordersCorrect(size_t, size_t) const -> bool;
    auto isBordersCorrect(QPoint) const -> bool;

protected:    // variables
    matrix_t walls;
    size_t rows_count = 0;
    size_t columns_count = 0;
};

std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
