#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include <fstream>

struct Position {
  int x, y;
  Position(int x, int y) : x(x), y(y) {}
  bool operator<(const Position &other) const {
    return std::tie(x, y) < std::tie(other.x, other.y);
  }
};

std::map<char, std::vector<Position>>
parseMap(const std::vector<std::string> &grid) {
  std::map<char, std::vector<Position>> antennas;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {

      char freq = grid[i][j];
      if (freq != '.') {
        antennas[freq].emplace_back(i, j);
      }
    }
  }
  return antennas;
}

int calculateAntinodes(const std::vector<std::string> &grid) {
  auto antennas = parseMap(grid);
  std::set<Position> antinodePositions;

  for (const auto &[freq, positions] : antennas) {
    int n = positions.size();
    for (int i = 0; i < n; i++) {
      antinodePositions.insert(positions[i]);

      for (int j = i + 1; j < n; j++) {
        int dx = positions[j].x - positions[i].x;
        int dy = positions[j].y - positions[i].y;

        for (int k = -1; k <= 1; k += 2) {
          int nx = positions[j].x + k * dx;
          int ny = positions[j].y + k * dy;

          while (nx >= 0 && ny >= 0 && nx < grid.size() &&
                 ny < grid[0].size()) {
            antinodePositions.insert(Position(nx, ny));
            nx += k * dx;
            ny += k * dy;
          }
        }
      }
    }
  }

  return antinodePositions.size();
}

int main() {
  std::ifstream inFile("input.txt");
  std::vector<std::string> grid;
  std::string line;

  // Read grid from file
  while (std::getline(inFile, line)) {
    grid.push_back(line);
  }

  std::cout << calculateAntinodes(grid) << std::endl;

  return 0;
}