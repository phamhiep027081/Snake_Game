#ifndef A_STAR_H_
#define A_STAR_H_

#include <vector>
#include "SDL.h"
#include <limits>
#include <memory>

using std::vector;

enum class State{
    kEmpty = 0,
    kClose,
    kOpen,
    kPath
};
class Node{
    public:
        Node *parent = nullptr;
        int x = 0;
        int y = 0;
        int g = 0;
        int h = std::numeric_limits<int>::max();
        State state = State::kEmpty;
};
class AStar{
    public:
        AStar(const std::size_t grid_width, const std::size_t grid_height);
        vector<SDL_Point> Search(const SDL_Point &startPoint, const SDL_Point &endPoint);

    private:
        vector<vector<Node>> nodes;
        vector<Node> openList = {};
        int delta[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        int Heuristic(const int startPoint_X, const int startPoint_Y, const int endPoint_X, const int endPoint_Y);
        bool isInRange(const int x, const int y);
};


#endif /*A_STAR_H_*/