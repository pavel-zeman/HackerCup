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
    int cases;
    unsigned int x;
    int max = 46340;

    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &x);
        unsigned int a = 0, b = max, total = 0;
        while (a <= b) {
            while (a * a + b * b > x && a < b) b--;
            if (a * a + b * b == x) total++;
            a++;
        }
        printf("%d\n", total);
    }
}
