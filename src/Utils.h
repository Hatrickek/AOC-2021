#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#define LOG(...) std::cout << __VA_ARGS__ << std::endl

#define PROFILER_START() Utils::ProfilerTimer timer
#define PROFILER_STOP(timer) timer.Print("Day 1")

namespace Utils {
	std::vector<std::string> ReadInputFile(const std::string& day);
	std::vector<int> ReadInputFileAsInt(const std::string& day);

	class ProfilerTimer {
	public:
		ProfilerTimer(const char* name = "", bool writeProfile = false)
			: m_Name(name), m_WriteProfile(writeProfile), m_ElapsedTime(0), m_Stopped(false) {
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		~ProfilerTimer() {
			if(!m_Stopped)
				Stop();
		}

		float ElapsedMilliSeconds() const { return static_cast<float>(m_ElapsedTime.count()) / 1000.0f; }

		float ElapsedMicroSeconds() const { return static_cast<float>(m_ElapsedTime.count()) / 1000.0f; }

		void Stop();

		void Print(const std::string_view day);
	private:
		const char* m_Name;
		bool m_WriteProfile;
		std::chrono::microseconds m_ElapsedTime;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}
