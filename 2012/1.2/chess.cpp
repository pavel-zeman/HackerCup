#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define N 16

int p;


char board[N][N];
bool danger[N][N];


int moveCount[4] = {8, 4, 8, 4};

int moves[10][10][2] = {
    {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}},
    {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}},
    {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}},
    {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};








void checkPiece(int t, int x, int y, bool unlimited) {
    int total = unlimited ? 32 : 1;
    FOR(j, moveCount[t]) {
        int x1 = x;
        int y1 = y;
        FOR(i, total) {
            x1 += moves[t][j][0];
            y1 += moves[t][j][1];
            if (x1 < 0 || x1 >= N || y1 < 0 || y1 >= N)
                break;
            if (board[x1][y1]) {
                danger[x1][y1] = true;
                break;
            }
        }
    }
}


void check(int x, int y) {
    char t = board[x][y];

    switch (t) {
        case 'K': // king
          checkPiece(0, x, y, false);
          break;
        case 'Q': // queen
          checkPiece(0, x, y, true);
          break;
        case 'R': // vez
          checkPiece(3, x, y, true);
          break;
        case 'B': // strelec
          checkPiece(1, x, y, true);
          break;
        case 'N': // kun
          checkPiece(2, x, y, false);
          break;
        case 'S': // nightrider
          checkPiece(2, x, y, true);
          break;
        case 'A': // archbishop
          checkPiece(1, x, y, true);
          checkPiece(2, x, y, false);
          break;
        case 'E':
          FOR(i, 16) FOR(j, 16)
            if (board[i][j] && (i != x || j != y))
              danger[i][j] = true;
          break;
    }
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &p);
        FOR(i, N) FOR(j, N) board[i][j] = 0, danger[i][j] = false;

        FOR(i, p) {
            char t[10];
            int r, f;
            scanf("%s%d%d", t, &r, &f);
            board[r - 1][f - 1] = t[0];
        }

        FOR(i, N) FOR(j, N)
            if (board[i][j])
                check(i, j);

        int threatened = 0;
        FOR(i, N) FOR(j, N)
            if (danger[i][j]) threatened++;

        printf("%d\n", threatened);
    }
}
