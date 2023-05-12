#pragma once

#include <cstddef>
#include <random>
#include <unordered_map>

#include "matrix.h"

class MazeGenerator {
public: 
    explicit MazeGenerator(size_t, size_t);

    auto generate()                 -> void;
    auto show()                     -> void;
private: // functions
    auto generateRow()              -> void;
    auto fillEmptyCells()           -> void;
    auto assignUniqueSets()         -> void;
    auto createVerticalWalls(int)   -> void;
    auto createHorizontalWalls(int) -> void;
    auto prepareNewLine(int)           -> void;
    auto mergeSets(int, int)        -> void;
    auto getRoot(int)               -> int;
    auto random(int, int)           -> int;

private: // variables
    Matrix vertical_walls;   /* vertical   - right boarder of cell */
    Matrix horizontal_walls; /* horizontal - bottom boarder of cell */

    std::unordered_map<int, int> parent; // TODO: move this to local variable
    std::vector<int> line;     // TODO: move this to local varibale

    static constexpr int kEmptyCell = 0;
    size_t rows = 0, collumns = 0;
    int set_counter = 1;
};
