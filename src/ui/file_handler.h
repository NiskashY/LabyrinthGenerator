#pragma once

#include <QApplication>
#include <QString>

#include <iomanip>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

namespace file {

const QString kSavedMazesDirPath = QApplication::applicationDirPath() + "/saved-mazes/";

class Handler {
public:
    template <class T> using v = std::vector<T>;
    explicit Handler(const std::string& fileName) : fileStream(fileName) {
    }

    explicit Handler(const QString& fileName) : fileStream(fileName.toStdString()) {
    }


    auto read() -> std::pair<v<v<int>>, v<v<int>>>;

    auto write(const std::vector<std::vector<int>>& v_data,
               const std::vector<std::vector<int>>& h_data) -> void;

private:
    auto readVec(auto& vec) -> void;

    auto writeVec(const auto& vec) -> void;

    std::fstream fileStream;

};

auto createFileName(QString = "") -> QString;
auto getFileNameFromPath(QString) -> QString;
}; // end namespace file

