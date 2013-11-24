#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int main(void) {
    int n, r, c, k, m;
    char pegs[100][200];
    double prob[100][200];
    scanf("%d", &n);
    for(int cc=1;cc<=n;cc++) {
        scanf("%d%d%d%d", &r, &c, &k, &m);
        c = c * 2 - 1;
        FOR(i, r) FOR(j, c) pegs[i][j] = (i + j + 1) & 1, prob[i][j] = 0;
        FOR(i, m) {
            int r1, c1;
            scanf("%d%d", &r1, &c1);
            pegs[r1][c1 * 2 + (r1 & 1)] = 0;
        }

        prob[r - 1][k * 2 + 1] = 1;
        for(int i=r-2;i>=0;i--) {
            FORE(j, (i&0), c - (i&0))
                if (!pegs[i][j]) {
                    if (!pegs[i + 1][j])
                        prob[i][j] = prob[i+1][j];
                    else {
                        if ((i&1) == 0 && j == 1) prob[i][j] = prob[i+1][j+1];
                        else if ((i&1) == 0 && j == c - 2) prob[i][j] = prob[i+1][j-1];
                        else prob[i][j] = 0.5 * (prob[i+1][j-1] + prob[i+1][j+1]);
                    }
                }
        }

        /*FOR(i, r) {
            FOR(j, c)
              printf("%.6f ", prob[i][j]);
            printf("\n");
        }
        FOR(i, r) {
            FOR(j, c)
              printf("%c", pegs[i][j] ? 'X' : '.');
            printf("\n");
        }
        printf("\n\n");*/

        double max = 0;
        int maxc = -1;
        FOR(i, c) if (prob[0][i] > max) max = prob[0][i], maxc = i;
        printf("%d %.6f\n", maxc/2, max);
    }
}
