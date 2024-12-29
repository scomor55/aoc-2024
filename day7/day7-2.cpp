#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

bool evaluateExpression(const std::vector<long long> &numbers,
                        const std::vector<std::string> &operators,
                        long long target) {
  long long result = numbers[0];
  for (int i = 0; i < operators.size(); i++) {
    if (operators[i] == "+") {
      result += numbers[i + 1];
    } else if (operators[i] == "*") {
      result *= numbers[i + 1];
    } else if (operators[i] == "||") {
      result =
          std::stoll(std::to_string(result) + std::to_string(numbers[i + 1]));
    }
  }
  return result == target;
}

bool checkEquation(const std::vector<long long> &numbers, long long target,
                   int index, std::vector<std::string> &operators) {

  if (index == numbers.size() - 1) {
    return evaluateExpression(numbers, operators, target);
  }

  operators[index] = "+";
  if (checkEquation(numbers, target, index + 1, operators)) {
    return true;
  }

  operators[index] = "*";
  if (checkEquation(numbers, target, index + 1, operators)) {
    return true;
  }

  operators[index] = "||";
  if (checkEquation(numbers, target, index + 1, operators)) {
    return true;
  }
  return false;
}

int main() {

  std::ifstream inputFile("input.txt");
  if (!inputFile.is_open()) {
    return 1;
  }
  long long totalCalibrationResult = 0;
  std::string line;

  while (std::getline(inputFile, line)) {
    std::istringstream lineStream(line);
    std::string keyStr, numbersPart;

    std::getline(lineStream, keyStr, ':');
    long long target;
    try {
      target = std::stoll(keyStr);
    } catch (const std::exception &e) {
      continue;
    }

    std::getline(lineStream, numbersPart);
    std::istringstream numbersStream(numbersPart);
    std::vector<long long> numbers;

    long long num;
    while (numbersStream >> num) {
      numbers.push_back(num);
    }

    std::vector<std::string> operators(numbers.size() - 1);
    if (checkEquation(numbers, target, 0, operators)) {
      totalCalibrationResult += target;
    }
  }

  inputFile.close();
  std::cout << totalCalibrationResult << std::endl;
  return 0;
}