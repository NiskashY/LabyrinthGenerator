#pragma once

#include <QFileDialog>
#include <QApplication>

template <class Func>
void createFileWindow(QWidget* parent, Func windowFunction, QString fileTypes = "") {
    QFileDialog dirWindow(parent);
    dirWindow.setWindowTitle("Select Files");
    dirWindow.setFileMode(QFileDialog::ExistingFile);
    dirWindow.setNameFilter("files (" + fileTypes + ")");

    if (dirWindow.exec()) {
        for (const auto& file_path : dirWindow.selectedFiles()) {
            windowFunction(file_path);
        }
    }
}
