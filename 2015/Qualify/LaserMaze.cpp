// Breadth-first search
// https://www.facebook.com/hackercup/problems.php?pid=1523599254559737&round=742632349177460
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <queue>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 120

#define START 'S'
#define GOAL 'G'
#define WALL '#'
#define EMPTY '.'
#define TURRET1 '^'
#define TURRET2 '>'
#define TURRET3 'v'
#define TURRET4 '<'
#define MAX_TIME (MAX_N * MAX_N * 4)

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct Turret {
    int x, y;
    int orientation;

    Turret(int x, int y, int orientation) {
        this->x = x;
        this->y = y;
        this->orientation = orientation;
    }
};

struct WorkItem {
    int x, y;
    int time;

    WorkItem(int x, int y, int time) {
        this->x = x;
        this->y = y;
        this->time = time;
    }
};

char maze[MAX_N][MAX_N];
int n, m;
int minTime[MAX_N][MAX_N][4];
vector<Turret> turrets;
queue<WorkItem> todo;

int getInt() {
    int d;
    scanf("%d", &d);
    return d;
}

bool isEmpty(int x, int y) {
    return maze[y][x] == EMPTY || maze[y][x] == START || maze[y][x] == GOAL;
}

bool isSafe(int x, int y, int time) {
    if (time == 0) return true;
    FOR(i, (int)turrets.size()) {
        Turret turret = turrets[i];
        int orientation = (turret.orientation + time) & 3;
        int cx = turret.x + dx[orientation];
        int cy = turret.y + dy[orientation];
        while (cx >= 0 && cx < n && cy >= 0 && cy < m && isEmpty(cx, cy)) {
            if (cx == x && cy == y) return false;
            cx += dx[orientation];
            cy += dy[orientation];
        }
    }
    return true;
}

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        turrets.clear();
        while (!todo.empty()) todo.pop();

        m = getInt();
        n = getInt();
        FOR(i, m) scanf("%s", maze[i]);
        int sx = -1, sy = -1;
        int gx = -1, gy = -1;
        FOR(i, m) FOR(j, n) {
            switch (maze[i][j]) {
                case START: sy = i; sx = j; break;
                case GOAL: gy = i; gx = j; break;
                case TURRET1: turrets.push_back(Turret(j, i, 0)); break;
                case TURRET2: turrets.push_back(Turret(j, i, 1)); break;
                case TURRET3: turrets.push_back(Turret(j, i, 2)); break;
                case TURRET4: turrets.push_back(Turret(j, i, 3)); break;
            }
        }
        FOR(i, m) FOR(j, n) FOR(k, 4) minTime[i][j][k] = MAX_TIME;

        todo.push(WorkItem(sx, sy, 0));
        while (!todo.empty()) {
            WorkItem currentItem = todo.front();
            todo.pop();
            if (currentItem.time < minTime[currentItem.y][currentItem.x][currentItem.time & 3] &&
                isSafe(currentItem.x, currentItem.y, currentItem.time)) {
                minTime[currentItem.y][currentItem.x][currentItem.time & 3] = currentItem.time;
                FOR(i, 4) {
                    int cx = currentItem.x + dx[i];
                    int cy = currentItem.y + dy[i];
                    if (cx >= 0 && cx < n && cy >= 0 && cy < m && isEmpty(cx, cy))
                        todo.push(WorkItem(cx, cy, currentItem.time + 1));
                }
            }
        }

        int result = minTime[gy][gx][0];
        FOR(i, 4) if (minTime[gy][gx][i] < result) result = minTime[gy][gx][i];
        if (result == MAX_TIME) printf("Case #%d: impossible\n", cc + 1);
        else printf("Case #%d: %d\n", cc + 1, result);
    }
}
