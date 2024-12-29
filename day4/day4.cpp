#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream inputFile("data.txt");
  if (!inputFile.is_open()) {
    return 1;
  }

  std::vector<std::string> grid;
  std::string line;
  while (getline(inputFile, line)) {
    grid.push_back(line);
  }
  inputFile.close();

  const std::string target = "XMAS";
  const std::vector<std::pair<int, int>> directions = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

  int matchCount = 0;
  int numRows = grid.size();
  int numCols = grid[0].size();

  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      if (grid[row][col] == 'X') {
        for (const auto &direction : directions) {
          int currentRow = row;
          int currentCol = col;
          bool isMatch = true;

          for (int i = 1; i < target.size(); ++i) {
            currentRow += direction.first;
            currentCol += direction.second;

            if (currentRow >= 0 && currentRow < numRows && currentCol >= 0 &&
                currentCol < numCols &&
                grid[currentRow][currentCol] == target[i]) {
              continue;
            } else {
              isMatch = false;
              break;
            }
          }

          if (isMatch) {
            ++matchCount;
          }
        }
      }
    }
  }

  std::cout << matchCount << std::endl;
  return 0;
}
