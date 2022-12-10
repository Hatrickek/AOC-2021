#include "Day1.hpp"

#include "../Utils.hpp"

void GetElvesList(const std::vector<int> &data, std::vector<int> *elves)
{
	int current = 0;
	for (const int i : data)
	{
		current += i;
		if (i == 0)
		{
			elves->emplace_back() += current;
			current = 0;
		}
	}
}

std::vector<int> elves;

void Day1Part1(const std::vector<int> &data)
{
	Utils::ProfilerTimer timer;

	int current = 0;
	int richestElf = -1;
	for (const int i : data)
	{
		current += i;
		if (i == 0)
		{
			elves.emplace_back() += current;
			if (current > richestElf)
				richestElf = current;
			current = 0;
		}
	}

	timer.Print("Day 1, Part 1");

	LOG(richestElf);
}

void Day1Part2()
{
	Utils::ProfilerTimer timer;

	std::ranges::sort(elves, std::greater());

	timer.Print("Day 1, Part 2");

	LOG(elves[0] + elves[1] + elves[2]);
}

void Day1()
{
	const std::vector<int> &data = Utils::ReadInputFileAsInt("day1");

	Day1Part1(data);

	Day1Part2();
}
