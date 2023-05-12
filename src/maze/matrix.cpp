#include "matrix.h"

Matrix::Matrix(size_t cnt_rows, size_t cnt_collumns) {
    this->resize(cnt_rows, cnt_collumns);
}

auto Matrix::resize(size_t cnt_rows, size_t cnt_collumns) -> void{
   rows_count = cnt_rows;
   collumns_count = cnt_collumns;
   walls.resize(rows_count, std::vector<char>(collumns_count));
}

auto Matrix::getRows() const -> size_t {
   return rows_count;
}

auto Matrix::getCollumns() const -> size_t {
    return collumns_count;
}

auto Matrix::setWall(size_t x, size_t y) -> bool {
    return isBoardersCorrect(x, y) && (walls[x][y] = true);
}

auto Matrix::removeWall(size_t x, size_t y) -> bool {
    return isBoardersCorrect(x, y) && !(walls[x][y] = false);
}


auto Matrix::isWallExist(size_t x, size_t y) -> bool {
    return isBoardersCorrect(x, y) && walls[x][y];
}

auto Matrix::assignBoarderHorizontal() -> void {
    for (auto& cell : walls.back()) { // walls.back() -> last row
        cell = true;
    }
}

auto Matrix::assignBoarderVertical() -> void {
    const int j = (int)collumns_count - 1;
    for (int i = 0; i < rows_count; ++i) {
        walls[i][j] = true;
    }
}

auto Matrix::isBoardersCorrect(size_t x, size_t y) const -> bool {
    return x < rows_count && y < collumns_count;
}


auto Matrix::show() -> void {
    for (auto& row : walls) {
        for (auto& item : row) {
            std::cout << char(item + '0') << ' ';
        }
        std::cout << std::endl;
    }
}
