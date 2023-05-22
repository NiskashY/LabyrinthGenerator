#pragma once

#include <QMainWindow>
#include <QFileDialog>

#include <QApplication>
#include <QStringList>

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

private:
    MazeUi mazeUi;
    MazeGenerator maze;

    Ui::MainWindow *ui;
};
