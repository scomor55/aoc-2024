#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isSafeReport(const std::vector<int> &levels) {
  if (levels.size() < 2) {
    return true;
  }

  bool isIncreasing = true;
  bool isDecreasing = true;
  int badDiffCounter = 0;
  int isIncreasingCounter = 0;
  int isDecreasingCounter = 0;

  for (int i = 1; i < levels.size(); i++) {
    int diff = levels[i] - levels[i - 1];

    if (diff > 0) {
      isDecreasing = false;
      isIncreasingCounter++;
    } else if (diff < 0) {
      isIncreasing = false;
      isDecreasingCounter++;
    }
  }

  if (isDecreasingCounter == 1 && isIncreasingCounter > 1) {
    isIncreasing = true;
  }
  if (isIncreasingCounter == 1 && isDecreasingCounter > 1) {
    isDecreasing = true;
  }

  for (int i = 1; i < levels.size(); i++) {
    int diff = levels[i] - levels[i - 1];

    if (std::abs(diff) < 1 || std::abs(diff) > 3) {
      badDiffCounter++;
      if (badDiffCounter == 1 && std::abs(levels[i + 1] - levels[i - 1]) < 1 ||
          std::abs(levels[i + 1] - levels[i - 1]) > 3) {
        // std::cout << "---------" << std::endl;
        return false;
      }
      if (badDiffCounter > 1) {
        return false;
      }
    }
  }

  return isIncreasing || isDecreasing;
}

int main() {
  std::string filename = "data.txt";
  std::ifstream inputFile(filename);

  if (!inputFile.is_open()) {
    return 1;
  }

  int safeCount = 0;
  std::string line;

  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::vector<int> levels;
    int level;

    while (iss >> level) {
      levels.push_back(level);
    }

    if (isSafeReport(levels)) {
      safeCount++;
    }
  }

  inputFile.close();
  /*if (isSafeReport(levels)) {
    safeCount++;
  }*/
  std::cout << safeCount << std::endl;

  return 0;
}
