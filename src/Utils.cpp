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
		ProfilerTimer timer;
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
		timer.Print("Input loaded");

		return inputs;
	}

	double ProfilerTimer::ElapsedMilliSeconds() const {
		return m_ElapsedTime.count() / 1000.0;
	}

	double ProfilerTimer::ElapsedMicroSeconds() const {
		return m_ElapsedTime.count() / 10.0;
	}

	void ProfilerTimer::Stop() {
		const auto endTimepoint = std::chrono::steady_clock::now();
		m_ElapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

		m_Stopped = true;
	}

	void ProfilerTimer::Print(const std::string_view arg) {
		Stop(); 
		LOG(arg << "  | Took: " << ElapsedMicroSeconds() << "us");
	}
}
