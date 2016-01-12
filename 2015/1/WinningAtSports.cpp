// Dynamic programming - for each score, there can be at most 2 predecessors (either I win or I lose), so sum the number of ways to get there.
// https://www.facebook.com/hackercup/problems.php?pid=688426044611322&round=344496159068801
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_SCORE 2010
#define MOD 1000000007


int result[MAX_SCORE][MAX_SCORE];
int maxs2;

int getInt() {
    int d;
    scanf("%d", &d);
    return d;
}

int getStressFree(int s1, int s2) {
    if (result[s1][s2] == -1) {
        int total = 0;
        if (s1 > 0 && (s1 - 1 > s2 || s2 == 0)) total += getStressFree(s1 - 1, s2);
        if (s2 > 0) total += getStressFree(s1, s2 - 1);
        result[s1][s2] = total % MOD;
    }
    return result[s1][s2];
}


int getStressFul(int s1, int s2) {
    if (result[s1][s2] == -1) {
        int total = 0;
        if (s1 > 0 && (s1 <= s2 || s2 == maxs2)) total += getStressFul(s1 - 1, s2);
        if (s2 > 0 && s2 > s1) total += getStressFul(s1, s2 - 1);
        result[s1][s2] = total % MOD;
    }
    return result[s1][s2];
}


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int s1, s2;
        scanf("%d-%d", &s1, &s2);
        maxs2 = s2;

        FOR(i, MAX_SCORE) FOR(j, MAX_SCORE) result[i][j] = -1;
        result[0][0] = 1;
        int stressFree = getStressFree(s1, s2);

        FOR(i, MAX_SCORE) FOR(j, MAX_SCORE) result[i][j] = -1;
        result[0][0] = 1;
        int stressFul = getStressFul(s1, s2);

        printf("Case #%d: %d %d\n", cc + 1, stressFree, stressFul);
    }
}
