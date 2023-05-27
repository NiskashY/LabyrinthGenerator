#pragma once

#include "../maze/maze.h"

#include <QMainWindow>
#include <QRect>
#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QLayoutItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct ImageSelector {
    bool isSelected = false;
    QString fileName;

    auto set(QString newFileName) {
        fileName = newFileName;
        isSelected = true;
    }
};

class MazeUi {
public:
    MazeUi(Ui::MainWindow* ui_);

    auto create(const MazeGenerator&) -> void;
    auto draw(const MazeGenerator&, QLabel*) -> void;
    auto clear() -> void;
    auto changeBackground(QString, const MazeGenerator&, QLabel*) -> void;

    auto open(QString, MazeGenerator&) -> void;
    auto save(const MazeGenerator&, QLabel*) -> QString;

private: // funcitons
    auto saveMazeData(const MazeGenerator&, QString) -> void;
    auto saveMazeImage(const QPixmap&, QString) -> void;
    auto getMazeFieldPixmap(QLabel*) -> QPixmap;

private:
    Ui::MainWindow* ui = nullptr;
    ImageSelector image;
};
