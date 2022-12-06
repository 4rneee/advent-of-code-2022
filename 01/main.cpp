#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
#include "../util.h"

void star1(std::string file_name) {
    unsigned maxCallories{0};
    unsigned currentCallories{0};
    util::for_each_line(file_name, [&maxCallories, &currentCallories] (const std::string& line) {
        if (line.empty()) {
            maxCallories = std::max(maxCallories, currentCallories);
            currentCallories = 0;
        } else {
            currentCallories += std::stoul(line);
        }
    });
    std::cout << "Solution star 1:\n" << maxCallories << '\n';
}

void star2(std::string file_name) {
    unsigned first{0};
    unsigned second{0};
    unsigned third{0};
    unsigned currentCallories{0};
    util::for_each_line(file_name, [&first, &second, &third, &currentCallories] (const std::string& line) {
        if (line.empty()) {
            unsigned long tmp;
            if (currentCallories > first) {
                third = second;
                second = first;
                first = currentCallories;
            } else if (currentCallories > second) {
                third = second;
                second = currentCallories;
            } else if (currentCallories > third) {
                third = currentCallories;
            }
            currentCallories = 0;
        } else {
            currentCallories += std::stoul(line);
        }
    });
    std::cout << "Solution star 2:\n" << first + second + third << '\n';
}

int main() {
    star1("input.txt");
    star2("input.txt");
    return 0;
}
