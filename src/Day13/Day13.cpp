#include "Day13.hpp"
#include "../Utils.hpp"

bool IsNumber(const char c) {
	return c >= '0' && c <= '9';
}

int32_t ToNumber(const char c) {
	return c - '0';
}

bool Compare(const std::string& packet1, const std::string& packet2) {
	size_t index1 = 0;
	size_t index2 = 0;
	while(index1 < packet1.size() && index2 < packet2.size()) {
		if(IsNumber(packet1[index1]) && IsNumber(packet2[index2])) {
			int n1 = 0;
			int n2 = 0;
			while(IsNumber(packet1[index1])) {
				n1 = n1 * 10 + ToNumber(packet1[index1]);
				index1++;
			}
			while(IsNumber(packet2[index2])) {
				n2 = n2 * 10 + ToNumber(packet2[index2]);
				index2++;
			}
			if(n1 == n2)
				continue;
			if(n1 < n2)
				return true;
			break;
		}
		if(packet1[index1] == packet2[index2]) {
			index1++;
			index2++;
		}
		else if(packet1[index1] == ']')
			return true;
		else if(packet2[index2] == ']')
			break;
		else if(packet1[index1] == '[' || packet1[index1] == ',')
			index1++;
		else if(packet2[index2] == ',' || packet2[index2] == '[')
			index2++;
	}
	if(index1 == packet1.size()) {
		return true;
	}
	return false;
}

void Day13Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day13, Part1");

	int32_t sum = 51;
	int32_t index = 0;

	for(size_t i = 0; i < data.size() - 1; i++) {
		if(data[i].empty()) {
			continue;
		}
		index++;
		if(Compare(data[i], data[i + 1])) {
			sum += index;
		}
		i++;
	}

	timer.Print();
	LOG(sum);
}

void Day13Part2(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day13, Part2");

	std::vector<std::string> copy;
	for(auto& line : data) {
		if(line.empty())
			continue;
		copy.emplace_back(line);
	}

	const std::vector<std::string> dividerPackets{
	  "[[2]]",
	  "[[6]]"
	};

	copy.emplace_back(dividerPackets[0]);
	copy.emplace_back(dividerPackets[1]);

	std::ranges::sort(copy, Compare);

	int ans = 1;
	for(const auto& dividerPacket : dividerPackets) {
		ans *= std::distance(std::begin(copy), std::ranges::find(copy, dividerPacket)) + 1;
	}


	timer.Print();
	LOG(ans);
}

void Day13() {
	const auto data = Utils::ReadInputFile("Day13");
	Day13Part1(data);
	Day13Part2(data);
}