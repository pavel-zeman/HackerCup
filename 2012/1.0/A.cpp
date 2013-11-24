#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int r, c;

char maze[100][100];
int distance[100][100];


struct pos {
    int r, c;
} toProcess[100000];

int toProcessCount, toProcessPos;
char colorUsed[100];

void check(int r1, int c1, int d) {
    if (r1 < r && r1 >= 0 && c1 < c && c1 >= 0 && maze[r1][c1] != 'W' && distance[r1][c1] > d + 1) {
        distance[r1][c1] = d + 1;
        toProcess[toProcessCount].r = r1;
        toProcess[toProcessCount].c = c1;
        toProcessCount++;

    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        scanf("%d%d", &r, &c);
        FOR(i, r) {
            char row[1000];
            scanf("%s", row);
            memcpy(maze[i], row, c);
            FOR (j, c) distance[i][j] = 10000000;
        }
        FOR(i, 10) colorUsed[i] = 0;
        int startC = -1;
        FOR (i, c) if (maze[0][i] == 'S') startC = i;
        if (startC == -1) {
            printf("Error");
            return 1;
        }

        toProcess[0].r = 0;
        toProcess[0].c = startC;
        toProcessPos = 0;
        toProcessCount = 1;
        distance[0][startC] = 0;

        while (toProcessPos < toProcessCount) {
            int r1 = toProcess[toProcessPos].r;
            int c1 = toProcess[toProcessPos].c;

            // all dirs
            check(r1 + 1, c1, distance[r1][c1]);
            check(r1 - 1, c1, distance[r1][c1]);
            check(r1, c1 + 1, distance[r1][c1]);
            check(r1, c1 - 1, distance[r1][c1]);

            if (maze[r1][c1] >= '1' && maze[r1][c1] <= '9' && !colorUsed[maze[r1][c1] - '0']) {
                int color = maze[r1][c1];
                int d = distance[r1][c1];
                FOR (k, r) FOR (l, c)
                    if (maze[k][l] == color && distance[k][l] > d + 1) {
                        distance[k][l] = d + 1;
                        toProcess[toProcessCount].r = k;
                        toProcess[toProcessCount].c = l;
                        toProcessCount++;
                    }
                colorUsed[color - '0'] = 1;
            }
            toProcessPos++;
        }

        int endC = -1;
        FOR (i, c) if (maze[r - 1][i] == 'E') endC = i;
        if (endC == -1) {
            printf("Error");
            return 1;
        }

        printf("%d\n", distance[r - 1][endC]);
    }
}
