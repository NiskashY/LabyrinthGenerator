#pragma once

#include <QMainWindow>

#include "maze_ui.h"
#include "../maze/maze.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_generateButton_clicked();
    void on_openButton_clicked();
    void on_saveButton_clicked();
    void on_changeBackground_clicked();
    void on_resetBackgroundButton_clicked();

private:
    Ui::MainWindow *ui;
    MazeUi mazeUi;
    MazeGenerator maze;
};
