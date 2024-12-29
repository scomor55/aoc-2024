#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

const std::vector<std::string> directions = {"North", "East", "South", "West"};
const std::vector<std::pair<int, int>> moves = {
    {0, -1}, {1, 0}, {0, 1}, {-1, 0}};

struct State {
  int score, x, y, direction;
  State(int s, int x, int y, int dir) : score(s), x(x), y(y), direction(dir) {}
  bool operator>(const State &other) const { return score > other.score; }
};

std::tuple<std::vector<std::string>, std::pair<int, int>, std::pair<int, int>>
parseMaze(const std::string &filePath) {
  std::ifstream file(filePath);
  std::vector<std::string> maze;
  std::string line;
  std::pair<int, int> start, end;

  int y = 0;
  while (getline(file, line)) {
    maze.push_back(line);
    for (int x = 0; x < line.size(); x++) {
      if (line[x] == 'S')
        start = {x, y};
      if (line[x] == 'E')
        end = {x, y};
    }
    y++;
  }
  return {maze, start, end};
}

int reindeerMazeSolver(const std::vector<std::string> &maze,
                       std::pair<int, int> start, std::pair<int, int> end) {
  int width = maze[0].size();
  int height = maze.size();

  std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
  pq.emplace(0, start.first, start.second, 1);

  std::unordered_set<std::string> visited;

  while (!pq.empty()) {
    State current = pq.top();
    pq.pop();

    int score = current.score;
    int x = current.x;
    int y = current.y;
    int dir = current.direction;

    std::string stateKey =
        std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(dir);
    if (visited.count(stateKey))
      continue;
    visited.insert(stateKey);

    if (x == end.first && y == end.second)
      return score;

    int nx = x + moves[dir].first;
    int ny = y + moves[dir].second;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
        maze[ny][nx] != '#') {
      pq.emplace(score + 1, nx, ny, dir);
    }

    pq.emplace(score + 1000, x, y, (dir + 1) % 4);
    pq.emplace(score + 1000, x, y, (dir + 3) % 4);
  }

  return -1;
}

int main() {
  auto result = parseMaze("input.txt");
  std::vector<std::string> maze = std::get<0>(result);
  std::pair<int, int> start = std::get<1>(result);
  std::pair<int, int> end = std::get<2>(result);

  int lowestScore = reindeerMazeSolver(maze, start, end);
  std::cout << lowestScore << std::endl;

  return 0;
}