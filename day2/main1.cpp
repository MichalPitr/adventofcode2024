#include <fstream>
#include <string>
#include <vector>
#include <iostream>

int main() {
    std::ifstream file("input.txt");
    std::string str;

    int correct = 0;
    while (std::getline(file, str)) {
      // Start with i = 0 and look for white char. Once we have it, we know the substr [i, j+1) is a number.
        // std::cout << str << '\n';
        int i = 0;
        std::vector<int> nums;
        while (i < str.size()) {
            int j = i;
            while (j < str.size() && str[j] != ' ') j++;
            int num = std::stoi(str.substr(i, j-i));
            nums.push_back(num);
            i = j+1;
        }

        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << '\n';

        // std::cout << "nums size:  " << nums.size() << '\n';

        // is increasing?
        bool increasing = true;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] <= nums[i-1]) {
                increasing = false;
                break;
            }
            if (abs(nums[i] - nums[i-1]) > 3) {
                increasing = false;
                break;
            }
        }

        if (increasing) {
            std::cout << "increasing" << '\n';
            ++correct;
            continue;
        }

        // is decreasing?
        bool decreasing = true;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] >= nums[i-1]) {
                decreasing = false;
                break;
            }
            if (abs(nums[i] - nums[i-1]) > 3) {
                decreasing = false;
                break;
            }
        }

        if (decreasing) {
            std::cout << "decreasing" << '\n';
            ++correct;
            continue;
        }
    }

    std::cout << "correct: " << correct << '\n';
}