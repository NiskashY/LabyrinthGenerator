#pragma once

#include <random>
#include <unordered_map>

#include "matrix.h"

auto random(int, int) -> int;

class MazeGenerator {
public:

    MazeGenerator() = default;

    explicit MazeGenerator(size_t, size_t);

    auto generate() -> void;
    auto show() const -> void;
    auto create(size_t, size_t) -> void;
    auto resize(size_t, size_t, int = 0) -> void;
    auto getRows() const -> size_t;
    auto getColumns() const -> size_t;

    auto get(size_t r, size_t c) const -> std::pair<bool, bool> {
        return {vertical_walls.isWallExist(r, c),
                horizontal_walls.isWallExist(r, c)};
    }

    auto getVData() const -> std::vector<std::vector<int>>;
    auto setVData(const std::vector<std::vector<int>>&) -> void;

    auto getHData() const -> std::vector<std::vector<int>>;
    auto setHData(const std::vector<std::vector<int>>&) -> void;

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
    VerticalMatrix vertical_walls;
    HorizontalMatrix horizontal_walls;

    std::unordered_map<int, int> parent; // TODO: move this to local variable
    std::vector<int> line;     // TODO: move this to local varibale

    static constexpr int kEmptyCell = 0;
    size_t rows = 0, columns = 0;
    int set_counter = 1;
};
