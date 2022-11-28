#pragma once
#include <iostream>
#include <string>
#include <vector>

#define LOG(...) std::cout << __VA_ARGS__ << std::endl

namespace Utils {
	std::vector<std::string> ReadInputFile(const std::string& day);
	std::vector<int> ReadInputFileAsInt(const std::string& day);
}
