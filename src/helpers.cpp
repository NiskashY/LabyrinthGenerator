#include "helpers.h"

Turn determine_turn(QPoint p1, QPoint p2) {    // from p1 to p2
    if (p2.y() == p1.y() + 1)      return Turn::RIGHT;
    else if (p2.y() == p1.y() - 1) return Turn::LEFT;
    else if (p2.x() == p1.x() + 1) return Turn::DOWN;
    else if (p2.x() == p1.x() - 1) return Turn::UP;
    return Turn::NONE;
}

QPoint move_to_turn(QPoint p, Turn turn) {
    switch(turn) {
        case Turn::LEFT:  return {p.x(), p.y() - 1};
        case Turn::RIGHT: return {p.x(), p.y() + 1};
        case Turn::UP:    return {p.x() - 1, p.y()};
        case Turn::DOWN:  return {p.x() + 1, p.y()};
        default:          return p;
    }
}
