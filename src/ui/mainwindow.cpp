#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Maze Generator");
    maze.create(10, 10);
    mazeUi.create(maze, ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    if (!ui->inputHeight->text().isEmpty() &&
        !ui->inputWidth->text().isEmpty()) {
        maze.create(ui->inputHeight->text().toInt(),
                    ui->inputWidth->text().toInt());
    } else {
        maze.generate();
    }
    mazeUi.clear(ui);
    mazeUi.create(maze, ui);
}

