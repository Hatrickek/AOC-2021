#include "Day3.hpp"
#include "../Utils.hpp"
#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int GetScore(const char character) {
	if(character >= 'a')
		return character - 'a' + 1;
	return character - 'A' + 1 + 26;
}

void Day3Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer;
	int score = 0;
	for(const auto& line : data) {
		const auto mid = line.length() / 2;
		const auto c = *std::find_first_of(std::begin(line), std::next(std::begin(line), mid),
										   std::next(std::begin(line), mid), std::end(line));
		score += GetScore(c);
	}
	timer.Print("Day 3, Part 1");
	LOG(score);
}

void Day3Part2(std::vector<std::string>& data) {
	Utils::ProfilerTimer timer;
	int score = 0;

	std::array<int, 58> counter{};
	std::ranges::fill(counter, 0);
	for(auto& line : data) {
		std::ranges::sort(line);
		line.erase(std::ranges::unique(line).begin(), std::end(line));
		for(const auto c : line) {
			counter[c - 'A'] += 1;
			if(counter[c - 'A'] == 3) {
				score += GetScore(c);
				std::ranges::fill(counter, 0);
				break;
			}
		}
	}
	timer.Print("Day3, Part2");
	LOG(score);
}

void Day3() {
	const auto& data = Utils::ReadInputFile("Day3");

	auto nData = data;

	Day3Part1(data);
	Day3Part2(nData);
}