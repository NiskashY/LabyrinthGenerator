#include <QtWidgets>
#include <QFile>

#include "ui/mainwindow.h"

auto getStyleSheet() -> QString {
    QFile file("/home/mint/GitRepos/LabyrinthGenerator/images/stylesheet.qss");
    file.open(QFile::ReadOnly);
    return QLatin1String(file.readAll());
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setStyleSheet(getStyleSheet());
    MainWidget w;
    w.show();

    return app.exec();
}
