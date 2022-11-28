#include "Utils.h"

#include <filesystem>
#include <fstream>

namespace Utils {
	std::vector<std::string> ReadInputFile(const std::string& day) {
		std::vector<std::string> inputs;
		const std::filesystem::path fileName = "input.txt";
		const std::filesystem::path srcPath = "src";
		const std::filesystem::path path = srcPath / day / fileName;
		std::ifstream file(path);

		std::string s;
		while(std::getline(file, s))
			inputs.emplace_back(s);

		file.close();
		return inputs;
	}

	std::vector<int> ReadInputFileAsInt(const std::string& day) {
		std::vector<int> inputs;
		const std::filesystem::path fileName = "input.txt";
		const std::filesystem::path srcPath = "src";
		const std::filesystem::path path = srcPath / day / fileName;
		std::ifstream file(path);

		std::string s;
		while(std::getline(file, s))
			inputs.emplace_back(stoi(s));

		file.close();
		return inputs;
	}
}
