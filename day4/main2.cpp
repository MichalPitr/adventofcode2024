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

// We always start search from an A so we can assume x >= 1 and <= grid[0].size()-2, and similarly for y.  
bool isMaxCross(std::vector<std::vector<char>>& grid, int x, int y) {
    bool mainDiag = false;
    if (grid[y-1][x-1] == 'M' && grid [y+1][x+1] == 'S' || grid[y-1][x-1] == 'S' && grid [y+1][x+1] == 'M') {
        mainDiag = true;
    }

    bool secondaryDiag = false;
    if (grid[y+1][x-1] == 'M' && grid [y-1][x+1] == 'S' || grid[y+1][x-1] == 'S' && grid [y-1][x+1] == 'M') {
        secondaryDiag = true;
    }

    return mainDiag && secondaryDiag;
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
    for (int y = 1; y < grid.size()-1; ++y) {
        for (int x = 1; x < grid[0].size()-1; ++x) {
            if (grid[y][x] == 'A') {
                total += int(isMaxCross(grid, x, y));
            }
        }
    }
    std::cout << "count: " << total << '\n';
}