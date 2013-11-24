#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define T 10000100

int total[T];

int main(void) {
    total[0] = total[1] = 0;
    FOR(i, T) total[i] = 0;
    FORE(i, 2, T) {
        if (total[i] == 0) {
            int j = i;
            while (j < T) { total[j]++; j += i; }
        }
    }

    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        int a, b, n;
        scanf("%d%d%d", &a, &b, &n);
        int x  = 0;
        FORE(i, a, b + 1) {
            if (total[i] == n) x++;
        }
        printf("%d\n", x);
    }
}
