#include "matrix.h"

Matrix::Matrix(int cnt_rows, int cnt_collumns) {
    this->resize(cnt_rows, cnt_collumns);
}

void Matrix::resize(int cnt_rows, int cnt_collumns) {
   rows_count_ = cnt_rows + 1; 
   collumns_count_ = cnt_collumns + 1;
   walls.resize(rows_count_, std::vector<char>(collumns_count_));
}

int Matrix::getRows() const {
   return walls.size();
}

int Matrix::getCollumns() const {
    return (rows_count_ ? collumns_count_ : 0);
}  

bool Matrix::setWall(int x, int y) {
    if (x < 0 || x >= rows_count_ ||
        y < 0 || y >= collumns_count_ || walls[x][y]) {
        return false;
    }
    return walls[x][y] = true;
}

bool Matrix::isWallExist(int x, int y) {
    if (x < 0 || x >= rows_count_ || 
        y < 0 || y >= collumns_count_) {
        return false;
    }
    return walls[x][y];
}

void Matrix::assignBoarderHorizontal() {
    std::vector<int> rows_start = {0, rows_count_ - 1};
    for (auto& position : rows_start) {
        for (auto& cell : walls[position]) {
            cell = 1;
        }
    }
}

void Matrix::assignBoarderVertical() {
    std::vector<int> coll_start = {0, collumns_count_ - 1};
    for (auto& position : coll_start) {
        for (int i = 0; i < rows_count_; ++i) {
            walls[i][position] = 1;
        }
    }
}

