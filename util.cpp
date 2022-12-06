#include <cstddef>
#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <fstream>
#include <iostream>
#include "util.h"

namespace util {

void for_each_line(std::string file_name, const std::function<void(const std::string&)>& f) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line))
            f(line);

        file.close();
    } else
        std::cout << "Unable to open file\n";
}

void for_n_lines(std::string file_name, size_t n, const std::function<void(const std::vector<std::string>&)>& f) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line)) {
            lines.push_back(line);
            if (lines.size() == n) {
                f(lines);
                lines.clear();
            }
        }
        file.close();
    } else
        std::cout << "Unable to open file\n";
}

}