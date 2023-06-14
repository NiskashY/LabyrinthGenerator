#include "./ui/mainwindow.h"

#include <QApplication>
#include <QFile>

auto getStyleSheet() -> QString {
    QFile file(":/style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    return QLatin1String(file.readAll());
}

namespace file {
    QString kSavedMazesDirPath;
};

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    QApplication a(argc, argv);
    file::kSavedMazesDirPath = QApplication::applicationDirPath() + "/saved-mazes/";

    a.setStyleSheet(getStyleSheet());

    MainWindow w;
    w.show();

    return a.exec();
}
