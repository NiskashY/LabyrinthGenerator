#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"

#include <QApplication>
#include <QValidator>
#include <QMessageBox>

#include "change_background_window.h"
#include "file_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), mazeUi(ui)
{
    ui->setupUi(this);
    ui->inputHeight->setValidator(new QIntValidator(0, 100, this));
    ui->inputWidth->setValidator(new QIntValidator(0, 100, this));
    setWindowTitle("Maze Generator");
    maze.create(10, 10);
    mazeUi.create(maze);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked() {
    if (!ui->inputHeight->text().isEmpty() &&
        !ui->inputWidth->text().isEmpty()) {
        maze.resize(ui->inputHeight->text().toInt(),
                    ui->inputWidth->text().toInt());
    }

    maze.generate();
    mazeUi.create(maze);
}

void MainWindow::on_saveButton_clicked() {
    auto pix_label = this->findChild<QLabel*>("drawable_label");
    auto savedDirPath = mazeUi.save(maze, pix_label);
    QMessageBox msgBox;
    msgBox.setText("Saved into directory:" + savedDirPath);
    msgBox.exec();
}

void MainWindow::on_openButton_clicked() {
    createFileWindow (this, [&](QString path) {
        mazeUi.open(path, maze);
        mazeUi.create(maze);
        ui->inputHeight->setText(QString::number(maze.getRows()));
        ui->inputWidth->setText(QString::number(maze.getColumns()));
    }, "*.txt");
}

void MainWindow::on_changeBackground_clicked() {
    // TODO: implement default themes

    hide();
    {
        ChangeBackgroundWindow changeBackground;
        changeBackground.exec();
    }
    show();
}

void MainWindow::on_resetBackgroundButton_clicked() {
    mazeUi.resetBackground(maze);
}

