#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

long long int n, k;



int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%lld%lld", &n, &k);
        k++;
        long long int kk = 0;
        long long int d = 1;

        while (d <= (k - 1) * n) {
            kk++;
            long long int res = d * k;
            if (res % (k - 1) == 0) res /= k - 1; else res = res / (k - 1) + 1;
            d = res;

            if (kk % 1000000 == 0) printf("%lld\n", d);
        }

        long long int out = k * n + 1 - d;
        printf("%lld\n", out);
    }
}
