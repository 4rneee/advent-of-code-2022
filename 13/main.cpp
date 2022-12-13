#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "../util.h"

using namespace std;

struct Packet {
    vector<Packet> children{};
    int val{0};
    bool isList{true};
};

int index_of_closing_bracket (const string& s, int idx) {
    int openBrackets{1};
    while (openBrackets > 0)
        if (s.at(++idx) == '[')
            ++openBrackets;
        else if (s.at(idx) == ']')
            --openBrackets;

    return idx;
}

Packet parse_list(const string& s) {
    Packet packet{};
    int idx{0};
    while (idx < s.size()) {
        if (s.at(idx) == '[') {
            int closingIdx = index_of_closing_bracket(s, idx);
            packet.children.push_back(parse_list(s.substr(idx+1, closingIdx-(idx+1))));
            idx = closingIdx;
        } else if (s.at(idx) != ',') {
            int commaIdx = s.find(',', idx);
            packet.children.push_back(Packet{{}, stoi(s.substr(idx, commaIdx-idx)), false});
            idx = (commaIdx == string::npos ? idx : commaIdx);
        }
        ++idx;
    }
    return packet;
}

int in_correct_order(Packet& left, Packet& right) {
    if (!left.isList && !right.isList) {
        if (left.val < right.val)
            return 1;
        else if (left.val == right.val)
            return 0;
        else
            return -1;
        
    } else if (left.isList != right.isList) {
        if (!left.isList) {
            Packet list {};
            list.children.push_back(left);
            return in_correct_order(list, right);
        }
        Packet list {};
        list.children.push_back(right);
        return in_correct_order(left, list);
    }
    size_t leftIdx{0};
    size_t rightIdx{0};
    
    while (leftIdx < left.children.size() && rightIdx < right.children.size()) {
        Packet& childL = left.children.at(leftIdx);
        Packet& childR = right.children.at(rightIdx);

        int rec_res = in_correct_order(childL, childR);
        if (rec_res == 1)
            return 1;
        else if (rec_res == -1)
            return -1;

        ++leftIdx;
        ++rightIdx;
    }

    if (left.children.size() < right.children.size())
        return 1;
    else if (left.children.size() == right.children.size())
        return 0;
    return -1;
}

void star_1(std::string file_name) {
    int result{0};
    unsigned index{1};

    util::for_n_lines(file_name, 3, [&] (const vector<string>& lines) {
        Packet left = parse_list(lines[0].substr(1, lines[0].size()-2));
        Packet right = parse_list(lines[1].substr(1, lines[1].size()-2));

        if (in_correct_order(left, right) >= 0) {
            result += index;
        }
        ++index;
    });

    std::cout << "Solution for Star 1:\n";
    std::cout << result << '\n';
}

void star_2(std::string file_name) {
    vector<Packet> packets{};
    util::for_each_line(file_name, [&] (const string& line) {
        if (line.empty())
            return;

        packets.push_back(parse_list(line.substr(1, line.size()-2)));
    });

    packets.push_back({{{{}, 2, false}}, -1, true});
    packets.push_back({{{{}, 6, false}}, -1, true});

    std::sort(packets.begin(), packets.end(), [] (Packet& l, Packet& r) {
            return in_correct_order(l, r) >= 0;
    });

    int result{1};
    for (size_t i{0}; i<packets.size(); ++i) {
        const auto& p = packets.at(i);
        if (p.isList && p.val == -1)
            result *= (i+1);
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
