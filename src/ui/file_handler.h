#pragma once

#include <QApplication>
#include <QString>

#include <iomanip>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

namespace file {
class Handler {
public:
    template <class T> using v = std::vector<T>;

    explicit Handler(const QString&);

    auto read() -> std::pair<v<v<int>>, v<v<int>>>;

    auto write(const std::vector<std::vector<int>>&,
               const std::vector<std::vector<int>>&) -> void;

private: // funcitons
    auto createFile() -> void;

    auto readVec(auto&) -> void;

    auto writeVec(const auto&) -> void;

private: // vars
    const std::string fileName;
    std::fstream fileStream;
};

auto createFileName(QString = "") -> QString;
auto getFileNameFromPath(QString) -> QString;
}; // end namespace file

