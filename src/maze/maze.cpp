#include "maze.h"

#include <queue>
#include <random>

namespace {
    auto random(int l, int r) -> int {  // [l, r]
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(l, r);
        return distrib(gen);
    }
}

Maze::Maze(size_t rows_, size_t columns_) {
    resize(rows_, columns_);
}

auto Maze::create(size_t rows, size_t columns) -> void {
    resize(rows, columns);
    generate();
}

auto Maze::show() const -> void {
    walls.show();
}

auto Maze::resize(size_t rows_, size_t columns_, int val) -> void {
    rows = rows_; columns = columns_;
    walls.resize(rows, columns, val);
}

auto Maze::getRows() const -> size_t {
    return rows;
}

auto Maze::getColumns() const -> size_t {
    return columns;
}

auto Maze::getData() const -> matrix_t {
    return walls.getData();
}

auto Maze::getRefData() const -> const matrix_t& {
    return walls.getRefData();
}

auto Maze::setData(const matrix_t& data) -> void {
    walls.setData(data);
    rows = walls.getRows();
    columns = walls.getColumns();
}

auto Maze::isHorizontalWall(size_t x, size_t y) const -> bool {
    return walls.isHorizontalWallExist(x, y);
}

auto Maze::isVerticallWall(size_t x, size_t y) const -> bool {
    return walls.isVerticalWallExist(x, y);
}


auto Maze::isSeparatedByWall(QPoint cur, QPoint nxt) const -> bool {
    switch(determine_turn(cur, nxt)) {
        case Turn::RIGHT:   return isVerticallWall(cur.x(), cur.y());
        case Turn::LEFT:    return isVerticallWall(nxt.x(), nxt.y());
        case Turn::UP:      return isHorizontalWall(nxt.x(), nxt.y());
        case Turn::DOWN:    return isHorizontalWall(cur.x(), cur.y());
        default: return false;
    }
}

auto Maze::findPath(QPoint src, QPoint dest) const -> Matrix {
    std::vector<int> row = {-1, 1, 0, 0};
    std::vector<int> col = {0, 0, -1, 1};

    Matrix ret{getRows(), getColumns(), Turn::NONE};

    std::queue<QPoint> q;
    q.push(src);
    ret.set(src.x(), src.y(), Turn::START);

    int x = 0;
    while (!q.empty() && ++x < 200) {
        auto point = q.front(); q.pop();

        for (int i = 0; i < (int)row.size(); ++i) {
            QPoint nxt{point.x() + row[i], point.y() + col[i]};

            if (ret.isBordersCorrect(nxt) &&
                ret.get(nxt.x(), nxt.y()) == Turn::NONE &&
                !isSeparatedByWall(point, nxt)) {
                q.push(nxt);
                ret.set(nxt.x(), nxt.y(), determine_turn(nxt, point));
                if (nxt == dest) {
                    break;
                }
            }
        }
    }

    return ret;
}

auto Maze::generate() -> void {
    fillEmptyCells();
    for (int i = 0; i + 1 < rows; ++i) {
        assignUniqueSets();
        createVerticalWalls(i);
        createHorizontalWalls(i);
        prepareNewLine(i);
    }
    addLastRow();
}

auto Maze::getRoot(int v) -> int {
    if (parent.contains(v) && parent[v] != v) {
        return parent[v] = getRoot(parent[v]);
    }
    return v;
}

auto Maze::mergeSets(int x, int y) -> void {
    parent[y] = getRoot(x);
}

auto Maze::fillEmptyCells() -> void {
    this->resize(rows, columns);
    set_counter = 1;
    line.assign(columns, kEmptyCell);
    parent.clear();
}

auto Maze::assignUniqueSets() -> void {
    parent.clear();
    for (int i = 0; i < columns; ++i) {
        if (line[i] == kEmptyCell) {
            line[i] = set_counter++;
        }
        parent[line[i]] = line[i];
    }
}

auto Maze::createVerticalWalls(int row) -> void {
    // if two near sets are identical or if random choice is true -> create wall on the right
    // else -> unite sets

    for (int i = 0; i + 1 < columns; ++i) {
        if (random(0, 1) || getRoot(line[i]) == getRoot(line[i + 1])) {
            walls.setVerticalWall(row, i);
        } else {
            mergeSets(line[i], line[i + 1]);
        }
    }
    walls.setVerticalWall(row, columns - 1); // place right wall in the last cell of the row

    for (int i = 0; i < columns; ++i) {
        line[i] = getRoot(line[i]);
    }
}

auto Maze::createHorizontalWalls(int row) -> void {
    // random choice to put wall or not
    // if every cell in current set with bottom wall ->
    // -> randomly choose to remove bottom wall

    for (int i = 0; i < columns; ++i) {
        if (random(0, 1)) {
            walls.setHorizontalWall(row, i);
        }
    }

    int left = 0, right = 0;
    while (left < columns) {
        int walls_bottom_count = 0;
        while (right < columns && getRoot(line[right]) == getRoot(line[left])) {
            walls_bottom_count += walls.isHorizontalWallExist(row, right);
            right += 1;
        }

        int total_cells = right - left;
        if (walls_bottom_count == total_cells) {
            int pos_to_override = left + random(0, total_cells - 1);
            walls.removeHorizontalWall(row, pos_to_override);
        }

        left = right;
    }
}

auto Maze::prepareNewLine(int row) -> void {
    for (int i = 0; i < columns; ++i) {
        if (walls.isHorizontalWallExist(row, i)) {
            line[i] = kEmptyCell;
        }
    }
}

auto Maze::addLastRow() -> void {
    // if set[i] != set[i + 1] && vertical wall is set
    // than i need to remove current right border

    int i = (int)rows - 1;  // last row index
    assignUniqueSets();
    createVerticalWalls(i);

    for (int j = 0; j + 1 < columns; ++j) {
        bool is_right_wall = walls.isVerticalWallExist(i, j);
        if (is_right_wall && getRoot(line[j]) != getRoot(line[j + 1])) {
            walls.removeVerticalWall(i, j);
            mergeSets(line[j], line[j + 1]);
        }
    }
}
