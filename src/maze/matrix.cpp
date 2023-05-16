#include "matrix.h"

Matrix::Matrix(size_t cnt_rows, size_t cnt_columns) {
    this->resize(cnt_rows, cnt_columns);
}

auto Matrix::resize(size_t cnt_rows, size_t cnt_columns, int val) -> void{
   rows_count = cnt_rows;
   columns_count = cnt_columns;
   walls.clear();
   walls.resize(rows_count, std::vector<int>(columns_count, val));
}

void Matrix::setData(std::vector<std::vector<int>> data) {
   std::swap(walls, data);
}

auto Matrix::getData() const -> std::vector<std::vector<int>> {
   return walls;
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


auto Matrix::isWallExist(size_t x, size_t y) const -> bool {
    return isBordersCorrect(x, y) && walls[x][y];
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
