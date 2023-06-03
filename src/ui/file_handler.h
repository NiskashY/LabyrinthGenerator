#pragma once

#include "../custom_aliases.h"

#include <QString>
#include <fstream>

namespace file {
class Handler {
public:
    explicit Handler(const QString&);

    auto read() -> matrix_t;
    auto write(const matrix_t&) -> void;

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

