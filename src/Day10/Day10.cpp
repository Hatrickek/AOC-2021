#include "Day10.hpp"
#include "../Utils.hpp"
#include <array>

static int64_t s_X = 1;
static int64_t s_CycleCount = 0;
static int64_t s_SignalStrength = 0;
static std::array<std::array<char, 40>, 6> s_Screen;
static bool s_IsPart2 = false;

void UpdateScreen() {
	const auto pixel_id = (s_CycleCount - 1) % 240;
	const auto pixel_row = pixel_id / 40;
	const auto pixel_col = pixel_id % 40;
	if(pixel_col == s_X || pixel_col == (s_X - 1) || pixel_col == (s_X + 1)) {
		s_Screen[pixel_row][pixel_col] = '#';
	}
	else {
		s_Screen[pixel_row][pixel_col] = '.';
	}
}

void Tick() {
	s_CycleCount++;
	if(s_IsPart2)
		UpdateScreen();
	if((s_CycleCount - 20) % 40 == 0) {
		s_SignalStrength += s_CycleCount * s_X;
	}
}

void AddX(const int val) {
	Tick();
	Tick();
	s_X += val;
}

void Noop() {
	Tick();
}

void PrintScreen() {
	for(const auto& row : s_Screen) {
		for(const auto ele : row) {
			std::cout << ele;
		}
		std::cout << '\n';
	}
}

void Day10Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day10, Part1");
	for(const auto& line : data) {
		constexpr auto space = 4;
		const auto cmd = line.substr(0, space);
		if(cmd == "noop") {
			Noop();
		}
		else if(cmd == "addx") {
			AddX(std::atoi(line.substr(space + 1, line.size() - space - 1).c_str()));
		}
	}
	timer.Print();
	LOG(s_SignalStrength);
}

void Reset() {
	s_X = 1;
	s_CycleCount = 0;
	s_SignalStrength = 0;
	s_IsPart2 = true;
}

void Day10Part2(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day10, Part2");
	for(const auto& line : data) {
		constexpr auto space = 4;
		const auto cmd = line.substr(0, space);
		if(cmd == "noop") {
			Noop();
		}
		else if(cmd == "addx") {
			AddX(std::atoi(line.substr(space + 1, line.size() - space - 1).c_str()));
		}
	}
	timer.Print();
	PrintScreen();
}

void Day10() {
	const auto data = Utils::ReadInputFile("Day10");
	Day10Part1(data);
	Reset();
	Day10Part2(data);
}
