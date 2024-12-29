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

  int totalDistance = 0;

  for (int i = 0; i < leftList.size(); ++i) {
    totalDistance += std::abs(leftList[i] - rightList[i]);
  }
  return totalDistance;
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