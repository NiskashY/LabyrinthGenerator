#pragma once

#include "../maze/maze.h"

#include <QMainWindow>
#include <QRect>
#include <QPainter>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MazeUi {
public:
    MazeUi() = default;

    auto create(const MazeGenerator&, Ui::MainWindow*) -> void;
    auto draw(const MazeGenerator&, QLabel*) const -> void;
    auto clear(Ui::MainWindow*) -> void;
};