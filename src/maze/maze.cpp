#include "maze.h"

MazeGenerator::MazeGenerator(int rows_, int collumns_) {
    vertical_walls.resize(rows_, collumns_);
    vertical_walls.assignBoarderVertical();

    horizontal_walls.resize(rows_, collumns_);
    horizontal_walls.assignBoarderHorizontal();
    rows = vertical_walls.getRows();
    collumns = vertical_walls.getCollumns();
}

bool MazeGenerator::randomChoice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(false, true);
    return distrib(gen);
}

int MazeGenerator::GetRoot(int v) {
    if (parent.contains(v)) {
        return parent[v] = GetRoot(parent[v]);
    }
    return v;
}

void MazeGenerator::mergeSets(int x, int y) {
    parent[y] = GetRoot(x);
}

void MazeGenerator::fillEmptyCells() {
    line.clear();
    line.assign(collumns, kEmptyCell);
}

void MazeGenerator::assignUniqueSets() {
    parent.clear();
    for (int i = 0; i + 1 < collumns; ++i) {
        if (line[i] == kEmptyCell) {
            line[i] = set_counter++;
        }
        parent[line[i]] = line[i];
    }
}

void MazeGenerator::createVerticalWalls(int row) {
    for (int i = 0; i + 2 < collumns; ++i) {
        bool is_put_wall = randomChoice();
        int left  = GetRoot(line[i]);
        int right = GetRoot(line[i + 1]);
        if (left == right || is_put_wall) {
            parent[line[i + 1]] = set_counter++;
            vertical_walls.setWall(row, i + 1);
        } else {
            mergeSets(i, i + 1);
        }
    }
}

void MazeGenerator::createHorizontalWalls(int row) {
    
}

void MazeGenerator::generate() {
   fillEmptyCells(); 
   for (int i = 1; i + 1 < rows; ++i) {
        assignUniqueSets();
        createVerticalWalls(i);
        createHorizontalWalls(i); // TODO
        prepareNewLine();         // TODO
   }
}


