#include "../Utils.h"

void Part1(const std::vector<std::string>& data) {
	int depth = 0, horizontal = 0;

	for (const auto& i : data) {
		if (i.starts_with("forward")) {
			const int value = stoi(i.substr(8, i.find(' ')));
			horizontal += value;
		}
		if(i.starts_with("up")) {
			const int value = stoi(i.substr(3, i.find(' ')));
			depth -= value;
		}
		if(i.starts_with("down")) {
			const int value = stoi(i.substr(5, i.find(' ')));
			depth += value;
		}
	}
	LOG(depth * horizontal);
}

void Part2(const std::vector<std::string>& data) {
	int deep = 0, aim = 0, position = 0;

	for(const auto& i : data) {
		if(i.starts_with("forward")) {
			const int value = stoi(i.substr(8, i.find(' ')));
			position += value;
			deep += aim * value;
		}
		if(i.starts_with("up")) {
			const int value = stoi(i.substr(3, i.find(' ')));
			aim -= value;
		}
		if(i.starts_with("down")) {
			const int value = stoi(i.substr(5, i.find(' ')));
			aim += value;
		}
	}
	LOG(position * deep);
}

void Day2() {
	const auto& data = Utils::ReadInputFile("Day2");
	Part1(data);
	Part2(data);
}