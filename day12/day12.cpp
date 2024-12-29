#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Region {
  char type;
  int area;
  int perimeter;
};

bool isValid(int x, int y, int rows, int cols) {
  return x >= 0 && x < rows && y >= 0 && y < cols;
}

void bfs(int startX, int startY, std::vector<std::vector<char>> &grid,
         std::vector<std::vector<bool>> &visited, Region &region) {
  int rows = grid.size();
  int cols = grid[0].size();
  std::queue<std::pair<int, int>> q;
  q.push({startX, startY});
  visited[startX][startY] = true;
  char plantType = grid[startX][startY];

  region.type = plantType;
  region.area = 0;
  region.perimeter = 0;

  while (!q.empty()) {
    // auto [x, y] = q.front();
    std::pair<int, int> current = q.front();
    q.pop();
    int x = current.first;
    int y = current.second;
    region.area++;

    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (isValid(nx, ny, rows, cols)) {
        if (grid[nx][ny] == plantType && !visited[nx][ny]) {
          visited[nx][ny] = true;
          q.push({nx, ny});
        } else if (grid[nx][ny] != plantType) {
          region.perimeter++;
        }
      } else {
        region.perimeter++;
      }
    }
  }
}

int main() {
  std::ifstream inputFile("input.txt");
  if (!inputFile) {
    return 1;
  }

  std::vector<std::vector<char>> grid;
  std::string line;

  while (getline(inputFile, line)) {
    std::vector<char> row(line.begin(), line.end());
    grid.push_back(row);
  }

  inputFile.close();

  int rows = grid.size();
  int cols = grid[0].size();
  std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

  std::vector<Region> regions;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (!visited[i][j]) {
        Region region;
        bfs(i, j, grid, visited, region);
        regions.push_back(region);
      }
    }
  }

  int totalPrice = 0;
  for (const auto &region : regions) {
    int price = region.area * region.perimeter;
    totalPrice += price;
  }

  std::cout << totalPrice << std::endl;
  return 0;
}
