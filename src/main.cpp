#include "ui/mainwindow.h"

#include <QApplication>
#include <QFile>

auto getStyleSheet() -> QString {
    QFile file(":/style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    return QLatin1String(file.readAll());
}

namespace file {
QString kSavedMazesDirPath;
QString kSavedBackgroundPresetsDirPath;
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    file::kSavedMazesDirPath = QApplication::applicationDirPath() + "/saved-mazes/";
    file::kSavedBackgroundPresetsDirPath = QApplication::applicationDirPath() + "/background-presets/";

    a.setStyleSheet(getStyleSheet());

    MainWindow w;
    w.show();

    return a.exec();
}
