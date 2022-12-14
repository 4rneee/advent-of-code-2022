#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include <set>

#include "../util.h"

using namespace std;

void init_cave(const string& file_name, set<pair<int, int>>& cave) {
    
    regex exp{"[0-9]+,[0-9]+"};
    smatch m;

    util::for_each_line(file_name, [&] (const string& line) {
        auto begin = sregex_iterator{line.begin(), line.end(), exp};
        auto end = sregex_iterator{};

        int fromX, fromY;

        for (auto i = begin; i != end; ++i) {
            string s{(*i).str()};
            unsigned commaIdx = s.find(',');
            int x{stoi(s.substr(0, commaIdx))};
            int y{stoi(s.substr(commaIdx+1))};

            if (i != begin) {
                while (fromX != x || fromY != y) {
                    cave.insert({fromX, fromY});
                    if (fromX < x)
                        ++fromX;
                    else if (fromX > x)
                        --fromX;

                    if (fromY < y)
                        ++fromY;
                    else if (fromY > y)
                        --fromY;
                }
                cave.insert({x, y});
            }
            fromX = x;
            fromY = y;
        }
    });
}

void star_1(std::string file_name) {
    set<pair<int, int>> cave{};
    init_cave(file_name, cave);

    int maxY = max_element(cave.begin(), cave.end(),
                           [] (const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; }
                           )->second;

    int result{0};

    while (1) {
        int x{500};
        int y{-1};

        while (1) {
            if (y >= maxY)
                goto done;

            if (!cave.contains({x, y+1}))
                ++y;
            else if (!cave.contains({x-1, y+1})) {
                --x;
                ++y;
            } else if (!cave.contains({x+1, y+1})) {
                ++x;
                ++y;
            } else {
                cave.insert({x, y});
                ++result;
                break;
            }
        }
    }

    done:

    std::cout << "Solution for Star 1:\n";
    std::cout << result << '\n';
}

void star_2(std::string file_name) {
    set<pair<int, int>> cave{};
    init_cave(file_name, cave);

    int maxY = max_element(cave.begin(), cave.end(), [] 
            (const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second; })->second;

    int result{0};

    while (!cave.contains({500, 0})) {
        int x{500};
        int y{-1};

        while (1) {
            if (y > maxY)
                goto insert;

            if (!cave.contains({x, y+1}))
                ++y;
            else if (!cave.contains({x-1, y+1})) {
                --x;
                ++y;
            } else if (!cave.contains({x+1, y+1})) {
                ++x;
                ++y;
            } else {
                insert:
                cave.insert({x, y});
                ++result;
                break;
            }
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
