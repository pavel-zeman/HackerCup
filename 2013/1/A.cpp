#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define M 10000001
#define P 20

int minLength[M];
long long int pascal1[P];
long long int pascal2[P];

int main(void) {
    FOR(i, M) minLength[i] = -1;
    minLength[1] = 1;
    pascal1[0] = 1;
    pascal1[1] = 1;
    FORE(i, 2, M) {
        pascal2[0] = 1;
        int j = 1;
        for(;j<i && j < P;j++) {
            pascal2[j] = pascal1[j - 1] + pascal1[j];
            if (pascal2[j] > M) break;
        }
        if (i < P) pascal2[i] = 1;
        for(int k=0;k<j + 1 && k < P;k++) {
            if (pascal2[k] < M && minLength[pascal2[k]] == -1) {
                minLength[pascal2[k]] = i;
            }
            pascal1[k] = pascal2[k];
        }
        if (i < P) pascal1[i] = 1;
    }

    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        int s;
        scanf("%d", &s);
        int i = 1;
        int min = M * 100;
        while (i * i <= s) {
            if (s % i == 0) {
                int j = s / i;
                if (minLength[i] + minLength[j] < min) {
                    min = minLength[i] + minLength[j];
                    //printf("%d %d ", i, j);
                }
            }
            i++;
        }

        printf("Case #%d: %d\n", cc + 1, min);
    }
}
