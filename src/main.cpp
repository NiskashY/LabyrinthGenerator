#include "ui/mainwindow.h"

#include <QApplication>
#include <QFile>

auto getStyleSheet() -> QString {
    QFile file(":/style/stylesheet.qss");
    file.open(QFile::ReadOnly);
    return QLatin1String(file.readAll());
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyleSheet(getStyleSheet());

    MainWindow w;
    w.show();

    return a.exec();
}
