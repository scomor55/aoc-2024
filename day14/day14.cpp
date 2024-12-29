#include <cmath>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

const int GRID_WIDTH = 101;
const int GRID_HEIGHT = 103;
const int TIME = 100;

int determineQuadrant(int x, int y, int midX, int midY) {
  if (x == midX || y == midY)
    return 0;
  if (x < midX && y < midY)
    return 1;
  if (x > midX && y < midY)
    return 2;
  if (x < midX && y > midY)
    return 3;
  if (x > midX && y > midY)
    return 4;
  return 0;
}

int main() {
  std::ifstream inputFile("input.txt");
  if (!inputFile) {
    return 1;
  }

  std::vector<std::tuple<int, int, int, int>> robots;
  std::string line;

  while (getline(inputFile, line)) {
    int px, py, vx, vy;
    sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
    robots.emplace_back(px, py, vx, vy);
  }

  inputFile.close();

  std::vector<std::pair<int, int>> finalPositions;
  for (auto &robot : robots) {
    int px, py, vx, vy;
    std::tie(px, py, vx, vy) = robot;

    int finalX = (px + vx * TIME) % GRID_WIDTH;
    int finalY = (py + vy * TIME) % GRID_HEIGHT;

    if (finalX < 0)
      finalX += GRID_WIDTH;
    if (finalY < 0)
      finalY += GRID_HEIGHT;

    finalPositions.emplace_back(finalX, finalY);
  }

  int midX = GRID_WIDTH / 2;
  int midY = GRID_HEIGHT / 2;
  int quadrantCounts[5] = {0};

  for (auto &pos : finalPositions) {
    int x, y;
    std::tie(x, y) = pos;

    int quadrant = determineQuadrant(x, y, midX, midY);
    if (quadrant != 0) {
      quadrantCounts[quadrant]++;
    }
  }

  int safetyFactor = quadrantCounts[1] * quadrantCounts[2] * quadrantCounts[3] *
                     quadrantCounts[4];

  std::cout << safetyFactor << std::endl;

  return 0;
}