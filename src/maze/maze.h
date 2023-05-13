#pragma once

#include <cstddef>
#include <random>
#include <unordered_map>

#include "matrix.h"

class MazeGenerator {
public:

    MazeGenerator() = default;

    explicit MazeGenerator(size_t, size_t);

    auto generate() -> void;
    auto show() const -> void;
    auto create(size_t, size_t) -> void;
    auto resize(size_t, size_t) -> void;
    auto getRows() const -> size_t;
    auto getColumns() const -> size_t;

    auto get(size_t r, size_t c) -> std::pair<bool, bool> {
        return {vertical_walls.isWallExist(r, c), horizontal_walls.isWallExist(r, c)};
    }

private: // functions
    auto addLastRow()               -> void;
    auto fillEmptyCells()           -> void;
    auto assignUniqueSets()         -> void;
    auto createVerticalWalls(int)   -> void;
    auto createHorizontalWalls(int) -> void;
    auto prepareNewLine(int)        -> void;
    auto mergeSets(int, int)        -> void;
    auto getRoot(int)               -> int;
    auto random(int, int)           -> int;


private: // variables
    Matrix vertical_walls;   /* vertical   - right border of cell */
    Matrix horizontal_walls; /* horizontal - bottom border of cell */

    std::unordered_map<int, int> parent; // TODO: move this to local variable
    std::vector<int> line;     // TODO: move this to local varibale

    static constexpr int kEmptyCell = 0;
    size_t rows = 0, columns = 0;
    int set_counter = 1;
};
