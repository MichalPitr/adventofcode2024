#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<char>> fileToGrid(std::string filename) {
    std::ifstream file(filename);
    std::string str;
    std::vector<std::vector<char>> grid;
    while (std::getline(file, str)) {
        std::vector<char> row;
        for (char c : str) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    file.close();
    return grid;
}

// x, y
std::vector<std::pair<int, int>> directions{
    {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

std::string xmas = "XMAS";

int countXmasStartingAt(std::vector<std::vector<char>>& grid, int x, int y) {
    int count = 0;
    for (auto [dx, dy] : directions) {
        // 4 is the length of XMAS
        bool valid = true;
        for (int i = 0; i < xmas.size(); ++i) {
            if (x + i * dx >= 0 && x + i * dx < grid[0].size() &&
                y + i * dy >= 0 && y + i * dy < grid.size() &&
                grid[y + i * dy][x + i * dx] == xmas[i]) {
                continue;
            } else {
                valid = false;
                break;
            }
        }
        if (valid) ++count;
    }
    return count;
}

int main() {
    auto grid = fileToGrid("input.txt");

    // for (auto row : grid) {
    //     for (char c : row) {
    //         std::cout << c << " ";
    //     }
    //     std::cout << '\n';
    // }

    int total = 0;
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            if (grid[y][x] == 'X') {
                total += countXmasStartingAt(grid, x, y);
            }
        }
    }
    std::cout << "count: " << total << '\n';
}