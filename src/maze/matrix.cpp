#include "matrix.h"

Matrix::Matrix(size_t cnt_rows, size_t cnt_columns) {
    this->resize(cnt_rows, cnt_columns);
}

auto Matrix::resize(size_t cnt_rows, size_t cnt_columns) -> void{
   rows_count = cnt_rows;
   columns_count = cnt_columns;
   walls.clear();
   walls.resize(rows_count, std::vector<char>(columns_count));
}

auto Matrix::getRows() const -> size_t {
   return rows_count;
}

auto Matrix::getColumns() const -> size_t {
    return columns_count;
}

auto Matrix::setWall(size_t x, size_t y) -> bool {
    return isBordersCorrect(x, y) && (walls[x][y] = true);
}

auto Matrix::removeWall(size_t x, size_t y) -> bool {
    return isBordersCorrect(x, y) && !(walls[x][y] = false);
}


auto Matrix::isWallExist(size_t x, size_t y) -> bool {
    return isBordersCorrect(x, y) && walls[x][y];
}

auto Matrix::assignBorderHorizontal() -> void {
    for (auto& cell : walls.back()) { // walls.back() -> last row
        cell = true;
    }
}

auto Matrix::assignBorderVertical() -> void {
    const int j = (int)columns_count - 1;
    for (int i = 0; i < rows_count; ++i) {
        walls[i][j] = true;
    }
}

auto Matrix::isBordersCorrect(size_t x, size_t y) const -> bool {
    return x < rows_count && y < columns_count;
}


auto Matrix::show() -> void {
    for (auto& row : walls) {
        for (auto& item : row) {
            std::cout << char(item + '0') << ' ';
        }
        std::cout << std::endl;
    }
}
