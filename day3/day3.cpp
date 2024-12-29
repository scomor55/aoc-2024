#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


int main() {
  std::ifstream inputFile;
  std::string ref = "mul(X,X)";
  std::string dostr = "do()";
  std::string dontstr = "don't()";

  int sum1 = 0;
  int sum2 = 0;

  inputFile.open("data.txt");

  if (inputFile.is_open()) {

    std::string line;
    bool enable = true;

    while (std::getline(inputFile, line)) {
      int index, index1, index2, temp, num1, num2, flag;
      index = index1 = index2 = temp = num1 = num2 = flag = 0;
      bool ifflag;

      // part 1
      for (int i = 0; i < line.size(); i++) {
        if (index < 4 && line[i] == ref[index])
          index++;
        else if (index == 4 && line[i] >= '0' && line[i] <= '9') {
          flag = 1;
          temp = temp * 10 + (line[i] - '0');

        } else if (line[i] == ',' && index == 4 && temp <= 999 && flag == 1) {
          num1 = temp;
          temp = 0;
          flag = 0;
          index++;
        } else if (index == 5 && line[i] >= '0' && line[i] <= '9') {
          flag = 1;
          temp = temp * 10 + (line[i] - '0');
        } else if (index == 5 && line[i] == ')' && temp <= 999 && flag == 1) {
          num2 = temp;
          sum1 += (num1 * num2);
          temp = index = flag = num1 = num2 = 0;
        } else {
          temp = index = flag = num1 = num2 = 0;
        }
      }

      // part 2
      for (int i = 0; i < line.size(); i++) {
        ifflag = true;

        if (line[i] == dostr[index1]) {
          index1++;
          ifflag = false;

          if (index1 == dostr.size()) {
            enable = true;
            index1 = 0;
          }
        } else {
          index1 = 0;
        }
        if (line[i] == dontstr[index2]) {
          index2++;
          ifflag = false;

          if (index2 == dontstr.size()) {
            enable = false;
            index2 = 0;
          }
        } else {
          index2 = 0;
          if (index < 4 && enable && ifflag && line[i] == ref[index])
            index++;

          else if (index == 4 && line[i] >= '0' && line[i] <= '9') {
            flag = 1;
            temp = temp * 10 + (line[i] - '0');
          } else if (line[i] == ',' && index == 4 && temp <= 999 && flag == 1) {
            num1 = temp;
            temp = flag = 0;
            index++;
          } else if (index == 5 && line[i] >= '0' && line[i] <= '9') {
            flag = 1;
            temp = temp * 10 + (line[i] - '0');
          } else if (index == 5 && line[i] == ')' && temp <= 999 && flag == 1) {
            num2 = temp;
            sum2 += (num1 * num2);
            temp = index = flag = num1 = num2 = 0;
          } else {
            temp = flag = index = num1 = num2 = 0;
          }
        }
      }
    }
  }
  std::cout << sum1 << std::endl;
  std::cout << sum2 << std::endl;
  return 0;
}


