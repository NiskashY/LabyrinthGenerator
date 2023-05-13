#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>

#include "../maze/maze.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override = default;

    auto createParametersLayout() const -> QLayout*;
    auto createOpenSaveLayout() const -> QLayout*;
    auto setupLabyrinthUi() -> void;
private:

    auto createCellQss(bool, int, int, bool) const -> QString;  // bottom, top, left, right

    std::shared_ptr<QPushButton> button;
    std::shared_ptr<QTextBrowser> textBrowser;

    MazeGenerator maze;
};
