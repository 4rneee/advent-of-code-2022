#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "../util.h"


void star_1(std::string file_name) {
    auto optLines = util::get_all_lines(file_name);
    if (!optLines)
        return;

    auto lines = optLines.value();

    unsigned result{0};
    for (int i{1}; i<lines.size()-1; ++i) {
        for (int j{1}; j<lines.at(i).size()-1; ++j) {
            // check left
            for (int k{j-1}; k>=0; --k)
                if (lines.at(i).at(k) >= lines.at(i).at(j))
                    goto check_top;

            goto visible;

            check_top:
            for (int k{i-1}; k>=0; --k)
                if (lines.at(k).at(j) >= lines.at(i).at(j))
                    goto check_right;

            goto visible;

            check_right:
            for (int k{j+1}; k<lines.at(i).size(); ++k)
                if (lines.at(i).at(k) >= lines.at(i).at(j))
                    goto check_bottom;

            goto visible;

            check_bottom:
            for (int k{i+1}; k<lines.size(); ++k)
                if (lines.at(k).at(j) >= lines.at(i).at(j))
                    goto cont;

            goto visible;

            cont:
                continue;

            visible:
                ++result;
        }
    }
    // add edges
    result += 2*lines.size() + 2*lines.at(0).size() - 4;
    std::cout << "Solution for Star 1:\n";
    std::cout << result << '\n';
}

void star_2(std::string file_name) {
    auto optLines = util::get_all_lines(file_name);
    if (!optLines)
        return;

    auto lines = optLines.value();

    unsigned result{0};
    for (int i{1}; i<lines.size()-1; ++i) {
        for (int j{1}; j<lines.at(i).size()-1; ++j) {
            unsigned score{1};
            // check left
            for (int k{j-1}; k>=0; --k)
                if (k == 0 || lines.at(i).at(k) >= lines.at(i).at(j)) {
                    score *= (j-k);
                    break;
                }
            
            // check top
            for (int k{i-1}; k>=0; --k)
                if (k == 0 || lines.at(k).at(j) >= lines.at(i).at(j)) {
                    score *= (i-k);
                    break;
                }

            // check right
            for (int k{j+1}; k<lines.at(i).size(); ++k)
                if (k == lines.at(i).size()-1 || lines.at(i).at(k) >= lines.at(i).at(j)) {
                    score *= (k-j);
                    break;
                }

            // check botttom
            for (int k{i+1}; k<lines.size(); ++k)
                if (k == lines.size()-1 || lines.at(k).at(j) >= lines.at(i).at(j)) {
                    score *= (k-i);
                    break;
                }

            if (score > result)
                result = score;
        }
    }
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
