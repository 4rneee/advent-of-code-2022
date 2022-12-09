#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <set>
#include <array>

#include "../util.h"

using namespace std;

void move(pair<int, int>& h, pair<int, int>& t, const char dir) {
    switch (dir) {
        case 'R': ++h.first; break;
        case 'L': --h.first; break;
        case 'U': ++h.second; break;
        case 'D': --h.second; break;
    }

    int xDiff = h.first - t.first;
    int yDiff = h.second - t.second;

    if (abs(xDiff) > 1) {
        t.first += xDiff > 0 ? 1 : -1;
        if (yDiff != 0)
            t.second += yDiff > 0 ? 1 : -1;
    }
    else if (abs(yDiff) > 1) {
        t.second += yDiff > 0 ? 1 : -1;
        if (xDiff != 0)
            t.first += xDiff > 0 ? 1 : -1;
    }
}

void move_long(array<pair<int, int>, 10>& rope, const char dir) {
    auto& h = rope.at(0);
    switch (dir) {
        case 'R': ++h.first; break;
        case 'L': --h.first; break;
        case 'U': ++h.second; break;
        case 'D': --h.second; break;
    }

    for (int i{1}; i<10; ++i) {
        auto& prev = rope.at(i-1);
        auto& curr = rope.at(i);

        int xDiff = prev.first - curr.first;
        int yDiff = prev.second - curr.second;

        if (abs(xDiff) > 1) {
            curr.first += xDiff > 0 ? 1 : -1;
            if (yDiff != 0)
                curr.second += yDiff > 0 ? 1 : -1;
        }
        else if (abs(yDiff) > 1) {
            curr.second += yDiff > 0 ? 1 : -1;
            if (xDiff != 0)
                curr.first += xDiff > 0 ? 1 : -1;
        }
    }
}

void star_1(std::string file_name) {
    pair<int, int> head{0,0};
    pair<int, int> tail{0,0};
    set<pair<int, int>> visited;
    
    util::for_each_line(file_name, [&head, &tail, &visited] (const string& line) {
        char direction = line.at(0);
        int repetitions = stoi(line.substr(line.find(' ')+1));
        for (int i{0}; i<repetitions; ++i) {
            move(head, tail, direction);
            visited.insert(tail);
        }
    });

    std::cout << "Solution for Star 1:\n";
    std::cout << visited.size() << '\n';
}

void star_2(std::string file_name) {
    array<pair<int, int>, 10> rope{};
    set<pair<int, int>> visited;

    util::for_each_line(file_name, [&rope, &visited] (const string& line) {
        char direction = line.at(0);
        int repetitions = stoi(line.substr(line.find(' ')+1));
        for (int i{0}; i<repetitions; ++i) {
            move_long(rope, direction);
            visited.insert(rope.at(9));
        }
    });

    std::cout << "Solution for Star 2:\n";
    std::cout << visited.size() << '\n';
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
