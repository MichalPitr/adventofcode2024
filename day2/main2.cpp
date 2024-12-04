#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> subarrayWithoutI(std::vector<int> &nums, int i) {
    std::vector<int> a;
    for (int j = 0; j < nums.size(); ++j) {
        if (j != i) {
            a.push_back(nums[j]);
        }
    }
    return a;
}

bool isIncreasingSequence(std::vector<int> &nums, bool damperAvailable) {
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] <= nums[i - 1] || abs(nums[i] - nums[i - 1]) > 3) {
            if (damperAvailable) {
                // try if nums without i or without i-1 works.
                std::vector<int> a = subarrayWithoutI(nums, i - 1);
                std::vector<int> b = subarrayWithoutI(nums, i);

                if (isIncreasingSequence(a, false) ||
                    isIncreasingSequence(b, false)) {
                    std::cout << "corrected\n";
                    return true;
                }
            }
            return false;
        }
    }
    return true;
}

bool isDecreasingSequence(std::vector<int> &nums, bool damperAvailable) {
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] >= nums[i - 1] || abs(nums[i] - nums[i - 1]) > 3) {
            if (damperAvailable) {
                // try if nums without i or without i-1 works.
                std::vector<int> a = subarrayWithoutI(nums, i - 1);
                std::vector<int> b = subarrayWithoutI(nums, i);

                if (isDecreasingSequence(a, false) ||
                    isDecreasingSequence(b, false)) {
                    std::cout << "corrected\n";
                    return true;
                }
            }
            return false;
        }
    }
    return true;
}

int main() {
    std::ifstream file("input.txt");
    std::string str;

    int correct = 0;
    while (std::getline(file, str)) {
        // Start with i = 0 and look for white char. Once we have it, we know
        // the substr [i, j+1) is a number.
        int i = 0;
        std::vector<int> nums;
        while (i < str.size()) {
            int j = i;
            while (j < str.size() && str[j] != ' ') j++;
            int num = std::stoi(str.substr(i, j - i));
            nums.push_back(num);
            i = j + 1;
        }

        if (isIncreasingSequence(nums, true)) {
            for (auto num : nums) {
                std::cout << num << " ";
            }
            std::cout << "increasing\n";
            ++correct;
            continue;
        }

        if (isDecreasingSequence(nums, true)) {
            for (auto num : nums) {
                std::cout << num << " ";
            }
            std::cout << "decreasing\n";
            ++correct;
            continue;
        }
    }

    std::cout << "correct: " << correct << '\n';
}