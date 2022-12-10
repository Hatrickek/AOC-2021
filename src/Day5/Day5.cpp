#include "Day5.hpp"

#include <regex>
#include <stack>

#include "../Utils.hpp"

auto ParseInput(const std::vector<std::string>& data) -> std::vector<std::stack<char>> {
	std::vector<std::string> stackLines;

	for(auto& l : data) {
		if(l[1] == '1') break;
		stackLines.emplace_back(l);
	}

	std::vector<std::stack<char>> stacks(9);

	for(int i = (int)stackLines.size() - 1; i >= 0; i--) {
		for(int j = 0; j < (int)stacks.size(); j++) {
			const int k = j * 4 + 1;
			if(stackLines[i][k] == ' ') continue;
			stacks[j].push(stackLines[i][k]);
		}
	}

	return stacks;
}

void Day5Part1(const std::vector<std::string>& data, std::vector<std::stack<char>>& stacks) {
	Utils::ProfilerTimer timer("Day5, Part1");

	const std::regex pattern(R"(move ([0-9]+) from ([0-9]+) to ([0-9]+))");
	
	for(auto line = data.begin() + 10; line != data.end(); ++line) {
		std::smatch match;
		std::regex_match(*line, match, pattern);
		const int n = std::stoi(match[1]);
		const int from = std::stoi(match[2]) - 1;
		const int to = std::stoi(match[3]) - 1;
		for(int i = 0; i < n; i++) {
			const char c = stacks[from].top();
			stacks[from].pop();
			stacks[to].push(c);
		}
	}

	timer.Print();

	for(const auto& stack : stacks) {
		LOGN((!stack.empty() ? stack.top() : ' '));
	}
	LOG(' ');
}

void Day5Part2(const std::vector<std::string>& data, std::vector<std::stack<char>>& stacks) {
	Utils::ProfilerTimer timer("Day5, Part2");

	const std::regex pattern(R"(move ([0-9]+) from ([0-9]+) to ([0-9]+))");
	
	for(auto line = data.begin() + 10; line != data.end(); ++line) {
		std::smatch match;
		std::regex_match(*line, match, pattern);
		const int n = std::stoi(match[1]);
		const int from = std::stoi(match[2]) - 1;
		const int to = std::stoi(match[3]) - 1;
		std::vector<char> cratesLifted;
		for(int i = 0; i < n; i++) {
			cratesLifted.push_back(stacks[from].top());
			stacks[from].pop();
		}
		for(int i = (int)cratesLifted.size() - 1; i >= 0; i--) {
			stacks[to].push(cratesLifted[i]);
		}
	}

	timer.Print();

	for(const auto& stack : stacks) {
		LOGN((!stack.empty() ? stack.top() : ' '));
	}
	LOG(' ');
}

void Day5() {
	const auto data = Utils::ReadInputFile("Day5");

	Utils::ProfilerTimer parseTimer("Parsing stack");
	auto stacks = ParseInput(data);
	parseTimer.Print();

	Day5Part1(data, stacks);
	Day5Part2(data, stacks);
}
