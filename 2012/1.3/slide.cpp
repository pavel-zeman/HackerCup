#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define M 50

int r,c;
int tiles[M][M];
int max;

void check() {
    FOR(rs, r) {
        int power = 0;
        int stop = tiles[rs][0];
        int lc = 0;

        FOR(cs, c) {
            power += tiles[rs][cs];
            stop -= tiles[rs][cs];
            while (power > stop && lc < c - 1) {
                stop += tiles[rs][++lc];
            }
            int d = lc - cs - (power >= stop ? 0 : 1);
            if (d > max) max = d;
        }
    }

}

void rotate() {
    int temp[M][M];
    FOR(i, r) FOR(j, c) temp[j][r - i - 1] = tiles[i][j];
    FOR(i, M) FOR(j, M) tiles[i][j] = temp[i][j];
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d%d", &r, &c);
        FOR(i, r) {
            char temp[100];
            scanf("%s", temp);
            FOR(j, c) tiles[i][j] = temp[j] - '0';
        }
        max = 0;
        FOR(i, 4) {
            check();
            rotate();
            int z = r;
            r = c;
            c = z;
        }

        printf("%d\n", max);
    }
}
