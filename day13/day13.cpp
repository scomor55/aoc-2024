#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <tuple>

std::vector<std::string> split(const std::string& str)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

void parseInput(std::fstream& inputFile, std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>>>& machines)
{
    std::string line;
    std::pair<int, int> buttonA, buttonB, prize;

    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            machines.push_back(std::make_tuple(buttonA, buttonB, prize));
            buttonA = buttonB = prize = std::make_pair(0, 0);
            continue;
        }

        std::vector<std::string> tokens = split(line);

        if (tokens[0] == "Button" && tokens[1] == "A:")
        {
            std::sscanf(tokens[2].c_str(), "X+%d", &buttonA.first);
            std::sscanf(tokens[3].c_str(), "Y+%d", &buttonA.second);
        }
        else if (tokens[0] == "Button" && tokens[1] == "B:")
        {
            std::sscanf(tokens[2].c_str(), "X+%d", &buttonB.first);
            std::sscanf(tokens[3].c_str(), "Y+%d", &buttonB.second);
        }
        else if (tokens[0] == "Prize:")
        {
            std::sscanf(tokens[1].c_str(), "X=%d", &prize.first);
            std::sscanf(tokens[2].c_str(), "Y=%d", &prize.second);
        }
    }

    machines.push_back(std::make_tuple(buttonA, buttonB, prize));
}

int calculateSolution(const std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>>>& machines, bool limitTo100 = false)
{
    int total = 0;

    for (const auto& machine : machines)
    {
        int resultA = 0, resultB = 0;

        auto buttonA = std::get<0>(machine);
        auto buttonB = std::get<1>(machine);
        auto prize = std::get<2>(machine);

        int x1 = buttonA.first, x2 = buttonA.second;
        int y1 = buttonB.first, y2 = buttonB.second;
        int p1 = prize.first, p2 = prize.second;

        int ky1 = -x2 * y1;
        int ky2 = x1 * y2;
        int kp1 = -x2 * p1;
        int kp2 = x1 * p2;

        int sumY = ky1 + ky2;
        int sumP = kp1 + kp2;

        if (sumY != 0 && sumP % sumY == 0)
        {
            resultB = sumP / sumY;
        }
        else
        {
            continue;
        }

        if ((p1 - resultB * y1) % x1 == 0)
        {
            resultA = (p2 - resultB * y2) / x2;
        }
        else
        {
            continue;
        }
        if (limitTo100 && (resultA > 100 || resultB > 100))
        {
            continue;
        }
        if (resultA >= 0 && resultB >= 0)
        {
            total += resultA * 3 + resultB;
        }
    }

    return total;
}

int main()
{
    // Open the input file
    std::fstream inputFile("input.txt", std::ios::in);
    if (!inputFile)
    {
        return 1;
    }

    std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>>> machines;

    parseInput(inputFile, machines);
    inputFile.close();

    std::cout << calculateSolution(machines, true) << std::endl;

    for (auto& machine : machines)
    {
        auto& prize = std::get<2>(machine);
        prize.first += 10000000000000;
        prize.second += 10000000000000;
    }

    std::cout << calculateSolution(machines) << std::endl;

    return 0;
}
