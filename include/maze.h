#pragma once

#include <unordered_map>

#include "matrix.h"
#include "helpers.h"

class Maze {
public:

    Maze() = default;

    explicit Maze(size_t, size_t);

    auto generate() -> void;
    auto show() const -> void;
    auto create(size_t, size_t) -> void;
    auto resize(size_t, size_t, int = 0) -> void;

    auto getRows() const -> size_t;
    auto getColumns() const -> size_t;
    auto getData() const -> matrix_t;
    auto getRefData() const -> const matrix_t&;
    auto setData(const matrix_t&) -> void;

    auto isHorizontalWall(size_t x, size_t y) const -> bool;
    auto isVerticallWall(size_t x, size_t y) const -> bool;

    auto findPath(QPoint, QPoint) const -> Matrix;
    auto isSeparatedByWall(QPoint, QPoint) const -> bool;

private: // functions
    auto addLastRow()               -> void;
    auto fillEmptyCells()           -> void;
    auto assignUniqueSets()         -> void;
    auto prepareNewLine(int)        -> void;

    auto createVerticalWalls(int)   -> void;
    auto createHorizontalWalls(int) -> void;
    auto mergeSets(int, int)        -> void;
    auto getRoot(int)               -> int;

private: // variables
    Matrix walls;

    std::unordered_map<int, int> parent; // TODO: move this to local variable
    std::vector<int> line;     // TODO: move this to local varibale

    static constexpr int kEmptyCell = 0;
    size_t rows = 0, columns = 0;
    int set_counter = 1;
};
