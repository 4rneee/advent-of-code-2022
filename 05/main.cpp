#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <array>
#include <vector>

#include "../util.h"

void star_1(std::string file_name) {
    std::array<std::stack<char>, 9> stacks{
        std::stack<char>({'V', 'C', 'D', 'R', 'Z', 'G', 'B', 'W'}),
        std::stack<char>({'G', 'W', 'F', 'C', 'B', 'S', 'T', 'V'}),
        std::stack<char>({'C', 'B', 'S', 'N', 'W'}),
        std::stack<char>({'Q', 'G', 'M', 'N', 'J', 'V', 'C', 'P'}),
        std::stack<char>({'T', 'S', 'L', 'F', 'D', 'H', 'B'}),
        std::stack<char>({'J', 'V', 'T', 'W', 'M', 'N'}),
        std::stack<char>({'P', 'F', 'L', 'C', 'S', 'T', 'G'}),
        std::stack<char>({'B', 'D', 'Z'}),
        std::stack<char>({'M', 'N', 'Z', 'W'}),
    };

    util::for_each_line(file_name, [&stacks] (const std::string& line) {
        int moves = std::stoi(line.substr(5, line.find(" from") - 5));
        int from = line.at(line.find("from") + 5) - '0';
        int to = line.at(line.find("to") + 3) - '0';
        for (int i{0}; i<moves; ++i) {
            stacks[to-1].push(stacks[from-1].top());
            stacks[from-1].pop();
        }
    });
    std::cout << "Solution for Star 1:\n";
    for (const auto& s : stacks)
        std::cout << s.top();
    std::cout << '\n';
}

void star_2(std::string file_name) {
    std::array<std::stack<char>, 9> stacks{
        std::stack<char>({'V', 'C', 'D', 'R', 'Z', 'G', 'B', 'W'}),
        std::stack<char>({'G', 'W', 'F', 'C', 'B', 'S', 'T', 'V'}),
        std::stack<char>({'C', 'B', 'S', 'N', 'W'}),
        std::stack<char>({'Q', 'G', 'M', 'N', 'J', 'V', 'C', 'P'}),
        std::stack<char>({'T', 'S', 'L', 'F', 'D', 'H', 'B'}),
        std::stack<char>({'J', 'V', 'T', 'W', 'M', 'N'}),
        std::stack<char>({'P', 'F', 'L', 'C', 'S', 'T', 'G'}),
        std::stack<char>({'B', 'D', 'Z'}),
        std::stack<char>({'M', 'N', 'Z', 'W'}),
    };

    util::for_each_line(file_name, [&stacks] (const std::string& line) {
        int moves = std::stoi(line.substr(5, line.find(" from") - 5));
        int from = line.at(line.find("from") + 5) - '0';
        int to = line.at(line.find("to") + 3) - '0';
        std::vector<char> tmp;
        for (int i{0}; i<moves; ++i) {
            tmp.push_back(stacks[from-1].top());
            stacks[from-1].pop();
        }
        for (int i{moves - 1}; i >= 0; --i)
            stacks[to-1].push(tmp[i]);
    });
    std::cout << "Solution for Star 2:\n";
    for (const auto& s : stacks)
        std::cout << s.top();
    std::cout << '\n';

}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "No input file given\n";
        return 1;
    }
    star_1(std::string(argv[1]));
    star_2(std::string(argv[1]));
    return 0;
}
