#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>



bool xmas(std::vector<std::string> grid, int r, int c) {
  std::string diag1 = "";
  diag1 += grid[r][c];
  diag1 += grid[r + 1][c + 1];
  diag1 += grid[r + 2][c + 2];

  std::string diag2 = "";
  diag2 += grid[r][c + 2];
  diag2 += grid[r + 1][c + 1];
  diag2 += grid[r + 2][c];

  if ((diag1 == "MAS" || diag1 == "SAM") &&
      (diag2 == "MAS" || diag2 == "SAM")) {
    return true;
  }
  return false;
}

int main() {
  std::ifstream inputFile("data.txt");
  if (!inputFile.is_open()) {
    return 1;
  }

  std::string line;
  int sum = 0;
  std::vector<std::string> grid;

  while (getline(inputFile, line)) {
    grid.push_back(line);
  }
  inputFile.close();

  int row = grid.size();
  int col = grid[0].length();
  for (int r = 0; r < row - 2; ++r) {
    for (int c = 0; c < col - 2; ++c) {
      if (xmas(grid, r, c)) {
        sum++;
      }
    }
  }

  std::cout << sum << std::endl;

  return 0;
}