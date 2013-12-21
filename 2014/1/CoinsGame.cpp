// The goal is to have the same number of coins all the jars. If it is possible, then P = C, otherwise we add some penalty.
// https://www.facebook.com/hackercup/problems.php?pid=105395349584705&round=1437956993099239
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
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        int n, k, c;
        scanf("%d %d %d", &n, &k, &c);

        int perJar = c % n == 0 ? c / n : c / n + 1;
        int p = c;
        if (perJar * n > k) {
            p += n - k / perJar;
        }
        printf("Case #%d: %d\n", cc + 1, p);
    }
}
