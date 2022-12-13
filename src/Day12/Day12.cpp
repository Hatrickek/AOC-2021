#include "Day12.hpp"
#include "../Utils.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

struct Vec2 {
	int32_t X;
	int32_t Y;
	Vec2(const int x, const int y) : X(x), Y(y) {}
	bool operator==(const Vec2& pos) const {
		return pos.X == X && pos.Y == Y;
	}
};

struct Point {
	Point(const Vec2& pos, const int parent, const int steps) : Pos(pos), Parent(parent), Steps(steps) {}
	Vec2 Pos;
	int32_t Parent, Steps;
};

auto IsInBounds(const std::vector<std::string>& grid, const Point& p) -> bool {
	return p.Pos.X >= 0 && p.Pos.Y >= 0 && p.Pos.X < (int32_t)grid.size() && p.Pos.Y < (int32_t)grid[0].size();
};

void Day12Part1(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day12, Part1");
	const std::vector directions = {
	  Point(Vec2(0, -1), 0, 0),
	  Point(Vec2(-1, 0), 0, 0),
	  Point(Vec2(0, 1), 0, 0),
	  Point(Vec2(1, 0), 0, 0)
	};

	std::vector<std::string> grid;
	Point start(Vec2(0, 0), 0, 0);
	Point end(Vec2(0, 0), 0, 0);
	for(const auto& line : data) {
		grid.push_back(line);
		auto it = line.find('S');
		if(it != std::string::npos) {
			start.Pos.X = (int32_t)grid.size() - 1;
			start.Pos.Y = (int32_t)it;
			start.Parent = start.Pos.X * (int32_t)grid[0].size() + start.Pos.Y;
			start.Steps = 0;
			grid[start.Pos.X][start.Pos.Y] = 'a';
		}
		it = line.find('E');
		if(it != std::string::npos) {
			end.Pos.X = (int32_t)grid.size() - 1;
			end.Pos.Y = (int32_t)it;
			end.Parent = 0;
			end.Steps = 0;
			grid[end.Pos.X][end.Pos.Y] = 'z';
		}
	}

	std::vector visited(grid.size(), std::vector(grid[0].size(), false));

	std::queue<Point> stack;
	stack.push(start);

	while(!stack.empty()) {
		const auto current = stack.front();
		stack.pop();
		if(visited[current.Pos.X][current.Pos.Y])
			continue;
		visited[current.Pos.X][current.Pos.Y] = true;
		if(current.Pos == end.Pos) {
			LOG(current.Steps);
			break;
		}
		for(const auto& dir : directions) {
			const auto newPoint = Point(
				Vec2(current.Pos.X + dir.Pos.X, current.Pos.Y + dir.Pos.Y),
				current.Pos.X * (int32_t)grid[0].size() + current.Pos.Y,
				current.Steps + 1
			);
			if(!IsInBounds(grid, newPoint))
				continue;
			if(visited[newPoint.Pos.X][newPoint.Pos.Y])
				continue;
			if(grid[current.Pos.X][current.Pos.Y] + 1 < grid[newPoint.Pos.X][newPoint.Pos.Y])
				continue;
			stack.push(newPoint);
		}
	}
	timer.Print();
}
void Day12Part2(const std::vector<std::string>& data) {
	Utils::ProfilerTimer timer("Day12, Part2");
	const std::vector directions = {
	  Point(Vec2(0, -1), 0, 0),
	  Point(Vec2(-1, 0), 0, 0),
	  Point(Vec2(0, 1), 0, 0),
	  Point(Vec2(1, 0), 0, 0)
	};

	std::vector<std::string> grid;
	Point start(Vec2(0, 0), 0, 0);
	Point end(Vec2(0, 0), 0, 0);
	for(const auto& line : data) {
		grid.push_back(line);
		auto it = line.find('S');
		if(it != std::string::npos) {
			start.Pos.X = (int32_t)grid.size() - 1;
			start.Pos.Y = (int32_t)it;
			start.Parent = start.Pos.X * (int32_t)grid[0].size() + start.Pos.Y;
			start.Steps = 0;
			grid[start.Pos.X][start.Pos.Y] = 'a';
		}
		it = line.find('E');
		if(it != std::string::npos) {
			end.Pos.X = (int32_t)grid.size() - 1;
			end.Pos.Y = (int32_t)it;
			end.Parent = 0;
			end.Steps = 0;
			grid[end.Pos.X][end.Pos.Y] = 'z';
		}
	}

	std::vector visited(grid.size(), std::vector(grid[0].size(), false));

	std::queue<Point> stack;
	stack.push(end);

	while(!stack.empty()) {
		const auto current = stack.front();
		stack.pop();
		if(visited[current.Pos.X][current.Pos.Y])
			continue;
		visited[current.Pos.X][current.Pos.Y] = true;
		if(grid[current.Pos.X][current.Pos.Y] == 'a') {
			LOG(current.Steps);
			break;
		}
		for(const auto& dir : directions) {
			const auto newPoint = Point(
				Vec2(current.Pos.X + dir.Pos.X, current.Pos.Y + dir.Pos.Y),
				current.Pos.X * (int32_t)grid[0].size() + current.Pos.Y,
				current.Steps + 1
			);
			if(!IsInBounds(grid, newPoint))
				continue;
			if(visited[newPoint.Pos.X][newPoint.Pos.Y])
				continue;
			if(grid[current.Pos.X][current.Pos.Y] > grid[newPoint.Pos.X][newPoint.Pos.Y] + 1)
				continue;
			stack.push(newPoint);
		}
	}
	timer.Print();
}

void Day12() {
	const auto data = Utils::ReadInputFile("Day12");
	Day12Part1(data);
	Day12Part2(data);
}