#include "file_handler.h"

file::Handler::Handler(const QString& fileName_) :
    fileName(fileName_.toStdString()), fileStream(fileName) {
    if (!fileStream) {
        this->createFile();
    }
}

auto getTimeStr() -> std::string {
    auto current_time = std::time(nullptr);
    auto fmt_time     = *std::localtime(&current_time);
    std::ostringstream oss;
    oss << std::put_time(&fmt_time, "%d-%m-%y_%H-%M-%S");
    return oss.str();
}

auto file::Handler::read() -> matrix_t {
    size_t rows = 0, columns = 0;
    fileStream >> rows >> columns;
    matrix_t data(rows, matrix_row_t(columns));
    readVec(data);
    return data;
}

auto file::Handler::write(const matrix_t& data) -> void {
    size_t rows = data.size();
    size_t columns = data.empty() ? 0 : data[0].size();
    fileStream << rows << ' ' << columns << '\n';
    writeVec(data);
}

auto file::Handler::readVec(auto& vec) -> void {
    for (auto& row : vec) {
        for (auto& cell : row) {
            fileStream >> cell;
        }
    }
}

auto file::Handler::writeVec(const auto& vec) -> void {
    for (auto& row : vec) {
        for (auto& cell : row) {
            fileStream << cell << ' ';
        }
        fileStream << '\n';
    }
}

auto file::createFileName(QString prefix) -> QString {
    auto time_str = QString::fromStdString(getTimeStr());
    if (prefix.isEmpty()) {
        prefix = "maze_";
    }
    return prefix + time_str;
}

auto file::getFileNameFromPath(QString file_path) -> QString {
    QString resultFileName;

    for (int i = (int)file_path.size() - 1; i >= 0 && file_path[i] != '/'; --i) {
        resultFileName += file_path[i];
    }

    std::reverse(resultFileName.begin(), resultFileName.end());
    return resultFileName;
}

auto file::Handler::createFile() -> void {  // weird ~-~
    fileStream.open(fileName, std::fstream::out); // creates file
    fileStream.close();
    fileStream.open(fileName, std::fstream::in |std::fstream::out); // reopen with read & write flags
}
