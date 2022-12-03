#include "../Utils.h"

// A -> ROCK
// B -> PAPER
// C -> SCISSOR

void Day2Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer;

	int score = 0;

	for(auto& item : data) {
		if(item == "A X") score += 4;
		else if(item == "A Y") score += 8;
		else if(item == "A Z") score += 3;
		else if(item == "B X") score += 1;
		else if(item == "B Y") score += 5;
		else if(item == "B Z") score += 9;
		else if(item == "C X") score += 7;
		else if(item == "C Y") score += 2;
		else if(item == "C Z") score += 6;
	}

	timer.Print("Day2, Part1");

	LOG(score);
}

void Day2Part2(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer;
	int score = 0;

	for(auto& item : data) {
		if(item == "A X") score += 3;
		else if(item == "A Y") score += 4;
		else if(item == "A Z") score += 8;
		else if(item == "B X") score += 1;
		else if(item == "B Y") score += 5;
		else if(item == "B Z") score += 9;
		else if(item == "C X") score += 2;
		else if(item == "C Y") score += 6;
		else if(item == "C Z") score += 7;
	}

	timer.Print("Day2, Part2");

	LOG(score);
}

void Day2() {
	const auto& data = Utils::ReadInputFile("Day2");
	Day2Part1(data);
	Day2Part2(data);
}