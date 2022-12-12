#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>
#include <map>
#include <set>

#include "../util.h"

using namespace std;

struct Node {
    pair<int, int> pos;
    unsigned distance;
    bool infinite;
    char height;
    char c;

    bool operator<(const Node& other) const {
        return infinite || distance > other.infinite;
    }
};

vector<reference_wrapper<Node>> get_neighbours(Node& node, vector<vector<Node>>& grid) {
    vector<pair<int, int>> neighbours{
        {node.pos.first+1, node.pos.second},
        {node.pos.first, node.pos.second-1},
        {node.pos.first-1, node.pos.second},
        {node.pos.first, node.pos.second+1}
    };


    vector<reference_wrapper<Node>> actualNeighbours{};
    for (const auto& neighbour : neighbours) {
        if (neighbour.first < 0 || neighbour.second < 0 || neighbour.first >= (int)grid[0].size() || neighbour.second >= (int)grid.size())
            continue;

        Node& n = grid[neighbour.second][neighbour.first];

        if (node.height - n.height < 2)
            actualNeighbours.push_back(n);
    }

    return actualNeighbours;
}

struct Comp_Nodes {
    bool operator()(const reference_wrapper<Node>& l, const reference_wrapper<Node>& r) const {
        return l.get() < r.get();
    }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "No input file given\n";
        return 1;
    }
    auto lines_opt = util::get_all_lines(argv[1]);

    if (!lines_opt)
        return -1;

    auto lines = lines_opt.value();

    vector<vector<Node>> grid {};
    grid.reserve(lines.size());

    priority_queue<reference_wrapper<Node>, vector<reference_wrapper<Node>>, Comp_Nodes> pq{};

    for (unsigned i{0}; i<lines.size(); ++i) {
        grid.push_back({});
        grid.back().reserve(lines[i].size());

        for (unsigned j{0}; j<lines[i].size(); ++j) {
            char height = lines[i][j];

            Node node{{j, i}, 0, true, height, height};

            if (height == 'S') {
                node.height = 'a';
            } else if (height == 'E') {
                node.height = 'z';
                node.infinite = false;
            }

            grid.back().push_back(node);
            pq.push(grid.back().back());
        }
    }

    // Dijkstra from End
    while (!pq.empty()) {
        Node& cur = pq.top();
        pq.pop();
        if (cur.infinite)
            continue;

        auto neighbours = get_neighbours(cur, grid);

        for (auto& neighbour : neighbours) {
            Node& n = neighbour.get();
            if (cur.distance+1 < n.distance || n.infinite) {
                n.distance = cur.distance+1;
                n.infinite = false;
                pq.push(n);
            }
        }
    }

    int result{0};
    int min{-1};
    for (const auto& x : grid)
        for (const auto& n: x) {
            if (n.c == 'S')
                result = n.distance;

            if (n.height == 'a' && (min < 0 || (!n.infinite && n.distance < min)))
                min = n.distance;
        }


    std::cout << "Solution for Star 1:\n";
    std::cout << result << '\n';
    std::cout << "Solution for Star 2:\n";
    std::cout << min << '\n';
    return 0;
}
