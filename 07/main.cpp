#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "../util.h"

class Dir {
    public:
        Dir(std::string name, unsigned size) {
            this->name=name;
            this->size=size;
        };
        std::string name;
        unsigned size;
        std::vector<Dir> children{};
};

void calc_size(Dir& dir) {
    for (Dir& d: dir.children) {
        calc_size(d);
        dir.size += d.size;
    }
}

void final1(Dir& dir, int& result) {
    for (Dir& d : dir.children) {
        final1(d, result);
    }
    if (dir.size <= 100000) {
        result += dir.size;
    }
}

void final2(Dir& dir, int& result, int needed) {
    for (Dir& d : dir.children) {
        final2(d, result, needed);
    }
    if (dir.size >= needed && dir.size < result) {
        result = dir.size;
    }
}

Dir get_root(std::string file_name) {
    std::stack<std::reference_wrapper<Dir>> pwd{};

    Dir root = Dir("/", 0);
    util::for_each_line(file_name, [&root, &pwd] (const std::string& line) {
        if (line.at(0) == '$') {
            if (line.at(2) == 'c') {
                if (line.at(5) == '.') {
                    pwd.pop();
                } else {
                    std::string dir_name = line.substr(5);
                    if (pwd.empty()) {
                        pwd.push(root);
                    } else
                        for (Dir& d : pwd.top().get().children)
                            if (d.name == dir_name) {
                                pwd.push(d);
                                break;
                            }
                }
            }
        } else {
            if (line.at(0) == 'd') {
                Dir dir = Dir(line.substr(4), 0);
                pwd.top().get().children.push_back(dir);
            } else {
                unsigned size = std::stoul(line.substr(0, line.find(' ')));
                pwd.top().get().size += size;
            }
        }
    });

    calc_size(root);

    return root;
}

void star_1(std::string file_name) {
    Dir root = get_root(file_name);
    int result{0};

    final1(root, result);

    std::cout << "Solution for Star 1:\n";
    std::cout << result << '\n';
}

void star_2(std::string file_name) {
    Dir root = get_root(file_name);

    int free = 70000000 - root.size;
    int result{30000000};
    final2(root, result, 30000000-free);

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
