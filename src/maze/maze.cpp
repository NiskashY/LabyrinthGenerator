#include "maze.h"

MazeGenerator::MazeGenerator(size_t rows_, size_t columns_) {
    this->resize(rows_, columns_);
}

auto MazeGenerator::generate() -> void {
    fillEmptyCells();
    for (int i = 0; i + 1 < rows; ++i) {
        assignUniqueSets();
        createVerticalWalls(i);
        createHorizontalWalls(i);
        prepareNewLine(i);
    }
    addLastRow();
}

auto MazeGenerator::create(size_t rows, size_t columns) -> void {
    this->resize(rows, columns);
    this->generate();
}

auto MazeGenerator::show() const -> void {
    std::cout << "\nvertical: " << std::endl;
    vertical_walls.show();
    std::cout << "\nhorizontal: " << std::endl;
    horizontal_walls.show();
}

auto MazeGenerator::resize(size_t rows_, size_t columns_) -> void {
    rows = rows_; columns = columns_;

    vertical_walls.resize(rows, columns);
    vertical_walls.assignBorderVertical();

    horizontal_walls.resize(rows, columns);
    horizontal_walls.assignBorderHorizontal();
}


auto MazeGenerator::getRows() const -> size_t {
    return rows;
}

auto MazeGenerator::getColumns() const -> size_t {
    return columns;
}
auto MazeGenerator::random(int l, int r) -> int {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(l, r);
    return distrib(gen);
}

auto MazeGenerator::getRoot(int v) -> int {
    if (parent.contains(v) && parent[v] != v) {
        return parent[v] = getRoot(parent[v]);
    }
    return v;
}

auto MazeGenerator::mergeSets(int x, int y) -> void {
    parent[y] = getRoot(x);
}

auto MazeGenerator::fillEmptyCells() -> void {
    set_counter = 1;
    line.assign(columns, kEmptyCell);
    parent.clear();
}

auto MazeGenerator::assignUniqueSets() -> void {
    parent.clear();
    for (int i = 0; i < columns; ++i) {
        if (line[i] == kEmptyCell) {
            line[i] = set_counter++;
        }
        parent[line[i]] = line[i];
    }
}

auto MazeGenerator::createVerticalWalls(int row) -> void {
    // if two near sets are identical or if random choice is true -> create wall on the right
    // else -> unite sets

    for (int i = 0; i + 1 < columns; ++i) {
        bool is_put_wall = random(0, 1);
        int left  = getRoot(line[i]);
        int right = getRoot(line[i + 1]);
        if (left == right || is_put_wall) {
            if (left == right) {
                parent[line[i + 1]] = set_counter++;
            }
            vertical_walls.setWall(row, i);
        } else {
            mergeSets(line[i], line[i + 1]);
        }
    }

    for (int i = 0; i < columns; ++i) {
        line[i] = getRoot(line[i]);
    }
}

auto MazeGenerator::createHorizontalWalls(int row) -> void {
    // random choice to put wall or not
    // if every cell in current set with bottom wall ->
    // -> randomly choose to remove bottom wall
    for (int i = 0; i < columns; ++i) {
        if (random(0, 1)) {
            horizontal_walls.setWall(row, i);
        }
    }

    int left = 0, right = 0;
    while (left < columns) {
        int walls_bottom_count = 0;
        while (right < columns && line[right] == line[left]) {
            walls_bottom_count += horizontal_walls.isWallExist(row, right);
            right += 1;
        }

        int total_cells = right - left;
        if (walls_bottom_count == total_cells) {
            int&& pos_to_override = left + random(0, total_cells - 1);
            horizontal_walls.removeWall(row, pos_to_override);
        }

        left = right;
    }
}

auto MazeGenerator::prepareNewLine(int row) -> void {
    for (int i = 0; i < columns; ++i) {
        if (horizontal_walls.isWallExist(row, i)) {
            line[i] = kEmptyCell;
        }
    }
}

auto MazeGenerator::addLastRow() -> void {
    // if set[i] != set[i + 1] && horizontal[i] is set
    // than i need to remove current right border

    int i = (int)rows - 1;  // last row index
    assignUniqueSets();
    createVerticalWalls(i);

    for (int j = 0; j + 1 < columns; ++j) {
        const bool is_right_wall = vertical_walls.isWallExist(i, j);
        if (is_right_wall && getRoot(line[j]) != getRoot(line[j + 1])) {
            vertical_walls.removeWall(i, j);
            mergeSets(line[j], line[j + 1]);
        }
    }
}
