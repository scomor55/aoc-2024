#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define SIZE 50

std::vector<std::string> map(SIZE);

bool move(int x, int y, int vx, int vy) {
  switch (map[y + vy][x + vx]) {
  case 'O': {
    bool result = move(x + vx, y + vy, vx, vy);
    if (!result)
      return false;
  }
  case '.':
    map[y + vy][x + vx] = map[y][x];
    map[y][x] = '.';
    return true;
  case '#':
    return false;
  }
  return true;
}

int main() {
  std::ifstream file("input.txt");
  if (!file) {
    return 1;
  }

  for (int i = 0; i < SIZE; i++) {
    file >> map[i];
  }

  int x = -1, y = -1;
  for (y = 0; y < SIZE; y++) {
    for (x = 0; x < SIZE; x++) {
      if (map[y][x] == '@')
        goto found;
    }
  }
found:;

  for (const auto &row : map) {
    std::cout << row << '\n';
  }
  std::cout << std::endl;

  char c;
  while (file.get(c)) {
    int vx = 0, vy = 0;

    switch (c) {
    case '<':
      vx = -1;
      vy = 0;
      break;
    case '>':
      vx = 1;
      vy = 0;
      break;
    case '^':
      vx = 0;
      vy = -1;
      break;
    case 'v':
      vx = 0;
      vy = 1;
      break;
    default:
      continue;
    }

    if (move(x, y, vx, vy)) {
      x += vx;
      y += vy;
    }
  }

  long sum = 0;
  for (int y = 0; y < SIZE; y++) {
    for (int x = 0; x < SIZE; x++) {
      if (map[y][x] == 'O') {
        sum += 100 * y + x;
      }
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
