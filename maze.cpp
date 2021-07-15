#include "maze.h"

class DSU {
private:
    vector<int> parent, rank;
    int findSet(int u) {
        return u == parent[u] ? u : (parent[u] = findSet(parent[u]));
    }

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    bool sameSet(int u, int v) {
        return findSet(u) == findSet(v);
    }

    void unite(int u, int v) {
        int pu = findSet(u), pv = findSet(v);
        if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        }
        else {
            parent[pu] = pv;
            if (rank[pu] == rank[pv])
                rank[pv]++;
        }
    }
};

struct Wall {
    int x, y, dir;
    Wall() {};
    Wall(int _x, int _y, int _dir) : x(_x), y(_y), dir(_dir) {};
};

Maze::Maze(int _height, int _width) {
    srand(time(0));
    height = _height;
    width = _width;
    maze.assign(height, vector<int>(width));

    for (int i = 0; i < 4; i++)
        directions[i] = 1 << i;

    dx[U] = -1, dx[R] = 0, dx[D] = 1, dx[L] = 0;
    dy[U] = 0, dy[R] = 1, dy[D] = 0, dy[L] = -1;
    opposite[U] = D, opposite[R] = L,
                                   opposite[D] = U, opposite[L] = R;
}

void Maze::reset() {
    maze.assign(height, vector<int>(width, 0));
}

bool Maze::out_of_bounds(int nx, int ny) {
    return nx < 0 || ny < 0 || nx >= height || ny >= width;
}

void Maze::draw_ascii() {
    // cout << string(width * 2 + 1, '_') << endl;
    cout << " ";
    for (int j = 0; j < width; j++)
        cout << "_ ";
    cout << endl;
    for (int i = 0; i < height; i ++) {
        cout << "|";
        for (int j = 0; j < width; j ++) {
            cout << ((maze[i][j] & D) ? ' ' : '_');
            cout << ((maze[i][j] & R) ? ' ' : '|');
        }
        cout << endl;
    }
}

void Maze::recursive_backtrack_dfs(int x, int y) {
    random_shuffle(directions, directions + 4);
    for (int dir : directions) {
        int nx = dx[dir] + x;
        int ny = dy[dir] + y;

        if (out_of_bounds(nx, ny) || maze[nx][ny]) {
            continue;
        }

        maze[x][y] |= dir;
        maze[nx][ny] |= opposite[dir];
        recursive_backtrack_dfs(nx, ny);
    }
}

void Maze::recursive_backtracker() {
    recursive_backtrack_dfs(0, 0);
}

int Maze::cellIndex(int x, int y) {
    return x * width + y;
}

void Maze::kruskal() {
    DSU dsu(height * width);
    vector<Wall> walls;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j) walls.push_back(Wall(i, j, L));
            if (i) walls.push_back(Wall(i, j, U));
        }
    }

    random_shuffle(walls.begin(), walls.end());

    for (auto wall : walls) {
        int x = wall.x, y = wall.y, dir = wall.dir;
        int nx = dx[dir] + x, ny = dy[dir] + y;
        int cur = cellIndex(x, y), nxt = cellIndex(nx, ny);
        if (!dsu.sameSet(cur, nxt)) {
            dsu.unite(cur, nxt);
            maze[x][y] |= dir;
            maze[nx][ny] |= opposite[dir];
        }
    }
}
