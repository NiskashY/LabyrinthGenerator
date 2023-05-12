#include "maze.h"

MazeGenerator::MazeGenerator(size_t rows_, size_t collumns_) : rows(rows_), collumns(collumns_) {
    vertical_walls.resize(rows, collumns);
    vertical_walls.assignBoarderVertical();

    horizontal_walls.resize(rows, collumns);
    horizontal_walls.assignBoarderHorizontal();
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
    line.assign(collumns, kEmptyCell);
    parent.clear();
}

auto MazeGenerator::assignUniqueSets() -> void {
    parent.clear();
    for (int i = 0; i < collumns; ++i) {
        if (line[i] == kEmptyCell) {
            line[i] = set_counter++;
        }
        parent[line[i]] = line[i];
    }
}

auto MazeGenerator::createVerticalWalls(int row) -> void {
    // if two near sets are identical or if random choice is true -> create wall on the right
    // else -> unite sets

    for (int i = 0; i + 1 < collumns; ++i) {
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

    for (int i = 0; i < collumns; ++i) {
        line[i] = getRoot(line[i]);
    }
}

auto MazeGenerator::createHorizontalWalls(int row) -> void {
    // random choice to put wall or not
    // if every cell in current set with bootom wall ->
    // -> randomly chouse to remove bottom wall
    for (int i = 0; i < collumns; ++i) {
        if (random(0, 1)) {
            horizontal_walls.setWall(row, i);
        }
    }

    int left = 0, right = 0;
    while (left < collumns) {
        int walls_bottom_count = 0;
        while (right < collumns && line[right] == line[left]) {
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
    for (int i = 0; i < collumns; ++i) {
        if (horizontal_walls.isWallExist(row, i)) {
            line[i] = kEmptyCell;
        }
    }
}

auto MazeGenerator::generate() -> void {
    fillEmptyCells();
    for (int i = 0; i + 1 < rows; ++i) {
        assignUniqueSets();
        createVerticalWalls(i);
        createHorizontalWalls(i);
        prepareNewLine(i);
   }
}

auto MazeGenerator::show() -> void {
    std::cout << "\nvertical: " << std::endl;
    vertical_walls.show();
    std::cout << "\nhorizontal: " << std::endl;
    horizontal_walls.show();
}

