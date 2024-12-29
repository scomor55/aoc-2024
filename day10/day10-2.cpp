#include <algorithm>
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
                 std::pair<int, int> start,
                 std::set<std::vector<std::pair<int, int>>> &distinctTrails) {
  int rows = topographicMap.size();
  int cols = topographicMap[0].size();
  std::queue<std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>>
      queue;
  std::set<std::pair<int, int>> visited;

  queue.push(std::make_pair(start, std::vector<std::pair<int, int>>{start}));

  while (!queue.empty()) {
    auto currentPair = queue.front();
    queue.pop();

    auto current = currentPair.first;
    auto path = currentPair.second;

    int x = current.first;
    int y = current.second;
    int currentHeight = topographicMap[x][y];

    if (currentHeight == 9) {
      distinctTrails.insert(path);
    }

    std::vector<std::pair<int, int>> directions = {
        std::make_pair(-1, 0), std::make_pair(1, 0), std::make_pair(0, -1),
        std::make_pair(0, 1)};
    for (const auto &direction : directions) {
      int nx = x + direction.first;
      int ny = y + direction.second;
      if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
        int nextHeight = topographicMap[nx][ny];
        if (isValidMove(currentHeight, nextHeight) &&
            std::find(path.begin(), path.end(), std::make_pair(nx, ny)) ==
                path.end()) {
          auto newPath = path;
          newPath.push_back(std::make_pair(nx, ny));
          queue.push(std::make_pair(std::make_pair(nx, ny), newPath));
        }
      }
    }
  }

  return distinctTrails.size();
}

int calculateTotalRating(const std::string &filePath) {
  std::vector<std::vector<int>> topographicMap = readMap(filePath);
  std::vector<std::pair<int, int>> trailheads = findTrailheads(topographicMap);

  int totalRating = 0;
  for (const auto &trailhead : trailheads) {
    std::set<std::vector<std::pair<int, int>>> distinctTrails;
    totalRating += exploreTrail(topographicMap, trailhead, distinctTrails);
  }

  return totalRating;
}

int main() {
  std::string inputFile = "input.txt";
  int totalRating = calculateTotalRating(inputFile);
  std::cout << totalRating << std::endl;
  return 0;
}