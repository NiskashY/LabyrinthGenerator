#include "file_handler.h"

auto getTimeStr() -> std::string {
    auto current_time = std::time(nullptr);
    auto fmt_time     = *std::localtime(&current_time);
    std::ostringstream oss;
    oss << std::put_time(&fmt_time, "%d-%m-%y_%H-%M-%S");
    return oss.str();
}


auto file::Handler::read() -> std::pair<v<v<int>>, v<v<int>>> {
    size_t rows = 0, columns = 0;
    fileStream >> rows >> columns;
    std::vector<std::vector<int>> v_data(rows, std::vector<int>(columns));
    std::vector<std::vector<int>> h_data(rows, std::vector<int>(columns));
    readVec(v_data);
    readVec(h_data);
    return std::pair{v_data, h_data};
}

auto file::Handler::write(const std::vector<std::vector<int>>& v_data,
                          const std::vector<std::vector<int>>& h_data) -> void {
    size_t rows = v_data.size();
    size_t columns = v_data.empty() ? 0 : v_data[0].size();
    fileStream << rows << ' ' << columns << '\n';
    writeVec(v_data);
    writeVec(h_data);
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
