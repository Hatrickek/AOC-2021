#include "Day11.hpp"

#include <stack>

#include "../Utils.hpp"

struct Monkey {
	std::stack<uint64_t> Items;
	char Operation;
	uint64_t OperationValue;
	uint64_t TestDivision = 0;
	uint64_t TrueThrowOp = 0;
	uint64_t FalseThrowOp = 0;
	uint64_t InspectAmount = 0;
};

static std::vector<Monkey> s_Monkies;
static bool s_Part2 = false;

auto GetMonkeyBusiness() -> uint64_t {
	std::vector<uint64_t> sortedMonkeys;
	sortedMonkeys.reserve(s_Monkies.size());
	for(const auto& monkey : s_Monkies) {
		sortedMonkeys.emplace_back(monkey.InspectAmount);
	}
	std::ranges::sort(sortedMonkeys);

	return sortedMonkeys[sortedMonkeys.size() - 1] * sortedMonkeys[sortedMonkeys.size() - 2];
}

auto ParseStartingItems(const std::string& line) -> std::stack<uint64_t> {
	std::stack<uint64_t> items;
	size_t start = 17;
	size_t end = line.find(", ", start);
	while(end != std::string::npos) {
		items.push(std::atoi(line.substr(start, end - start).c_str()));
		start = end + 2;
		end = line.find(", ", start);
	}
	items.push(std::atoi(line.substr(start, end - start).c_str()));

	return items;
}

auto MonkeyAction(const Monkey& monkey, const uint64_t worry) -> std::pair<uint64_t, uint64_t> {
	std::pair<uint64_t, uint64_t> result{}; //worry,monkey
	if(monkey.Operation == '*')
		result.first = worry * monkey.OperationValue / (s_Part2 == true ? 1 : 3);
	else if(monkey.Operation == '+')
		result.first = (worry + monkey.OperationValue) / (s_Part2 == true ? 1 : 3);
	result.second = result.first % monkey.TestDivision == 0 ? monkey.TrueThrowOp : monkey.FalseThrowOp;
	return result;
}
void Parse(const std::vector<std::string>& data) {
	Monkey monkey;
	for(const auto& line : data) {
		if(line.empty()) {
			s_Monkies.emplace_back(monkey);
			continue;
		}
		if(line[0] == 'M')
			continue;
		if(line[2] == 'S') {
			monkey.Items = ParseStartingItems(line);
		}
		else if(line[2] == 'O') {
			const auto op = line.find("old");
			monkey.Operation = line[23];
			const auto opVal = line.substr(op + 6, 2);
			monkey.OperationValue = std::atoi(opVal.c_str());
		}
		else if(line[2] == 'T') {
			const auto div = line.substr(line.size() - 2, 2);
			monkey.TestDivision = std::atoi(div.c_str());
		}
		else if(line[4] == 'I') {
			const auto op = line.substr(line.size() - 1, 1);
			if(line.find("true") != std::string::npos) {
				monkey.TrueThrowOp = std::atoi(op.c_str());
			}
			else {
				monkey.FalseThrowOp = std::atoi(op.c_str());
			}
		}
	}
}
void Day11Part1(const std::vector<std::string>& data) {
	Parse(data);

	constexpr int nRounds = 20;
	for(int round = 0; round < nRounds; round++) {
		for(auto& m : s_Monkies) {
			while(!m.Items.empty()) {
				m.InspectAmount++;
				const auto worry = m.Items.top();
				m.Items.pop();
				const auto [newWorry, newMonkey] = MonkeyAction(m, worry);
				s_Monkies[newMonkey].Items.push(newWorry);
			}
		}
	}

	LOG(GetMonkeyBusiness());
}

void Day11Part2(const std::vector<std::string>& data) {
	s_Monkies.clear();
	s_Part2 = true;
	Parse(data);

	constexpr int nRounds = 10000;
	for(int round = 0; round < nRounds; round++) {
		for(auto& m : s_Monkies) {
			while(!m.Items.empty()) {
				m.InspectAmount++;
				const auto worry = m.Items.top();
				m.Items.pop();
				const auto [newWorry, newMonkey] = MonkeyAction(m, worry);
				s_Monkies[newMonkey].Items.push(newWorry);
			}
		}
	}

	LOG(GetMonkeyBusiness());
}

void Day11() {
	const auto data = Utils::ReadInputFile("Day11");
	Utils::ProfilerTimer timer("Day11, Part1");
	Day11Part1(data);
	timer.Print();
	Utils::ProfilerTimer timer2("Day11, Part2");
	Day11Part2(data);
	timer2.Print();
}
