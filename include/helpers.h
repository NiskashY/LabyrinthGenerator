#pragma once

#include <vector>
#include <QPoint>

using matrix_data_t = int;
using matrix_row_t = std::vector<matrix_data_t>;
using matrix_t = std::vector<matrix_row_t>;

enum Turn {
    START, NONE, LEFT, RIGHT, UP, DOWN
//  0       1     2     3     4   5
};

Turn determine_turn(QPoint, QPoint);
QPoint move_to_turn(QPoint, Turn);
