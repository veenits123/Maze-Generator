#include "maze.h"

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Maze m = Maze(20, 20);
    m.draw_ascii();
    m.kruskal();
    m.draw_ascii();
    m.reset();
    m.recursive_backtracker();
    m.draw_ascii();

    return 0;
}
