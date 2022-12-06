#include <iostream>
#include <string>
#include <utility>

#include "../util.h"

std::pair<std::string, std::string> get_ranges_as_string(const std::string& s) {
    int comma_index = s.find(',');
    std::string first_range = s.substr(0, comma_index);
    std::string second_range = s.substr(comma_index+1);
    return std::make_pair(first_range, second_range);
}

std::pair<int, int> get_range(std::string s) {
    int dash_index = s.find('-');
    int lower = std::stoi(s.substr(0, dash_index));
    int higher = std::stoi(s.substr(dash_index+1));
    return std::make_pair(lower, higher);
}

void star_1(std::string file_name) {
    int result{0};
    util::for_each_line(file_name, [&result] (const std::string& line) {
        auto ranges = get_ranges_as_string(line);
        auto r1 = get_range(ranges.first);
        auto r2 = get_range(ranges.second);
        if ((r1.first <= r2.first && r1.second >= r2.second) || (r2.first <= r1.first && r2.second >= r1.second))
            ++result;
    });
    std::cout << "Result for star 1:\n" << result << '\n';
}

bool in_range(std::pair<int, int> r, int n) {
    return n >= r.first && n <= r.second;
}

void star_2(std::string file_name) {
    int result{0};
    util::for_each_line(file_name, [&result] (std::string line) {
        auto ranges = get_ranges_as_string(line);
        auto r1 = get_range(ranges.first);
        auto r2 = get_range(ranges.second);
        if (in_range(r1, r2.first) || in_range(r1, r2.second) || in_range(r2, r1.first) || in_range(r2, r1.second) )
            ++result;
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
