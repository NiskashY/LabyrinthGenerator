#include <vector>

class Matrix { 
private:
    std::vector<std::vector<char>> walls;
    int rows_count_ = 0;
    int collumns_count_ = 0;

public:
    Matrix() = default;

    explicit Matrix(int, int);

    void resize(int, int);

    int getRows() const;
    int getCollumns() const;

    bool setWall(int, int);
    bool isWallExist(int, int);
    void assignBoarderVertical();
    void assignBoarderHorizontal();
};
