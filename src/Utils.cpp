#include "Utils.hpp"

#include <filesystem>
#include <fstream>

namespace Utils {
	std::vector<std::vector<char>> ReadInputFileAs2D(const std::string& day) {
		std::vector<std::vector<char>> result;
		const std::filesystem::path fileName = "input.txt";
		const std::filesystem::path srcPath = "src";
		const std::filesystem::path path = srcPath / day / fileName;
		std::ifstream file(path);

		std::vector<std::string> lines;
		std::string s;
		while(std::getline(file, s))
			lines.emplace_back(s);

		result.resize(lines.size());
		for(auto& r : result)
			r.resize(lines.size());

		for(size_t i = 0; i < lines.size(); i++) {
			for(size_t j = 0; j < lines[i].size(); j++) {
				result[i][j] = lines[i][j];
			}
		}

		file.close();
		return result;
	}
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
		while(std::getline(file, s)) {
			if(!s.empty())
				inputs.emplace_back(stoi(s));
			else
				inputs.emplace_back(0);
		}

		file.close();

		return inputs;
	}

	double ProfilerTimer::ElapsedMilliSeconds() const {
		return static_cast<double>(m_ElapsedTime.count()) / 1000.0;
	}

	double ProfilerTimer::ElapsedMicroSeconds() const {
		return static_cast<double>(m_ElapsedTime.count());
	}

	double ProfilerTimer::ElapsedNanoSeconds() const {
		return static_cast<double>(m_ElapsedTime.count() * 1000);
	}

	void ProfilerTimer::Stop() {
		const auto endTimepoint = std::chrono::steady_clock::now();
		m_ElapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

		m_Stopped = true;
	}

	void ProfilerTimer::Print(const std::string_view arg) {
		Stop();
		if(arg.empty())
			LOG(m_Name << "  | Took: " << ElapsedMicroSeconds() << "us");
		else
			LOG(arg << "  | Took: " << ElapsedMicroSeconds() << "us");
	}
}
