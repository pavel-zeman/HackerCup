#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define MOD 0xfaceb00cL

long long int poss[100000];
long long int mod = MOD;
char status[100000];

int m;
int len;

int get(int pos1, int pos2) {
    int total = 0;
    FORE(i, pos1, pos2 + 1) {
        total *= 10;
        total += status[i] - '0';
    }
    return total;
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        scanf("%d %s", &m, status);
        len = strlen(status);
        poss[len] = 1;
        for(int i=len-1;i>=0;i--) {
            poss[i] = 0;
            if (status[i] != '0') {
                for(int j=0;i+j<len;j++) {
                    int value = get(i, i + j);
                    if (value <= m) {
                        poss[i] += poss[i + j + 1];
                    } else
                        break;
                }
            }
            poss[i] = poss[i] % mod;
        }

        printf("Case #%d: %lld\n", cc + 1, poss[0]);
    }
}
