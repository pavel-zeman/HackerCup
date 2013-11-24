#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int r, c;

char input[32][32];
char current[32][32];

void sw(int i, int j) {
    current[i][j] = !current[i][j];
    if (i > 0) current[i - 1][j] = !current[i - 1][j];
    if (i < r - 1) current[i + 1][j] = !current[i + 1][j];
    if (j > 0) current[i][j - 1] = !current[i][j - 1];
    if (j < c - 1) current[i][j + 1] = !current[i][j + 1];
}

void dumpState() {
    FOR(i, r) {
        FOR(j, c) printf("%c", current[i][j] ? 'X' : '.');
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++) {
        char row[100];
        scanf("%d%d", &r, &c);
        FOR(i, r) {
            scanf("%s", row);
            FOR(j, c) input[i][j] = row[j] == 'X';
        }

        int firstRow = (1<<c);
        int min = 500;

        while (--firstRow >= 0) {
            int switches = 0;
            FOR(i, r) FOR(j, c) current[i][j] = input[i][j];
            int temp = firstRow;
            FOR(i, c) {
                if (temp & 1) sw(0, i), switches++;
                temp >>= 1;
            }

            FORE(i, 1, r) {
                FOR(j, c)
                    if (!current[i - 1][j]) sw(i, j), switches++;
                if (switches >= min) break;
            }

            if (switches < min) {
                bool ok = true;
                FOR(j, c)
                    if (!current[r - 1][j]) {
                        ok = false;
                        break;
                    }
                if (ok) min = switches;
            }
        }
        if (min == 500) min = -1;

        printf("%d\n", min);
    }
}
