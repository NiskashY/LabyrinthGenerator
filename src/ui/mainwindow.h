#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QtWidgets>
#include <QGridLayout>
#include <QPixmap>

#include "../maze/maze.h"
#define STR_NAME(x) #x

class MainWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override = default;

private:  // functions
    auto createMainLayout() const -> QVBoxLayout*;
    auto createParametersLayout() const -> QLayout*;
    auto createOpenSaveLayout() const -> QLayout*;
    auto createMazeLayout() const -> QLayout*;
    auto createGenerateButton() const ->QPushButton*;
    auto setupLabyrinthUi() -> void;
    auto createCellQss(bool, int, int, bool) const -> QString;  // bottom, top, left, right

    auto hide(QGridLayout *gl, size_t row, size_t col) const -> void;

private:
    MazeGenerator maze;
};
