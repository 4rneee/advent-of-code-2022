#include <iostream>
#include <string>
#include <vector>

#include "../util.h"

int get_priority(char item) {
    if (item >= 'a' && item <= 'z')
        return (item - 'a') + 1;
    else if (item >= 'A' && item <= 'Z')
        return (item - 'A') + 27;
    return 0;
}

void star_1(std::string file_name) {
    int result{0};
    util::for_each_line(file_name, [&result] (const std::string& line) {
        int len = line.length();
        for (int i{0}; i<len/2; ++i) {
            for (int j{len/2}; j<len; ++j) {
                if (line.at(i) == line.at(j)) {
                    result += get_priority(line.at(i));
                    goto done;
                }
            }
        }
        done:;
    });
    std::cout << "Result for star 1:\n" << result << '\n';
}

void star_2(std::string file_name) {
    int result{0};
    util::for_n_lines(file_name, 3, [&result] (const std::vector<std::string>& lines) {
        for (const auto& c1 : lines[0])
            for (const auto& c2 : lines[1])
                if (c1 == c2)
                    for (const auto& c3 : lines[2])
                        if (c1 == c3) {
                            result += get_priority(c1);
                            goto done;
                        }
            
        done:;
    });
    std::cout << "Result for star 2:\n" << result << '\n';
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
