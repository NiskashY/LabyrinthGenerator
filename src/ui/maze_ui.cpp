#include "maze_ui.h"
#include "file_handler.h"
#include "ui/ui_mainwindow.h"

#include <QDir>

namespace file {
extern QString kSavedMazesDirPath;
};

auto ImageSelector::set(QString newFileName) -> void {
    fileName = newFileName;
    isSelected = true;
}

auto ImageSelector::reset() -> void {
    isSelected = false;
}

MazeUi::MazeUi(Ui::MainWindow* ui_) : ui(ui_) {

}

auto MazeUi::create(const MazeGenerator& maze) -> void {
    clear();
    auto field = new QLabel();
    field->setObjectName("drawable_label");
    field->setProperty("field", "maze");
    field->setScaledContents(true);
    draw(maze, field);

    ui->mazeLayout->addWidget(field);
}

auto MazeUi::getMazeFieldPixmap(QLabel* drawable_label) -> QPixmap {
    QPixmap pix(drawable_label->rect().size());
    pix.fill(Qt::black);
    if (image.isSelected) {
        pix.load(image.fileName);
        return pix.scaled(drawable_label->rect().size());
    }
    return pix;
}

auto MazeUi::draw(const MazeGenerator& maze, QLabel* drawable_label) -> void {
    const auto cellHeight = (double)drawable_label->rect().height() / maze.getRows();
    const auto cellWidth  = (double)drawable_label->rect().width()  / maze.getColumns();

    auto getCell = [&](int i, int j) {
        return std::tuple{
            j * cellWidth, i * cellHeight,
            (j + 1) * cellWidth, (i + 1) * cellHeight
        };
    };

    auto pix = getMazeFieldPixmap(drawable_label);
    QPainter painter(&pix);
    painter.setPen(QPen(Qt::white, 2));

    for (size_t i = 0; i < maze.getRows(); ++i) {
        for (size_t j = 0; j < maze.getColumns(); ++j) {
            auto [x0, y0, x1, y1] = getCell(i, j);
            if (maze.isHorizontalWall(i, j)) {
                painter.drawLine(x0, y1, x1, y1);
            }
            if (maze.isVerticallWall(i, j)) {
                painter.drawLine(x1, y0, x1, y1);
            }
        }
    }

    drawable_label->setPixmap(pix);
}

auto MazeUi::changeBackground(QString fileName, const MazeGenerator& maze) -> void {
    image.set(fileName);
    create(maze);
}

auto MazeUi::resetBackground(const MazeGenerator& maze) -> void {
    image.reset();
    create(maze);
}

void MazeUi::clear() {
    QLayoutItem *child;
    while ((child = ui->mazeLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}

auto MazeUi::open(QString file_path, MazeGenerator& maze) -> void {
    file::Handler fhandler(file_path);
    maze.setData(fhandler.read());
}

auto MazeUi::save(const MazeGenerator& maze, QLabel* label) -> QString {
    auto name = file::createFileName();

    QDir qdir;
    if (!qdir.exists(file::kSavedMazesDirPath)) {
        qdir.mkdir(file::kSavedMazesDirPath);
    }

    auto dir_path = file::kSavedMazesDirPath + name + "/";
    qdir.mkdir(dir_path);

    saveMazeImage(label->pixmap(), dir_path + name + ".png");
    saveMazeData(maze, dir_path + name + ".txt");

    return dir_path;
}

auto MazeUi::saveMazeData(const MazeGenerator& maze, QString file_path) -> void {
    file::Handler fhandler(file_path);
    fhandler.write(maze.getRefData());
}

auto MazeUi::saveMazeImage(const QPixmap& pix, QString file_path) -> void {
    QFile file(file_path);
    file.open(QIODevice::WriteOnly);
    pix.save(&file, "PNG");
}
