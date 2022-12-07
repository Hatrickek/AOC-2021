#include "Day6.h"
#include "../Utils.h"
#include <unordered_map>

void Day6Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day6, Part1");
	auto& line = data[0];

	std::unordered_map<char, int> s;

	for(int i = 0; i < 3; i++) {
		s[line[i]] += 1;
	}

	for(int i = 3; i < (int)line.size(); i++) {
		s[line[i]] += 1;
		if(s.size() == 4) {
			LOG(i + 1);
			break;
		}
		s[line[i - 3]] -= 1;
		if(s[line[i - 3]] == 0) {
			s.erase(line[i - 3]);
		}
	}
	timer.Print();
}

void Day6Part2(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day6, Part2");
	auto& line = data[0];

	std::unordered_map<char, int> s;

	for(int i = 0; i < 13; i++) {
		s[line[i]] += 1;
	}

	for(int i = 13; i < (int)line.size(); i++) {
		s[line[i]] += 1;
		if(s.size() == 14) {
			LOG(i + 1);
			break;
		}
		s[line[i - 13]] -= 1;
		if(s[line[i - 13]] == 0) {
			s.erase(line[i - 13]);
		}
	}
	timer.Print();
}

void Day6() {
	const auto data = Utils::ReadInputFile("Day6");
	Day6Part1(data);
	Day6Part2(data);
}
