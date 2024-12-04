#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream file("input.txt");
    std::string str;

    std::vector<int> left;
    std::vector<int> right;
    while (std::getline(file, str)) {
        int num1, num2;
        sscanf(str.c_str(), "%d %d", &num1, &num2);
        left.push_back(num1);
        right.push_back(num2);
    }

    std::unordered_map<int, int> counts;
    for (auto num : right) {
        counts[num]++;
    }

    int score = 0;
    for (auto num : left) {
        score += counts[num] * num;
    }
    std::cout << "score: " << score << '\n';
}