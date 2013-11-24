#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


bool contains(char *s, int f, int t, char w) {
    FORE(i, f, t + 1)
        if (s[i] == w) return true;
    return false;
}


int fact(int i) {
    int res = 1;
    while (i > 1) res *= i--;
    return res;
}

int calculate(char *s, int l) {
    int res = 0;

    char f = s[0];
    bool allTheSame = true;
    FORE(i, 1, l)
        if (f != s[i])  {
            allTheSame = false;
            break;
        }

    if (allTheSame) return fact(l);

    FOR(i, l - 1) {
        char t[100];
        memcpy(t, s, i);
        FORE(j, i + 1, l) {
            FOR(k, 2) {
                if (contains(s, i, j, 'a' + k)) {
                    t[i] = 'a' + k;
                    memcpy(t + i + 1, s + j + 1, l - j - 1);
                    int l1 = i + 1 + l - j - 1;
                    t[l1] = 0;
                    res += calculate(t, l1);
                }
            }
        }
    }
    return res + 1;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        char test[100];
        scanf("%s", test);
        int res = calculate(test, strlen(test));
        printf("%d\n", res);
    }
}
