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

void MainWindow::on_generateButton_clicked() {
    if (!ui->inputHeight->text().isEmpty() &&
        !ui->inputWidth->text().isEmpty()) {
        maze.create(ui->inputHeight->text().toInt(), // TODO:
                    ui->inputWidth->text().toInt()); // TODO:
    } else {
        maze.generate();
    }
    mazeUi.clear(ui);
    mazeUi.create(maze, ui);
}

void MainWindow::on_openButton_clicked() {
    QFileDialog dirWindow(this);
    dirWindow.setWindowTitle("Select Maze File");
    dirWindow.setFileMode(QFileDialog::ExistingFile);
    dirWindow.setNameFilter("Maze files (*.txt)");
    dirWindow.setDirectory(QApplication::applicationDirPath());

    if (dirWindow.exec()) {
        QStringList selectedFiles = dirWindow.selectedFiles();
        for (const auto& file_path : selectedFiles) {
            mazeUi.open(file_path, maze);
            mazeUi.clear(ui);
            mazeUi.create(maze, ui);
            ui->inputHeight->setText(QString::number(maze.getRows()));
            ui->inputWidth->setText(QString::number(maze.getColumns()));
        }
    }
}

void MainWindow::on_saveButton_clicked() {
    mazeUi.save(maze);
}


