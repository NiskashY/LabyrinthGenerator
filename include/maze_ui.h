#pragma once

#include "maze.h"

#include <QMainWindow>
#include <QRect>
#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QLayoutItem>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct ImageSelector {
    constexpr static auto kDefaultFileName = ":/style/background-preset/checked_dark_blue.jpg";
    bool isSelected = false;
    QString fileName = kDefaultFileName;

    auto set(QString newFileName) -> void;
    auto reset() -> void;
};

class MazeUi {
public:
    MazeUi(Ui::MainWindow* ui_);

    auto create(const Maze&) -> void;
    auto draw(const Maze&, QLabel*) -> void;
    auto clear() -> void;
    auto changeBackground(QString, const Maze&) -> void;
    auto resetBackground(const Maze&) -> void;

    auto open(QString, Maze&) -> void;
    auto save(const Maze&, QLabel*) -> QString;

private: // funcitons
    auto saveMazeData(const Maze&, QString) -> void;
    auto saveMazeImage(const QPixmap&, QString) -> void;
    auto getMazeFieldPixmap(QLabel*) -> QPixmap;

private:
    Ui::MainWindow* ui = nullptr;
    ImageSelector image;
};
