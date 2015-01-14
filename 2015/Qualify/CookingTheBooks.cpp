// Brute force - try all the pairs
// https://www.facebook.com/hackercup/problems.php?pid=582062045257424&round=742632349177460
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

char value[20];

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

void swap(int a, int b) {
    char t = value[a];
    value[a] = value[b];
    value[b] = t;
}

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int n = getInt();
        int minValue = n;
        int maxValue = n;
        sprintf(value, "%d", n);
        int length = strlen(value);

        FOR(i, length) FORE(j, i + 1, length) {
            swap(i, j);
            if (value[0] != '0' && atoi(value) < minValue) minValue = atoi(value);
            swap(i, j);
        }

        FOR(i, length) FORE(j, i + 1, length) {
            swap(i, j);
            if (value[0] != '0' && atoi(value) > maxValue) maxValue = atoi(value);
            swap(i, j);
        }
        printf("Case #%d: %d %d\n", cc + 1, minValue, maxValue);
    }
}
