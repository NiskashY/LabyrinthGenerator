#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"

#include <QValidator>
#include <QMessageBox>

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
    createFileWindow ([&](QString path) {
        mazeUi.open(path, maze);
        mazeUi.create(maze);
        ui->inputHeight->setText(QString::number(maze.getRows()));
        ui->inputWidth->setText(QString::number(maze.getColumns()));
    }, "*.txt");
}

void MainWindow::on_changeBackground_clicked() {
    createFileWindow ([&] (QString path) {
        mazeUi.changeBackground(path, maze);
    }, "*.png, *.jpg");
}

void MainWindow::on_resetBackgroundButton_clicked() {
    mazeUi.resetBackground(maze);
}

void MainWindow::createFileWindow(auto windowFunction, QString fileTypes) {
    QFileDialog dirWindow(this);
    dirWindow.setWindowTitle("Select Maze File");
    dirWindow.setFileMode(QFileDialog::ExistingFile);

    dirWindow.setNameFilter("files (" + fileTypes + ")");
    dirWindow.setDirectory(QApplication::applicationDirPath());

    if (dirWindow.exec()) {
        for (const auto& file_path : dirWindow.selectedFiles()) {
            windowFunction(file_path);
        }
    }
}
