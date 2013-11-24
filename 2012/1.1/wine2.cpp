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


long long int fact(int t) {
    long long int res = 1;
    while (t > 1) {
        res *= t--;
        res %= MOD;
    }
    return res;
}

long long int fixedPoint(int t) {
    long long res = 0;
    FOR(p, t + 1) {
        long long x = (comb[t][p] * fact(t - p)) % MOD;
        if ((p & 1) == 1) x = -x + MOD;
        res += x;
        res %= MOD;
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
        long long total = fact(g);
        FOR(i, c) {
            total -= (comb[g][i] * fixedPoint(g - i)) % MOD;
            if (total < 0) total += MOD;
        }
        printf("%lld\n", total);
    }
}
