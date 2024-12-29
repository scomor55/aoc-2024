#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

bool customCompare(int x, int y, const std::set<std::pair<int, int>> &rules) {
  if (rules.count({x, y}))
    return true;
  if (rules.count({y, x}))
    return false;
  return x < y;
}

bool isPageSorted(const std::vector<int> &page,
                  const std::set<std::pair<int, int>> &rules) {
  auto comparator = [&rules](int a, int b) {
    return customCompare(a, b, rules);
  };
  std::vector<int> sortedPage = page;
  std::sort(sortedPage.begin(), sortedPage.end(), comparator);
  return page == sortedPage;
}

int getMiddleElement(const std::vector<int> &page) {
  return page[page.size() / 2];
}

int main() {
  std::ifstream file("data.txt");
  if (!file.is_open()) {
    return 1;
  }

  std::set<std::pair<int, int>> rules;
  std::vector<std::vector<int>> pages;
  std::string line;

  while (std::getline(file, line) && !line.empty()) {
    std::istringstream input(line);
    int a, b;
    char comma;
    if (input >> a >> comma >> b) {
      rules.insert({a, b});
    }
  }

  while (std::getline(file, line)) {
    std::istringstream input(line);
    std::vector<int> page;
    int num;
    while (input >> num) {
      page.push_back(num);
      if (input.peek() == ',') {
        input.ignore();
      }
    }
    pages.push_back(page);
  }

  file.close();

  int result1 = 0;
  int result2 = 0;

  for (const auto &page : pages) {
    if (isPageSorted(page, rules)) {
      result1 += getMiddleElement(page);
    } else {
      auto comparator = [&rules](int a, int b) {
        return customCompare(a, b, rules);
      };
      std::vector<int> sortedPage = page;
      std::sort(sortedPage.begin(), sortedPage.end(), comparator);
      result2 += getMiddleElement(sortedPage);
    }
  }

  std::cout << result1 << std::endl;
  std::cout << result2 << std::endl;

  return 0;
}