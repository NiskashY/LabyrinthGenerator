#include "find_path.h"

#include <QPainter>

QPoint normalise(QPixmap pix, const Maze& maze, QPointF p) {
    auto cell_h = pix.height() / maze.getRows();
    auto cell_w = pix.width() / maze.getColumns();
    return {int(p.x() / cell_h), int(p.y() / cell_w)};
}

QPointF extend(QPixmap pix, const Maze& maze, QPoint p) {
    auto cell_h = pix.height() / maze.getRows();
    auto cell_w = pix.width() / maze.getColumns();
    return {p.y() * cell_w + cell_w / 2., p.x() * cell_h + cell_h / 2.};
}

QPixmap printed::find_path(QPixmap mazeImage, const Maze &maze, QPointF src, QPointF dest) {
    // Normalise points
    auto p1 = normalise(mazeImage, maze, src);
    auto p2 = normalise(mazeImage, maze, dest);
    auto pathMatrix = maze.findPath(p1, p2);

    QPainter painter(&mazeImage);
    painter.setPen(QPen(Qt::green, 3));

    dest = extend(mazeImage, maze, p2);             // center before drawing

    while (p1 != p2) {
        auto turn = pathMatrix.get(p2.x(), p2.y());
        QPoint nxt = move_to_turn(p2, static_cast<Turn>(turn));
        QPointF nxt_extended = extend(mazeImage, maze, nxt);

        painter.drawLine(dest.x(), dest.y(),
                         nxt_extended.x(), nxt_extended.y());

        dest = nxt_extended;
        p2 = nxt;
    }

    return mazeImage;
}
