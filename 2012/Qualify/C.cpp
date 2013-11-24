#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char used[10];
char strings[10][20];
char result[1000];
char prefix[1000];
int lengths[10];
int m;


void calculate(int level, int pos) {
    if (level < m) {
        FOR(i, m) if (!used[i]) {
            strcpy(prefix + pos, strings[i]);
            if (strcmp(prefix, result) < 0) {
                used[i] = 1;
                calculate(level + 1, pos + lengths[i]);
                used[i] = 0;
            }
        }
    } else {
        strcpy(result, prefix);
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    for(int c=1;c<=n;c++) {

        scanf("%d", &m);
        FOR(i, m) {
            scanf("%s", strings[i]);
            used[i] = 0;
            lengths[i] = strlen(strings[i]);
        }

        memset(result, 'z', sizeof(result));
        result[sizeof(result) - 1] = 0;
        prefix[0] = 0;
        calculate(0, 0);

        printf("%s\n", result);
    }
}
