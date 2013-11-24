#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <gmpxx.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

mpz_class n, k;



int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        char sn[100], sk[100];
        scanf("%s %s", sn, sk);
        n = sn;
        k = sk;
        k++;
        mpz_class kk = 0;
        mpz_class d = 1;

        while (d <= (k - 1) * n) {
            kk++;
            mpz_class res = d * k;
            if (res % (k - 1) == 0) res /= k - 1; else res = res / (k - 1) + 1;
            d = res;

            //if (kk % 1000000 == 0) printf("%lld\n", d);
        }

        mpz_class out = k * n + 1 - d;
        printf("%s\n", out.get_str().c_str());
    }
}
