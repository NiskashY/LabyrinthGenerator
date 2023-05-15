#include "maze_ui.h"
#include "ui/ui_mainwindow.h"

auto MazeUi::create(const MazeGenerator& maze, Ui::MainWindow* ui) -> void {
    auto field = new QLabel();
    field->setObjectName("drawable_label");
    field->setProperty("field", "maze");
    field->setScaledContents(true);
    this->draw(maze, field);

    ui->mazeLayout->addWidget(field);
}

auto MazeUi::draw(const MazeGenerator& maze, QLabel* drawable_label) const -> void {
    int rows = maze.getRows();
    int columns = maze.getColumns();

    auto wHeight = drawable_label->rect().height();
    auto wWidth  = drawable_label->rect().width();

    double cellHeight = (double)wHeight / rows;
    double cellWidth  = (double)wWidth / columns;

    auto getCell = [&](int i, int j) {
        return std::tuple{
            j * cellWidth, i * cellHeight,
            (j + 1) * cellWidth, (i + 1) * cellHeight
        };
    };

    QPixmap pix(drawable_label->rect().size());
    pix.fill(Qt::black);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            QPainter painter(&pix);
            painter.setPen(QPen(Qt::white, 2));
            auto [x0, y0, x1, y1] = getCell(i, j);
            auto [isHorizontalWall, isVerticalWall] = maze.get(i, j);   // v -> h, h -> v; because of coordinate plane
            if (isVerticalWall) {
                painter.drawLine(x0, y1, x1, y1);
            }
            if (isHorizontalWall) {
                painter.drawLine(x1, y0, x1, y1);
            }
        }
    }

    drawable_label->setPixmap(pix);
}

void MazeUi::clear(Ui::MainWindow* ui) {
    QLayoutItem *child;
    while ((child = ui->mazeLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}
