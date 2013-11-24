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


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        int g, w;
        char mt[100];
        int ccc = 1000000;
        mpz_class m;
        scanf("%d %d %s", &g, &w, mt);
        m = mt;
        mpz_class cg = m / 2 / g - ccc / 2;
        mpz_class maxCG = 0;
        mpz_class maxD = 0;

        FOR (i, ccc) {
            mpz_class cw = (m - cg * g) / w;
            mpz_class d = cg * cw;
            if (cg >= 0 && cw >= 0 && d > maxD) {
                maxD = d;
                maxCG = cg;
            }
            cg++;
        }
        printf("%s\n", maxCG.get_str().c_str());
    }
}
