#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXPRIME 1000002

#define MOD 1000000007

int n, a, b, c, d;

bool prime[MAXPRIME];


long long int pow(int a, int b) {
    long long int res = 1;
    long long int p = a;
    while (b > 0) {
        if ((b & 1) == 1) res = (res * p) % MOD;
        p = (p * p) % MOD;
        b >>= 1;
    }
    return res;
}

// pocet cisel v intervalu a, b, které jsou vsechna delitelna d, ale nejsou delitelna nicim mensim
long long int ns(int a, int b, int d) {
    if (b < d) return 0;


    int s1 = a / d;
    if (s1 * d != a) s1++;
    int s2 = b / d;

    long long int total = pow(s2 - s1 + 1, n);
    FOR(i, d) {
        if (prime[i]) {
            total -= ns(s1, s2, i);
            if (total < 0) total += MOD;
        }
    }
    //printf("Partial %d %d %d %d %d, res: %lld\n", a, b, d, s1, s2, total);
    return total;
}

long long int solve(int a, int b) {
    long long int total = pow(b - a + 1, n);
    FOR(i, MAXPRIME) {
        if (prime[i]) {
            total -= ns(a, b, i);
            if (total < 0) total += MOD;
        }
        if (i > b) break;
    }
    //printf("Solving: %d %d, res: %lld\n", a, b, total);
    return total;
}


int main(void) {

    FOR(i, MAXPRIME) prime[i] = true;
    prime[0] = prime[1] = false;
    for(int i=2;i<MAXPRIME;i++) {
        if (prime[i]) {
            int j = i + i;
            while (j < MAXPRIME) {
                prime[j] = false;
                j += i;
            }
        }
    }

    int cases;
    scanf("%d", &cases);

    while (cases--) {
        scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);

        if (a >= d || n == 1) printf("%d\n", 0); else {
            long long int res = solve(a, d);
            if (c > b) {
                res -= solve(a, c - 1);
                res -= solve(b + 1, d);
                res += solve(b + 1, c - 1);
            } else {
                res -= solve(a, c - 1);
                res -= solve(b + 1, d);
            }
            res %= MOD;
            if (res < 0) res += MOD;
            printf("%lld\n", res);
        }
    }
}
