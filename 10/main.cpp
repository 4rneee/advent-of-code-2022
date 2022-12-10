#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>

#include "../util.h"

void star_1(std::string file_name) {
    int result{0};
    int x{1};
    int cycle{0};

    util::for_each_line(file_name, [&x, &cycle, &result] (const std::string line) {
        if (line == "noop") {
            if ((++cycle - 20) % 40 == 0)
                result += cycle * x;
        } else {
            int add = std::stoi(line.substr(line.find(' ')+1));
            if ((++cycle - 20) % 40 == 0)
                result += cycle * x;
            
            if ((++cycle - 20) % 40 == 0)
                result += cycle * x;

            x += add;
        }
    });

    std::cout << "Solution for Star 1:\n";
    std::cout << result << '\n';
}

void draw(int cycle, int x) {
    int pixel = (cycle-1) % 40;
    if (pixel == 0)
        std::cout << '\n';

    if (pixel >= x-1 && pixel <= x+1)
        std::cout << '#';
    else
        std::cout << '.';
}

void star_2(std::string file_name) {
    std::cout << "Solution for Star 2:\n";

    int x{1};
    int cycle{0};
    util::for_each_line(file_name, [&x, &cycle] (const std::string line) {
        if (line == "noop") {
            draw(++cycle, x);

        } else {
            int add = std::stoi(line.substr(line.find(' ')+1));
            draw(++cycle, x);
            draw(++cycle, x);
            x += add;
        }
    });
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
