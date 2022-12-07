#include "Day4.hpp"

#include "../Utils.h"

auto Split(const std::string& str, const char delim) -> std::pair<std::string, std::string> {
	const auto offset = str.find(delim);
	const auto s1 = str.substr(0, offset);
	const auto s2 = str.substr(offset + 1, str.size() - offset);
	return { s1, s2 };
}

auto SplitInt(const std::string& str, const char delim) -> std::pair<int, int> {
	const auto [s1, s2] = Split(str, delim);
	return { std::stoi(s1), std::stoi(s2) };
}

void Day4Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer;

	int total = 0;
	for(auto& line : data) {
		if(line.empty()) continue;
		const auto [p1, p2] = Split(line, ',');
		const auto [min1, max1] = SplitInt(p1, '-');
		const auto [min2, max2] = SplitInt(p2, '-');
		if((min1 >= min2 && max1 <= max2) || (min1 <= min2 && max1 >= max2)) {
			total++;
		}
	}

	timer.Print("Day4, Part1");
	LOG(total);
}

void Day4Part2(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer;

	int total = 0;
	for(auto& line : data) {
		if(line.empty()) continue;
		const auto [p1, p2] = Split(line, ',');
		const auto [min1, max1] = SplitInt(p1, '-');
		const auto [min2, max2] = SplitInt(p2, '-');
		if((min1 >= min2 && min1 <= max2) || (min1 <= min2 && max1 >= min2)) {
			total++;
		}
	}

	timer.Print("Day4, Part2");
	LOG(total);
}

void Day4() {
	const auto& data = Utils::ReadInputFile("Day4");

	Day4Part1(data);

	Day4Part2(data);
}
