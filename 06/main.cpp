#include <cstdlib>
#include <iostream>
#include <string>
#include <set>

#include "../util.h"

void star_1(std::string file_name) {
    unsigned result{0};
    std::set<char> seq;
    util::for_each_line(file_name, [&result, &seq] (const std::string& line) {
        for (unsigned i{0}; i<line.length() - 4; ++i) {
            for (unsigned j{0}; j<4; ++j) {
                if (seq.contains(line[i+j])) {
                    break;
                } else {
                    seq.insert(line[i+j]);
                }
            }
            if (seq.size() == 4) {
                result = i+4;
                break;
            } else 
                seq.clear();
        }
    });
    std::cout << "Solution for Star 1:\n";
    std::cout << result << '\n';
}

void star_2(std::string file_name) {
    unsigned result{0};
    std::set<char> seq;
    util::for_each_line(file_name, [&result, &seq] (const std::string& line) {
        for (unsigned i{0}; i<line.length() - 4; ++i) {
            for (unsigned j{0}; j<14; ++j) {
                if (seq.contains(line[i+j])) {
                    break;
                } else {
                    seq.insert(line[i+j]);
                }
            }
            if (seq.size() == 14) {
                result = i+14;
                break;
            } else 
                seq.clear();
        }
    });
    std::cout << "Solution for Star 2:\n";
    std::cout << result << '\n';

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
