#include "AStar.h"
#include <iostream>
#include <algorithm>

AStar::AStar(const std::size_t grid_width, const std::size_t grid_height){
    openList.clear();
    nodes.clear();

    nodes.resize(grid_height);

    for (int i = 0; i < grid_height; i++) {
        nodes[i].resize(grid_width);
        for (int j = 0; j < nodes[i].size(); j++) {
            nodes[i][j].state = State::kEmpty;
        }
    }
}

int AStar::Heuristic(const int startPoint_X, const int startPoint_Y, const int endPoint_X, const int endPoint_Y) {
    return abs(endPoint_X - startPoint_X) + abs(endPoint_Y - startPoint_Y);
}

bool AStar::isInRange(const int x, const int y) {
    const bool on_board_x = (x >= 0 && x < nodes.size());
    const bool on_board_y = (y >= 0 && y < nodes[0].size());

    if (on_board_x && on_board_y) {
        return true;
    } else {
        return false;
    }
}

vector<SDL_Point> AStar::Search(const SDL_Point &startPoint, const SDL_Point &endPoint) {
    openList.clear();
    vector<SDL_Point> SDL_Points{};
    SDL_Point SDL_point;
    int search_count = 0;

    Node node;
    node.parent = nullptr;
    node.x = startPoint.x;
    node.y = startPoint.y;
    node.g = 0;
    node.h = Heuristic(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
    node.state = State::kOpen;
    nodes[node.x][node.y].x = node.x;
    nodes[node.x][node.y].y = node.y;
    openList.push_back(node);

    while (not openList.empty()) {
        search_count++;
        std::sort(openList.begin(), openList.end(), [](const Node &a, const Node &b){ return (a.g + a.h) > (b.g + b.h); });
        Node *current = &nodes[openList.back().x][openList.back().y];
        current->state = State::kClose;
        openList.pop_back();

        for (int i = 0;  i < 4; i++) {
            const int x_next = current->x + delta[i][0];
            const int y_next = current->y + delta[i][1];

            if (not isInRange(x_next, y_next)) {
                continue;
            }

            Node *node_next = &nodes[x_next][y_next];
            node_next->x = x_next;
            node_next->y = y_next;

            if (x_next == endPoint.x && y_next == endPoint.y) {
                node_next->parent = current;
                node_next->state = State::kPath;
                node_next->g = current->g + 1;
                node_next->h = 0;

                while (nullptr != node_next) {
                    SDL_point.x = node_next->x;
                    SDL_point.y = node_next->y;
                    SDL_Points.push_back(SDL_point);
                    node_next->state = State::kPath;
                    node_next = node_next->parent;
                }

                std::reverse(SDL_Points.begin(), SDL_Points.end());
                std::cout << "A* search OK! search_count: "  << search_count << std::endl;
                SDL_Points.pop_back();

                return SDL_Points;
            }

            if (State::kClose == node_next->state) {
                continue;
            }

            bool should_add_to_openlist = false;

            if (State::kOpen != node_next->state) {
                should_add_to_openlist = true;
            } else if (current->g + 1 < node_next->g) {
                should_add_to_openlist = true;
            } else {
                continue;
            }

            if (should_add_to_openlist) {
                node_next->parent = current;
                node_next->state = State::kOpen;
                node_next->g = current->g + 1;
                node_next->h = Heuristic(x_next, y_next, endPoint.x, endPoint.y);
                openList.push_back(*node_next);
            }
        }
    }

    std::cout << "A* search FAILED! search_count: "  << search_count << std::endl;

    return SDL_Points;
}