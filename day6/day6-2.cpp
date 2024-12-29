#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::vector<std::pair<int, int>> directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::vector<std::vector<char>> inputToPlayingField(const std::vector<std::string> &input) {
  std::vector<std::vector<char>> field;
  for (const std::string &line : input) {
    std::vector<char> row(line.begin(), line.end());
    field.push_back(row);
  }
  return field;
}

std::pair<int, int> findGuard(const std::vector<std::vector<char>> &field) {
  for (int x = 0; x < field.size(); ++x) {
    for (int y = 0; y < field[0].size(); ++y) {
      if (field[x][y] == '^') {
        return {x, y};
      }
    }
  }
  return {-1, -1};
}

bool isInBounds(const std::pair<int, int> &pos,
                const std::vector<std::vector<char>> &field) {
  return pos.first >= 0 && pos.second >= 0 && pos.first < field.size() &&
         pos.second < field[0].size();
}

bool isObstacle(const std::pair<int, int> &pos,
                const std::vector<std::vector<char>> &field) {
  return field[pos.first][pos.second] == '#';
}

bool checkLoop(std::vector<std::vector<char>> &field,
               std::pair<int, int> guard) {
  std::map<std::string, bool> visitedSquaresAndRotations;
  int dir = 0;

  while (true) {
    std::string key = std::to_string(guard.first) + "," +
                      std::to_string(guard.second) + "," + std::to_string(dir);
    if (visitedSquaresAndRotations.find(key) !=
        visitedSquaresAndRotations.end()) {
      return true;
    }

    visitedSquaresAndRotations[key] = true;

    std::pair<int, int> step = {guard.first + directions[dir].first,
                                guard.second + directions[dir].second};

    if (!isInBounds(step, field)) {
      return false;
    }
    if (isObstacle(step, field)) {
      dir = (dir + 1) % 4;
    } else {
      guard = step;
    }
  }
}

int main() {
  std::string filename = "data.txt";
  std::ifstream inFile(filename);
  
  std::vector<std::string> input;
  std::string line;
  while (getline(inFile, line)) {
    input.push_back(line);
  }

  std::vector<std::vector<char>> field = inputToPlayingField(input);

  std::pair<int, int> guard = findGuard(field);
  if (guard.first == -1 && guard.second == -1) {
    return -1;
  }

  int counter = 0;
  for (int x = 0; x < field.size(); ++x) {
    for (int y = 0; y < field[0].size(); ++y) {
      if (field[x][y] == '.') {
        field[x][y] = '#';

        if (checkLoop(field, guard)) {
          counter++;
        }

        field[x][y] = '.';
      }
    }
  }

  std::cout << counter << std::endl;
  return 0;
}