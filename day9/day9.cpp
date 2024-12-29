#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

struct Entry {
  int start;
  int size;
};

struct ParsedData {
  std::vector<int> blocks;
  std::vector<Entry> filetab;
  std::vector<Entry> spacetab;
};

ParsedData parseToBlocks(const std::string &filename) {
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    exit(1);
  }

  std::string line((std::istreambuf_iterator<char>(ifs)),
                   std::istreambuf_iterator<char>());
  if (!line.empty() && line.back() == '\n') {
    line.pop_back();
  }

  std::vector<int> blocks;
  std::vector<Entry> filetab;
  std::vector<Entry> spacetab;

  bool isfile = true;
  for (char c : line) {
    int size = c - '0';

    if (isfile) {
      int fileid = filetab.size();
      filetab.push_back(
          {static_cast<int>(blocks.size()), static_cast<int>(size)});
      blocks.insert(blocks.end(), size, static_cast<int>(fileid));
    } else {
      spacetab.push_back(
          {static_cast<int>(blocks.size()), static_cast<int>(size)});
      blocks.insert(blocks.end(), size, -1);
    }

    isfile = !isfile;
  }

  return {blocks, filetab, spacetab};
}

void compact(std::vector<int> &blocks) {
  auto next_free = blocks.begin();
  auto next_file = blocks.rbegin();

  while (true) {
    next_free = std::find_if(next_free, blocks.end(),
                             [](const auto &el) { return el < 0; });
    next_file = std::find_if(next_file, blocks.rend(),
                             [](const auto &el) { return el >= 0; });

    if (std::make_reverse_iterator(next_free) <= next_file)
      return;

    std::swap(*next_free, *next_file);

    ++next_free;
    ++next_file;
  }
}

void compactWhole(std::vector<Entry> &filetab, std::vector<Entry> &spacetab) {
  for (int fileid = filetab.size() - 1; fileid > 0; --fileid) {
    auto &file = filetab[fileid];

    auto free =
        std::find_if(spacetab.begin(), spacetab.end(), [&file](const Entry &e) {
          return e.size >= file.size && e.start < file.start;
        });

    if (free != spacetab.end()) {
      file.start = free->start;
      *free = {free->start + file.size, free->size - file.size};
    }
  }
}

long long checksumBlocks(std::vector<int> &blocks) {
  int idx = -1;
  return std::accumulate(blocks.begin(), blocks.end(), 0LL,
                         [&idx](long long sum, int el) {
                           ++idx;
                           if (el >= 0) {
                             return sum + el * idx;
                           } else {
                             return sum;
                           }
                         });
}

long long checksumFiletab(const std::vector<Entry> &filetab) {
  long long sum = 0;

  for (unsigned fileid = 0; fileid < filetab.size(); ++fileid) {
    const auto &file = filetab[fileid];
    for (unsigned i = file.start;
         i < static_cast<unsigned>(file.start + file.size); ++i) {
      sum += i * fileid;
    }
  }

  return sum;
}

int main(int argc, char *argv[]) {

  ParsedData data = parseToBlocks("input.txt");

  {
    compact(data.blocks);
    auto result1 = checksumBlocks(data.blocks);
    std::cout << result1 << std::endl;
  }

  {
    compactWhole(data.filetab, data.spacetab);
    auto result2 = checksumFiletab(data.filetab);
    std::cout << result2 << std::endl;
  }

  return 0;
}
