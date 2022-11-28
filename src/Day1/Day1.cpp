#include "Day1.h"
#include "../Utils.h"

void CalcIncreases(const std::vector<int>& data) {
    int sum = 0;
    const size_t lenght = data.size();
    for(size_t i = 1; i < lenght; i++) {
        if(data[i] > data[i - 1]) { sum += 1; }
    }
    LOG(sum);
}

void Part2() {
    const auto& data = Utils::ReadInputFileAsInt("day1");

    const size_t lenght = data.size();
    std::vector <int> data2;
    for(size_t i = 2; i < lenght; i++) {
        int window = data[i] + data[i - 1] + data[i - 2];
        data2.emplace_back(window);
    }

    CalcIncreases(data2);
}

void Day1() {
    const std::vector<int>& data = Utils::ReadInputFileAsInt("day1");

    CalcIncreases(data);
    Part2();
}
