#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1051962371

int g, c;

long long int comb[200][200];


long long int mul(int f, int t) {
    long long int res = 1;
    while (f <= t) {
        res *= f;
        res %= MOD;
        f++;
    }
    return res;
}

int main(void) {
    int cases;
    scanf("%d", &cases);

    comb[0][0] = 1;
    FORE(i, 1, 101) {
        comb[i][0] = 1;
        FORE(j, 1, i) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        comb[i][i] = 1;
    }

    for(int cc=1;cc<=cases;cc++) {
        scanf("%d %d", &g, &c);
        long long int total = mul(1, g - c);

        FORE(i, c + 1, g + 1) {
            long long int x = mul(g - c - (i - c) + 1, g - c);
            //printf("#1: %lld ", x);
            FORE(j, 1, i - c + 1) {
                long long int y = comb[i - c][j] * mul(g - c - j + 1 - (i - c - j), g - c - j) % MOD;
                //printf("#2 %d %lld ", j, y);
                if ((j & 1) == 1) y = -y + MOD;
                x += y;
                x %= MOD;
            }
            x *= comb[i - 1][i - c];
            x %= MOD;
            x *= mul(1, g - i);
            x %= MOD;
            //printf("Add %lld ", x);
            total += x;
            total %= MOD;
        }
        printf("%lld\n", total);
    }
}
