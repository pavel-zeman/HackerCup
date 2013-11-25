// No magic here - simply find top left corner, bottom right corner, count number of black squares and check if it is the same as top-left and bottom-right corner distance
// https://www.facebook.com/hackercup/problems.php?pid=318555664954399&round=598486203541358
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define BLACK '#'
#define MAX_N 30


char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        int n;
        scanf("%d", &n);
        int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
        int numBlack = 0;
        FOR(i, n) {
            char row[MAX_N];
            scanf("%s", row);
            if (x1 == -1) {
                FOR(j, n) if (row[j] == BLACK) {
                    x1 = j;
                    y1 = i;
                    break;
                }
            }
            for(int j=n-1;j>=0;j--) {
                if (row[j] == BLACK) {
                    x2 = j;
                    y2 = i;
                    break;
                }
            }
            FOR(j, n) if (row[j] == BLACK) numBlack++;
        }

        printf("Case #%d: %s\n", cc + 1, x2 - x1 == y2 - y1 && (x2 - x1 + 1) * (x2 - x1 + 1) == numBlack ? "YES" : "NO");
    }
}
