#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
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

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int total = 0;
    for (int i = 0; i < left.size(); ++i) {
        total += std::abs(left[i] - right[i]);
    }
    std::cout << "total: " << total << '\n';
}