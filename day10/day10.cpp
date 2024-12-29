#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

std::vector<std::vector<int>> readMap(const std::string &filePath) {
  std::vector<std::vector<int>> map;
  std::ifstream file(filePath);
  std::string line;
  while (std::getline(file, line)) {
    std::vector<int> row;
    for (char c : line) {
      row.push_back(c - '0');
    }
    map.push_back(row);
  }
  return map;
}

std::vector<std::pair<int, int>>
findTrailheads(const std::vector<std::vector<int>> &topographicMap) {
  std::vector<std::pair<int, int>> trailheads;
  int rows = topographicMap.size();
  int cols = topographicMap[0].size();

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (topographicMap[row][col] == 0) {
        trailheads.push_back(std::make_pair(row, col));
      }
    }
  }
  return trailheads;
}

bool isValidMove(int currentHeight, int nextHeight) {
  return nextHeight == currentHeight + 1;
}

int exploreTrail(const std::vector<std::vector<int>> &topographicMap,
                 std::pair<int, int> start) {
  int rows = topographicMap.size();
  int cols = topographicMap[0].size();
  std::set<std::pair<int, int>> visited;
  std::queue<std::pair<int, int>> queue;
  std::set<std::pair<int, int>> reachableNines;

  queue.push(start);

  while (!queue.empty()) {
    std::pair<int, int> current = queue.front();
    queue.pop();

    int x = current.first;
    int y = current.second;

    if (visited.count(current)) {
      continue;
    }

    visited.insert(current);
    int currentHeight = topographicMap[x][y];

    if (currentHeight == 9) {
      reachableNines.insert(current);
    }

    std::vector<std::pair<int, int>> directions = {
        std::make_pair(-1, 0), std::make_pair(1, 0), std::make_pair(0, -1),
        std::make_pair(0, 1)};
    for (const auto &direction : directions) {
      int nx = x + direction.first;
      int ny = y + direction.second;

      if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
        int nextHeight = topographicMap[nx][ny];

        if (isValidMove(currentHeight, nextHeight)) {
          queue.push(std::make_pair(nx, ny));
        }
      }
    }
  }

  return reachableNines.size();
}

int calculateTotalScore(const std::string &filePath) {
  std::vector<std::vector<int>> topographicMap = readMap(filePath);
  std::vector<std::pair<int, int>> trailheads = findTrailheads(topographicMap);

  int totalScore = 0;
  for (const auto &trailhead : trailheads) {
    totalScore += exploreTrail(topographicMap, trailhead);
  }

  return totalScore;
}

int main() {
  std::string inputFile = "input.txt";
  int totalScore = calculateTotalScore(inputFile);
  std::cout << totalScore << std::endl;
  return 0;
}