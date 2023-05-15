#include "matrix.h"

#include <functional>

VerticalMatrix::VerticalMatrix(size_t rows_, size_t columns_) : Matrix(rows_, columns_) {};

auto VerticalMatrix::assignBorder() -> void {
    const int j = (int)columns_count - 1;
    for (int i = 0; i < rows_count; ++i) {
        walls[i][j] = true;
    }
}
