#include <iostream>
#include <string>
#include <queue>
#include <regex>
#include <vector>

#include "../util.h"

using namespace std;

struct Monkey {
    Monkey(queue<unsigned long> items, char operation, string operationNum, int testNum, int ifTrue, int ifFalse) {
        this->items = items;
        this->operation = operation;
        this->operationNum = operationNum;
        this->testNum = testNum;
        this->ifTrue = ifTrue;
        this->ifFalse = ifFalse;
    }

    queue<unsigned long> items;
    char operation;
    string operationNum;
    int testNum;
    int ifTrue;
    int ifFalse;
    unsigned inspections{0};
};

vector<Monkey> parse_monkeys(const std::string& file_name) {
    vector<Monkey> monkeys{};
    util::for_n_lines(file_name, 7, [&monkeys] (const vector<string>& lines) {
        regex exp_num{"[0-9]+"};
        regex exp_operation{"[+*]"};
        smatch m;

        auto items_begin = sregex_iterator{lines[1].begin(), lines[1].end(), exp_num};
        auto items_end = sregex_iterator{};
        queue<unsigned long> items{};
        for (sregex_iterator i = items_begin; i!= items_end; ++i)
            items.push(stoul((*i).str()));

        string operationNum{};
        if (regex_search(lines[2], m, exp_num))
            operationNum = m[0];
        else
            operationNum = "old";
            

        regex_search(lines[2], m, exp_operation);
        char operation{m[0].str().at(0)};

        regex_search(lines[3], m, exp_num);
        int testNum{stoi(m[0])};

        regex_search(lines[4], m, exp_num);
        int ifTrue{stoi(m[0])};

        regex_search(lines[5], m, exp_num);
        int ifFalse{stoi(m[0])};

        monkeys.push_back(Monkey{items, operation, operationNum, testNum, ifTrue, ifFalse});
    });

    return monkeys;
}

void star_1(std::string file_name) {
    vector<Monkey> monkeys = parse_monkeys(file_name);

    for (unsigned i{0}; i<20; ++i) {
        for (Monkey& monkey : monkeys) {
            while (!monkey.items.empty()) {
                unsigned long item{monkey.items.front()};
                monkey.items.pop();

                int operationNum = monkey.operationNum == "old" ? item : stoi(monkey.operationNum);
                switch(monkey.operation) {
                    case '*': item *= operationNum; break;
                    case '+': item += operationNum; break;
                }

                item /= 3;

                if (item % monkey.testNum == 0)
                    monkeys.at(monkey.ifTrue).items.push(item);
                else
                    monkeys.at(monkey.ifFalse).items.push(item);

                ++monkey.inspections;
            }
        }
    }

    pair<unsigned long, unsigned long> topTwo{0, 0};
    for (Monkey& monkey : monkeys)
        if (monkey.inspections > topTwo.first) {
            topTwo.second = topTwo.first;
            topTwo.first = monkey.inspections;
        } else if (monkey.inspections > topTwo.second)
            topTwo.second = monkey.inspections;

    std::cout << "Solution for Star 1:\n";
    std::cout << topTwo.first * topTwo.second << '\n';
}

void star_2(std::string file_name) {
    vector<Monkey> monkeys = parse_monkeys(file_name);

    unsigned long commonMul{1};
    for (Monkey& monkey : monkeys)
        commonMul *= monkey.testNum;

    for (unsigned i{0}; i<10000; ++i) {
        for (Monkey& monkey : monkeys) {
            while (!monkey.items.empty()) {
                unsigned long item{monkey.items.front()};
                monkey.items.pop();

                unsigned long operationNum = monkey.operationNum == "old" ? item : stoi(monkey.operationNum);
                switch(monkey.operation) {
                    case '*': item *= operationNum; break;
                    case '+': item += operationNum; break;
                }

                item %= commonMul;

                if (item % monkey.testNum == 0)
                    monkeys.at(monkey.ifTrue).items.push(item);
                else
                    monkeys.at(monkey.ifFalse).items.push(item);

                ++monkey.inspections;
            }
        }
    }

    pair<unsigned long, unsigned long> topTwo{0, 0};
    for (Monkey& monkey : monkeys)
        if (monkey.inspections > topTwo.first) {
            topTwo.second = topTwo.first;
            topTwo.first = monkey.inspections;
        } else if (monkey.inspections > topTwo.second)
            topTwo.second = monkey.inspections;

    std::cout << "Solution for Star 2:\n";
    std::cout << topTwo.first * topTwo.second << '\n';
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
