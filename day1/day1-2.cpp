#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <new>
#include <stdexcept>
#include <utility>
#include <vector>

int calculateTotalDistance(std::vector<int> &leftList,
                           std::vector<int> &rightList) {

  std::sort(leftList.begin(), leftList.end());
  std::sort(rightList.begin(), rightList.end());
  int score = 0;

  for (int num : leftList) {
    int count = std::count(rightList.begin(), rightList.end(), num);
    score += num * count;
  }

  return score;
}

int main() {

  std::ifstream inputFile("input.txt");
  if (!inputFile) {
    return 1;
  }

  std::vector<int> leftList;
  std::vector<int> rightList;

  int leftValue, rightValue;

  while (inputFile >> leftValue >> rightValue) {
    leftList.push_back(leftValue);
    rightList.push_back(rightValue);
  }

  inputFile.close();
  if (leftList.size() != rightList.size()) {
    return 1;
  }
  int totalDistance = calculateTotalDistance(leftList, rightList);

  std::cout << totalDistance << std::endl;

  return 0;
}