#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

const std::vector<std::pair<int, int>> directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void loadMap(const std::string &filename, std::vector<std::string> &map) {
  std::ifstream inputFile(filename);
  std::string line;
  while (getline(inputFile, line)) {
    map.push_back(line);
  }
  inputFile.close();
}

int simulateGuardPath(std::vector<std::string> &map) {
  int rows = map.size();
  int cols = map[0].size();

  int guardX = -1, guardY = -1, direction = 0;
  for (int i = 0; i < rows && guardX == -1; i++) {
    for (int j = 0; j < cols; ++j) {
      if (map[i][j] == '^') {
        guardX = i;
        guardY = j;
        direction = 0;
      } else if (map[i][j] == '>') {
        guardX = i;
        guardY = j;
        direction = 1;
      } else if (map[i][j] == 'v') {
        guardX = i;
        guardY = j;
        direction = 2;
      } else if (map[i][j] == '<') {
        guardX = i;
        guardY = j;
        direction = 3;
      }
    }
  }

  if (guardX == -1 || guardY == -1) {
    return -1;
  }

  std::set<std::pair<int, int>> visited;
  visited.insert({guardX, guardY});

  while (true) {
    int nextX = guardX + directions[direction].first;
    int nextY = guardY + directions[direction].second;

    if (nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols) {
      break;
    }

    if (map[nextX][nextY] == '#') {
      direction = (direction + 1) % 4;
    } else {
      guardX = nextX;
      guardY = nextY;
      visited.insert({guardX, guardY});
    }
  }

  return visited.size();
}

int main() {
  std::string filename = "data.txt";
  std::vector<std::string> map;
  loadMap(filename, map);

  int result = simulateGuardPath(map);
  if (result != -1) {
    std::cout << result << std::endl;
  }

  return 0;
}