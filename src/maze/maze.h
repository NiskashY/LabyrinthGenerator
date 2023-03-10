#include <iostream>
#include <random>
#include <map>
#include <functional>

#include "matrix.h"

class MazeGenerator {
public: 
    explicit MazeGenerator(int, int);
    void generate();

private: // functions
    void generateRow();
    bool randomChoice();
    void fillEmptyCells();
    void assignUniqueSets();
    void createVerticalWalls(int);
    void createHorizontalWalls(int);
    void prepareNewLine();
    void mergeSets(int, int);
    int GetRoot(int);

private: // variables
    Matrix vertical_walls,   /* vertical   - left boarder of cell */
           horizontal_walls; /* horizontal - upper bouardre of cell */

    std::map<int, int> parent;
    std::vector<int> line;
    const int kEmptyCell = 0;
    int rows = 0, collumns = 0;
    int set_counter = 1;
};
