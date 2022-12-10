#include "Day8.hpp"
#include "../Utils.hpp"

#define CTI(x) ((x) - '0')

auto IsVisible(const std::vector<std::vector<char>>& data, size_t row, size_t col) -> bool {
	//UP
	if(row != 0 && CTI(data[row][col]) > CTI(data[row - 1][col])) {
		return true;
	}

	//DOWN
	if(row != data.size() && CTI(data[row][col]) > CTI(data[row + 1][col])) {
		return true;
	}

	//LEFT
	if(col != 0 && CTI(data[row][col]) > CTI(data[row][col - 1])) {
		return true;
	}

	//RIGHT
	if(col != data[0].size() && CTI(data[row][col]) > CTI(data[row][col + 1])) {
		return true;
	}

	return false;
}
auto GetScore(const std::vector<std::vector<char>>& data, size_t row, size_t col) -> int {
	int score = 0;
	//UP
	if(row != 0 && CTI(data[row][col]) > CTI(data[row - 1][col])) {
		for(size_t i = 0; i < row; i++) {
			if(IsVisible(data, i, col)) {
				score++;
			}
		}
	}

	//DOWN
	if(row != data.size() && CTI(data[row][col]) > CTI(data[row + 1][col])) {
		for(size_t i = row; i > 0; i--) {
			if(IsVisible(data, i, col)) {
				score++;
			}
		}
	}

	//LEFT
	if(col != 0 && CTI(data[row][col]) > CTI(data[row][col - 1])) {
		for(size_t i = 0; i < col; i++) {
			if(IsVisible(data, row, i)) {
				score++;
			}
		}
	}

	//RIGHT
	if(col != data[0].size() && CTI(data[row][col]) > CTI(data[row][col + 1])) {
		for(size_t i = col; i > 0; i--) {
			if(IsVisible(data, row, i)) {
				score++;
			}
		}
	}

	return score;
}
void Day8Part1And2(const std::vector<std::vector<char>>& data) {
	int hiddenTrees = 0;
	int visibleTrees = 0;

	for(size_t row = 0; row < data.size(); row++) {
		for(size_t col = 0; col < data[row].size(); col++) {
			if(row == 0 || col == 0 || col == data.size() - 1 || row == data[0].size() - 1) {
				visibleTrees += 1;
				continue;
			}
			if(IsVisible(data, row, col)) {
				visibleTrees += 1;
				continue;
			}
			hiddenTrees += 1;
		}
	}
	LOG(visibleTrees);

	int highestScore = 0;
	for(size_t row = 0; row < data.size(); row++) {
		for(size_t col = 0; col < data[row].size(); col++) {
			if(row == 0 || col == 0 || col == data.size() - 1 || row == data[0].size() - 1) {
				const int score = GetScore(data, row, col);
				if(score > highestScore)
					highestScore = score;
				continue;
			}
			if(IsVisible(data, row, col)) {
				const int score = GetScore(data, row, col);
				if(score > highestScore)
					highestScore = score;
			}
		}
	}

	LOG(highestScore);
}

void Day8() {
	const auto& data = Utils::ReadInputFileAs2D("Day8");
	Day8Part1And2(data);
}
