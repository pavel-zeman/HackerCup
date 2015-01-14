// Brute force - try all possible subsets (there are at maximum 2^20 of them)
// https://www.facebook.com/hackercup/problems.php?pid=1036037553088752&round=742632349177460
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 40

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
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int target[3];
        FOR(i, 3) target[i] = getInt();
        int n = getInt();
        int source[MAX_N][3];
        FOR(i, n) FOR(j, 3) source[i][j] = getInt();

        bool found = false;
        FORE(subset, 1, 1 << n) {
            int total[3];
            FOR(i, 3) total[i] = 0;
            int temp = subset;
            FOR(i, n) {
                if ((temp & 1) == 1)
                    FOR(j, 3) total[j] += source[i][j];
                temp >>= 1;
            }
            bool ok = true;
            FOR(j, 3) if (total[j] != target[j]) ok = false;
            if (ok) {
                found = true;
                break;
            }
        }
        printf("Case #%d: %s\n", cc + 1, found ? "yes" : "no");
    }
}
