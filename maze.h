#include <bits/stdc++.h>

using namespace std;

class Maze {

private:

    static const int _S = 20, U = 1, R = 2, D = 4, L = 8;
    int dx[_S], dy[_S], opposite[_S], directions[4];

    int width, height;
    string algo;
    vector<vector<int>> maze;

    bool out_of_bounds(int nx, int ny);
    int cellIndex(int x, int y);
    void recursive_backtrack_dfs(int x, int y);

public:

    Maze(int _height, int _width);
    void reset();
    void draw_ascii();

    void recursive_backtracker();

    void kruskal();
};