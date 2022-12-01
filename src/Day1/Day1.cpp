#include "Day1.h"
#include "../Utils.h"


void Part1(const std::vector<int>& data) {
	struct Elf {
		int value;
	};

	Utils::ProfilerTimer timer;

	std::vector<Elf> elfs;

	int current = 0;
	for (const int i : data) {
		current += i;
		if(i == 0) {
			elfs.emplace_back().value += current;
			current = 0;
		}
	}

	const Elf* richestElf = nullptr;

	for(const auto& elf : elfs) {
		if(!richestElf)
			richestElf = &elf;
		else {
			if(elf.value > richestElf->value) {
				richestElf = &elf;
			}
		}
	}

	LOG(richestElf->value);

	timer.Print("Day 1, Part 1");
}

void Part2() {
	Utils::ProfilerTimer timer;


	timer.Print("Day 1, Part 1");
}

void Day1() {
	const std::vector<int>& data = Utils::ReadInputFileAsInt("day1");

	Part1(data);
}
