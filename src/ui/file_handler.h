#pragma once

#include <QString>
#include <fstream>
#include <vector>

class FileHandler {
public:
    explicit FileHandler(const std::string& fileName) : fileStream(fileName) {
    }

    explicit FileHandler(const QString& fileName) : fileStream(fileName.toStdString()) {
    }


    auto read() -> std::pair<
            std::vector<std::vector<int>>,
            std::vector<std::vector<int>>>;

    auto write(auto& v_data, auto& h_data) -> void;

private:
    auto readVec(auto& vec) -> void {
        for (auto& row : vec) {
            for (auto& cell : row) {
                fileStream >> cell;
            }
        }
    }

    auto writeVec(const auto& vec) -> void {
        for (auto& row : vec) {
            for (auto& cell : row) {
                fileStream << cell << ' ';
            }
            fileStream << '\n';
        }
    }

    std::fstream fileStream;
};
