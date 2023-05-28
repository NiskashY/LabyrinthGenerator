#include "matrix.h"

Matrix::Matrix(size_t cnt_rows, size_t cnt_columns) {
    this->resize(cnt_rows, cnt_columns);
}

auto Matrix::resize(size_t cnt_rows, size_t cnt_columns, int val) -> void{
   rows_count = cnt_rows;
   columns_count = cnt_columns;
   walls.clear();
   walls.resize(rows_count, matrix_row_t(columns_count, val));
}

auto Matrix::setData(matrix_t data) -> void {
   std::swap(walls, data);
   rows_count = walls.size();
   columns_count = walls.front().size();
}

auto Matrix::getData() const -> matrix_t {
   return walls;
}

auto Matrix::getRefData() const -> const matrix_t& {
   return walls;
}

auto Matrix::getRows() const -> size_t {
   return rows_count;
}

auto Matrix::getColumns() const -> size_t {
    return columns_count;
}

auto Matrix::setVerticalWall(size_t x, size_t y) -> bool {
    return isBordersCorrect(x, y) && (walls[x][y] |= 0b01);
}

auto Matrix::setHorizontalWall(size_t x, size_t y) -> bool {
    return isBordersCorrect(x, y) && (walls[x][y] |= 0b10);
}

auto Matrix::removeVerticalWall(size_t x, size_t y) -> bool {
    return isBordersCorrect(x, y) && !(walls[x][y] &= ~(0b01));
}

auto Matrix::removeHorizontalWall(size_t x, size_t y) -> bool {
    return isBordersCorrect(x, y) && !(walls[x][y] &= ~(0b10));
}

auto Matrix::isVerticalWallExist(size_t x, size_t y) const -> bool {
    return isBordersCorrect(x, y) &&
           (walls[x][y] & 0b01) != 0;
}

auto Matrix::isHorizontalWallExist(size_t x, size_t y) const -> bool {
    return isBordersCorrect(x, y) &&
           (walls[x][y] & 0b10) != 0;
}

auto Matrix::isBordersCorrect(size_t x, size_t y) const -> bool {
    return x < rows_count && y < columns_count;
}

auto Matrix::show() const -> void {
    for (auto& row : walls) {
        for (auto& cell : row) {
            std::cout << int(cell) << ' ';
        }
        std::cout << std::endl;
    }
}
