#include "change_background_window.h"
#include "ui_change_background_window.h"

#include <flowlayout.h>

#include <QPushButton>
#include <QDirIterator>
#include <QString>
#include <QPixmap>

#include <iostream>

namespace file {
extern QString kSavedBackgroundPresetsDirPath;
}


ChangeBackgroundWindow::ChangeBackgroundWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBackgroundWindow)
{
    ui->setupUi(this);
    QDir qdir;
    if (!qdir.exists(file::kSavedBackgroundPresetsDirPath)) {
        qdir.mkdir(file::kSavedBackgroundPresetsDirPath);
    }

    QDirIterator it(file::kSavedBackgroundPresetsDirPath, {"*.jpg", "*.png"}, QDir::Files);
    ui->scrollAreaContents->setLayout(new FlowLayout());

    while (it.hasNext()) {   // the iterator is located before the first dir entry
        ui->scrollAreaContents->layout()->addWidget(createImageLabel(it.next()));
        it.next();
    }
}

ChangeBackgroundWindow::~ChangeBackgroundWindow()
{
    delete ui;
}

auto ChangeBackgroundWindow::createImageLabel(QString path) -> QLabel* {
    auto label = new QLabel;
    auto pix = QPixmap(path);
    pix = pix.scaled(QSize(200, 200));  // TODO: adaptive sizes
    label->setPixmap(pix);   // it.next() - return filePath to the next entry
    label_to_name[label] = path;
    return label;
}

// TODO: clickable label -> change event after clicked
// TODO: insert here maze_ui.h -> then change background
// TODO: pass as a parameters {maze, mazeUi} to regenerate bacgkround image

/*
    createFileWindow (this, [&] (QString path) {
        mazeUi.changeBackground(path, maze);
    }, "*.png *.jpg");

*/
