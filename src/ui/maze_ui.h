#pragma once

#include "../maze/maze.h"

#include <QMainWindow>
#include <QRect>
#include <QPainter>
#include <QLabel>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MazeUi {
public:
    MazeUi(Ui::MainWindow* ui_);

    auto create(const MazeGenerator&) -> void;
    auto draw(const MazeGenerator&, QLabel*) const -> void;
    auto clear() -> void;

    auto open(QString, MazeGenerator&) -> void;
    auto save(const MazeGenerator&, const QPixmap&) -> QString;

private:
    Ui::MainWindow* ui = nullptr;
    auto saveMazeData(const MazeGenerator&, QString) -> void;
    auto saveMazeImage(const QPixmap&, QString) -> void;
};
