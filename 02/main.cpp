#include <iostream>
#include <string>
#include "../util.h"

int score_of_round(char p1, char p2) {
    int score{0};
    score += p2 - 'W';

    int pickp1 = p1 - 'A';
    int pickp2 = p2 - 'X';

    if (pickp1 == pickp2)
        score += 3;
    else if (pickp2 == (pickp1 + 1) % 3)
        score += 6;
    
    return score;
}

void star_2(std::string file_name) {
    int score{0};
    util::for_each_line(file_name, [&score] (const std::string& line) {
        if (!line.empty()) {
            char opponent = line.at(0);
            char pick;
            switch (line.at(2)) {
                case 'X': pick = 'X' + (opponent == 'A' ? 2 : (opponent - 'A' - 1)); break;
                case 'Y': pick = 'X' + (opponent - 'A'); break;
                case 'Z': pick = 'X' + (((opponent - 'A') + 1) % 3); break;

            }
            score += score_of_round(opponent, pick);
        }
    });
    std::cout << "Solution star 2:\n" << score << '\n';
}

void star_1(std::string file_name) {
    int score{0};
    util::for_each_line(file_name, [&score] (const std::string& line) {
        if (!line.empty())
            score += score_of_round(line.at(0), line.at(2));
    });
    std::cout << "Solution star 1:\n" << score << '\n';
}

int main() {
    star_1("input.txt");
    star_2("input.txt");
    return 0;
}
