#include "maze_ui.h"
#include "file_handler.h"
#include "ui/ui_mainwindow.h"

namespace file {
extern QString kSavedMazesDirPath;
};

auto MazeUi::create(const MazeGenerator& maze, Ui::MainWindow* ui) -> void {
    auto field = new QLabel();
    field->setObjectName("drawable_label");
    field->setProperty("field", "maze");
    field->setScaledContents(true);
    this->draw(maze, field);

    ui->mazeLayout->addWidget(field);
}

auto MazeUi::draw(const MazeGenerator& maze, QLabel* drawable_label) const -> void {
    const double cellHeight = (double)drawable_label->rect().height() / maze.getRows();
    const double cellWidth  = (double)drawable_label->rect().width() / maze.getColumns();

    auto getCell = [&](int i, int j) {
        return std::tuple{
            j * cellWidth, i * cellHeight,
            (j + 1) * cellWidth, (i + 1) * cellHeight
        };
    };

    QPixmap pix(drawable_label->rect().size());
    pix.fill(Qt::black);

    QPainter painter(&pix);
    painter.setPen(QPen(Qt::white, 2));

    for (size_t i = 0; i < maze.getRows(); ++i) {
        for (size_t j = 0; j < maze.getColumns(); ++j) {
            auto [x0, y0, x1, y1] = getCell(i, j);
            auto [isHorizontalWall, isVerticalWall] = maze.get(i, j);   // v -> h, h -> v; because of coordinate plane
            if (isVerticalWall) {
                painter.drawLine(x0, y1, x1, y1); // segfault ? mazeUi.open
            }
            if (isHorizontalWall) {
                painter.drawLine(x1, y0, x1, y1); // segfault ? mazeUi.open
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

auto MazeUi::open(QString file_path, MazeGenerator& maze) -> void {
    auto file_name = file::getFileNameFromPath(file_path);
    QFile::copy(file_path, file::kSavedMazesDirPath + file_name);
    file::Handler fhandler(file_path);
    auto [v_data, h_data] = fhandler.read();
    maze.setVData(v_data);
    maze.setHData(h_data);
}

#include <QFile>
#include <cassert>

auto MazeUi::save(const MazeGenerator& maze) -> void {
    auto file_name = file::createFileName();
    auto file_path = file::kSavedMazesDirPath + file_name;

    file::Handler fhandler(file_path);
    fhandler.write(maze.getRefVData(), maze.getRefHData());
}
