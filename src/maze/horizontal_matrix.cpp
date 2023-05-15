#include "matrix.h"

HorizontalMatrix::HorizontalMatrix(size_t rows_, size_t columns_) : Matrix(rows_, columns_) {};

auto HorizontalMatrix::assignBorder() -> void {
    for (auto& cell : walls.back()) { // walls.back() -> last row
        cell = true;
    }
}
