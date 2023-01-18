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

void MazeGenerator::mergeSets(int x, int y) {
    line[y] = line[x];
}

void MazeGenerator::fillEmptyCells() {
    line.clear();
    line.assign(collumns, kEmptyCell);
}

void MazeGenerator::assignUniqueSets() {
    for (int i = 0; i + 1 < collumns; ++i) {
        if (line[i] == kEmptyCell) {
            line[i] = set_counter++;
        }
    }
}

void MazeGenerator::createVerticalWalls(int row) {
    for (int i = 0; i + 2 < collumns; ++i) {
        bool is_put_wall = randomChoice();
        if (line[i] == line[i + 1] || is_put_wall) {
            line[i + 1] = set_counter++;
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
        createHorizontalWalls(i);
        prepareNewLine();
   }
}


