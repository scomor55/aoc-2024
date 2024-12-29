#include <fstream>
#include <iostream>

struct Stone {
  long value;
  Stone *next;
};

int numDigits(long n) {
  int digits = 0;
  while (n != 0) {
    n /= 10;
    digits++;
  }
  return digits;
}

void printList(Stone *start) {
  for (auto s = start; s != nullptr; s = s->next) {
    std::cout << s->value << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ifstream inputFile("input.txt");
  if (!inputFile) {
    return 1;
  }

  Stone *start = new Stone();
  Stone *end = start;
  long num;

  while (inputFile >> num) {
    end->value = num;
    if (inputFile.peek() != EOF) {
      end->next = new Stone();
      end = end->next;
    }
  }

  inputFile.close();

  for (int i = 0; i < 25; ++i) {
    auto s = start;
    while (s != nullptr) {
      auto next = s->next;
      if (s->value == 0) {
        s->value = 1;
      } else {
        int digits = numDigits(s->value);
        if (digits % 2 == 0) {
          long place = 1;
          for (int j = 0; j < digits / 2; ++j) {
            place *= 10;
          }
          long num1 = s->value / place;
          long num2 = s->value % place;
          s->value = num1;

          Stone *newNode = new Stone();
          newNode->value = num2;
          newNode->next = s->next;
          s->next = newNode;
        } else {
          s->value *= 2024;
        }
      }
      s = next;
    }
  }

  int count = 0;
  for (auto s = start; s != nullptr; s = s->next) {
    count++;
  }

  std::cout << count << std::endl;

  Stone *current = start;
  while (current != nullptr) {
    Stone *next = current->next;
    delete current;
    current = next;
  }

  return 0;
}