#include "Day1.h"

#include "../Utils.h"

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

void Part1(const std::vector<int> &data)
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

	//LOG(richestElf);

	timer.Print("Day 1, Part 1");
}

void Part2()
{
	Utils::ProfilerTimer timer;

	std::ranges::sort(elves, std::greater());
	//LOG(elves[0] + elves[1] + elves[2]);

	timer.Print("Day 1, Part 2");
}

void Day1()
{
	const std::vector<int> &data = Utils::ReadInputFileAsInt("day1");

	Part1(data);

	Part2();
}
