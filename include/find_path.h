// Draw new image with finded path between
// two points


#pragma once

#include <QPixmap>
#include <maze.h>

namespace printed {
auto find_path(QPixmap, const Maze&, QPointF, QPointF) -> QPixmap;
}


