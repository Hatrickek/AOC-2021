#include "Day7.h"
#include "../Utils.h"

struct File {
	std::string Name;
	uint64_t Size = 0;
};

struct Directory {
	std::string Name;
	std::vector<std::shared_ptr<Directory>> Directories;
	std::vector<std::shared_ptr<File>> Files;
	Directory* Parent = nullptr;
	uint64_t Size = 0;
};

auto UpdateSizes(Directory* fileSystem) -> uint64_t {
	for(const auto& dir : fileSystem->Directories) {
		fileSystem->Size += UpdateSizes(dir.get());
	}
	for(const auto& file : fileSystem->Files) {
		fileSystem->Size += file->Size;
	}
	return fileSystem->Size;
}

uint64_t CountDirsLteThreshold(const Directory* main_dir) {
	uint64_t sum = 0;
	for(const auto& dir : main_dir->Directories) {
		if(dir->Size <= 100'000) {
			sum += dir->Size;
		}
		const auto ans = CountDirsLteThreshold(dir.get());
		sum += ans;
	}
	return sum;
}

void Day7Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day7, Part1");

	Directory fileSystem;
	fileSystem.Name = "/";
	fileSystem.Parent = &fileSystem;
	fileSystem.Directories.clear();
	fileSystem.Files.clear();

	auto currentDir = &fileSystem;

	for(const auto& line : data) {
		if(line[0] == '$') {
			constexpr auto index = 4;
			const auto command = line.substr(2, index - 2);
			if(command == "cd") {
				const auto command2 = line.substr(index + 1, line.size() - 1 - index);
				if(command2 == "..")
					currentDir = currentDir->Parent;
				else if(command2 == "/")
					currentDir = &fileSystem;
				else {
					bool found = false;
					for(auto& dir : currentDir->Directories) {
						if(dir->Name == command2) {
							found = true;
							currentDir = dir.get();
							break;
						}
					}
					if(!found) {
						auto& dir = currentDir->Directories.emplace_back(std::make_shared<Directory>(command2));
						dir->Parent = currentDir;
						currentDir = dir.get();
					}
				}
			}
		}
		else if(line[0] == 'd') {
			const auto& dirName = line.substr(4, line.size() - 4);
			const auto& dir = currentDir->Directories.emplace_back(std::make_shared<Directory>());
			dir->Name = dirName;
			dir->Parent = currentDir;
		}
		else if(line[0] != 'd' && line[0] != '$') {
			const auto index = line.find(' ');
			const auto fileSize = std::stoll(line.substr(0, index));
			const auto fileName = line.substr(index + 1, line.size() - 1 - index);
			currentDir->Files.emplace_back(std::make_shared<File>(fileName, fileSize));
		}
	}

	UpdateSizes(&fileSystem);

	auto sum = CountDirsLteThreshold(&fileSystem);
	if(fileSystem.Size <= 100'000) {
		sum += fileSystem.Size;
	}

	timer.Print();

	LOG(sum);
}

uint64_t FindDirectoryGte(const Directory* mainDir, const uint64_t threshold) {
	auto min = mainDir->Size;
	for(const auto& dir : mainDir->Directories) {
		if(dir->Size > threshold) {
			const auto minAboveThresh = FindDirectoryGte(dir.get(), threshold);
			min = std::min(min, minAboveThresh);
		}
	}
	return min;
}

void Day7Part2(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day7, Part2");

	Directory fileSystem;
	fileSystem.Name = "/";
	fileSystem.Parent = &fileSystem;
	fileSystem.Directories.clear();
	fileSystem.Files.clear();

	auto currentDir = &fileSystem;

	for(const auto& line : data) {
		if(line[0] == '$') {
			constexpr auto index = 4;
			const auto command = line.substr(2, index - 2);
			if(command == "cd") {
				const auto command2 = line.substr(index + 1, line.size() - 1 - index);
				if(command2 == "..")
					currentDir = currentDir->Parent;
				else if(command2 == "/")
					currentDir = &fileSystem;
				else {
					bool found = false;
					for(auto& dir : currentDir->Directories) {
						if(dir->Name == command2) {
							found = true;
							currentDir = dir.get();
							break;
						}
					}
					if(!found) {
						auto& dir = currentDir->Directories.emplace_back(std::make_shared<Directory>(command2));
						dir->Parent = currentDir;
						currentDir = dir.get();
					}
				}
			}
		}
		else if(line[0] == 'd') {
			const auto& dirName = line.substr(4, line.size() - 4);
			const auto& dir = currentDir->Directories.emplace_back(std::make_shared<Directory>());
			dir->Name = dirName;
			dir->Parent = currentDir;

		}
		else if(line[0] != 'd' && line[0] != '$') {
			const auto index = line.find(' ');
			const auto fileSize = std::stoll(line.substr(0, index));
			const auto fileName = line.substr(index + 1, line.size() - 1 - index);
			currentDir->Files.emplace_back(std::make_shared<File>(fileName, fileSize));
		}
	}

	UpdateSizes(&fileSystem);

	const auto available = 70'000'000 - fileSystem.Size;
	const auto required = 30'000'000 - available;
	const auto val = FindDirectoryGte(&fileSystem, required);
	timer.Print();

	LOG(val);

}

void Day7() {
	const auto data = Utils::ReadInputFile("Day7");

	Day7Part1(data);
	Day7Part2(data);
}
