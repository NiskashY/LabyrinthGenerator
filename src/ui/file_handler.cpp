#include "file_handler.h"

auto FileHandler::read() -> std::pair<
    std::vector<std::vector<int>>,
    std::vector<std::vector<int>>>
{
    size_t rows = 0, columns = 0;
    fileStream >> rows >> columns;
    std::vector<std::vector<int>> v_data(rows, std::vector<int>(columns));
    std::vector<std::vector<int>> h_data(rows, std::vector<int>(columns));
    readVec(v_data);
    readVec(h_data);
    return std::pair{v_data, h_data};
}

auto FileHandler::write(auto& v_data, auto& h_data) -> void {
    size_t rows = 0, columns = 0;
    fileStream << rows << ' ' << columns << '\n';
    writeVec(v_data);
    writeVec(h_data);
}

