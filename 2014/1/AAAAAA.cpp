// Simple search in a rectangular grid (unfortunately there is a mistake and it does not work)
// https://www.facebook.com/hackercup/problems.php?pid=184326661771870&round=1437956993099239
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <queue>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 600
#define EMPTY '.'


using namespace std;

struct Point {
    int row, column;
    Point(int r, int c) {
        row = r;
        column = c;
    }
};

char grid[MAX_N][MAX_N];
bool reachable[MAX_N][MAX_N];
int maxQueue[MAX_N][MAX_N];
int maxTotal[MAX_N][MAX_N];

int n, m;
queue<Point> reachableQueue;

void checkReachable(int r, int c) {
    if (r < n && c < m && grid[r][c] == EMPTY && !reachable[r][c]) {
        reachable[r][c] = true;
        reachableQueue.push(Point(r, c));
    }
}

void addEnd(int r, int c) {
    if ((r == n - 1 || grid[r + 1][c] != EMPTY) && (c == m - 1 || grid[r][c + 1] != EMPTY)) {
        maxQueue[r][c] = 1;
        reachableQueue.push(Point(r, c));
    }
}

void addMaxQueue(int r, int c, int size) {
    if (r >= 0 && c >= 0 && grid[r][c] == EMPTY && maxQueue[r][c] < size + 1) {
        maxQueue[r][c] = size + 1;
        reachableQueue.push(Point(r, c));
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        scanf("%d %d", &n, &m);
        FOR(i, n) scanf("%s", grid[i]);

        // mark reachable
        FOR(i, n) FOR(j, m) reachable[i][j] = false, maxQueue[i][j] = 0;
        reachable[0][0] = true;

        reachableQueue.push(Point(0, 0));
        while (!reachableQueue.empty()) {
            Point p = reachableQueue.front();
            reachableQueue.pop();

            checkReachable(p.row + 1, p.column);
            checkReachable(p.row, p.column + 1);
        }

        FOR(i, n) FOR(j, m) addEnd(n - 1 - i, m - 1 - j);
        while (!reachableQueue.empty()) {
            Point p = reachableQueue.front();
            reachableQueue.pop();

            addMaxQueue(p.row - 1, p.column, maxQueue[p.row][p.column]);
            addMaxQueue(p.row , p.column - 1, maxQueue[p.row][p.column]);
        }
        int result = maxQueue[0][0];
        //printf("%d\n", maxQueue[0][0]);

        FOR(i, n) FOR(j, m) maxTotal[i][j] = 0;

        FORE(j, 1, m) {
            FOR(i, n) {
                if (reachable[i][j] && reachable[i][j - 1]) {
                    int mm;
                    if (i == 0 || grid[i - 1][j] != EMPTY) {
                        mm = 1;
                    } else {
                        mm = maxTotal[i - 1][j] + 1;
                    }
                    if (j + 1 < m && grid[i][j + 1] == EMPTY) mm = max(mm, maxQueue[i][j + 1] + 1);
                    maxTotal[i][j] = mm;
                    if (mm + i + j > result) {
                        result = mm + i + j;
                        //printf("C %d %d = %d\n", i, j, m);
                    }
                }
            }
        }
        /*FOR(i, n) {
            FOR(j, m) printf("%d ", maxTotal[i][j]);
            printf("\n");
        }*/

        FOR(i, n) FOR(j, m) maxTotal[i][j] = 0;

        FORE(i, 1, n) {
            FOR(j, m) {
                if (reachable[i][j] && reachable[i - 1][j]) {
                    int mm;
                    if (j == 0 || grid[i][j - 1] != EMPTY) {
                        mm = 1;
                    } else {
                        mm = maxTotal[i][j - 1] + 1;
                    }
                    if (i + 1 < n && grid[i + 1][j] == EMPTY) mm = max(mm, maxQueue[i + 1][j] + 1);
                    maxTotal[i][j] = mm;
                    if (mm + i + j > result) {
                        result = mm + i + j;
                        //printf("R %d %d = %d\n", i, j, m);
                    }
                }
            }
        }

        printf("Case #%d: %d\n", cc + 1, result);
    }
}