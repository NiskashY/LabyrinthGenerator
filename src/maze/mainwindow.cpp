#include <QtWidgets>
#include "mainwindow.h"
#include "maze.h"

int main(int argc, char *argv[]) {
    MazeGenerator gen(4, 4);
    gen.generate();

    gen.show();
    return 0;
}
