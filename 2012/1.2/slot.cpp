#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 10000001
#define MOD1 1000
#define A 5402147
#define B 54321

int n;
int numbers[1000];
long long int last;

long long int next(long long int x) {
    return (x * A + B) % MOD;
}




int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d", &n);
        FOR(i, n) scanf("%d", &numbers[i]);

        if (n == 1) {
            printf("Not enough observations\n");
        } else {

            long long int x = numbers[0];
            long long int z = numbers[2];
            long long int y = numbers[1];
            bool wrong = false;
            bool notEnough = false;
            last = -1;
            while (x < MOD) {
                y = numbers[1];
                if (next(x) % MOD1 == y) {
                    while (y < MOD) {
                        /*long long int dif = ((y - x) * A) % MOD;
                        dif = (dif + y) % MOD;
                        if (dif < 0) dif += MOD;

                        if (z == (dif % MOD1) && ((x * A + B) % MOD) == y) {
                            z = dif;
                            goto end;
                        }*/
                        if (next(x) == y && (n == 2 || next(y) % MOD1 == z)) {
                            long long t = x;
                            FOR(i, n) {
                                if (t % MOD1 != numbers[i]) {
                                    wrong = true;
                                    goto end;
                                }
                                t = next(t);
                            }
                            if (last == -1) last = t; else {
                                if (last != t % MOD1) {
                                    notEnough = true;
                                    goto end;
                                }
                            }

                        }
                        y += MOD1;
                    }
                }
                x += MOD1;
            }
            end:

            if (wrong || last == -1)
                printf("Wrong machine\n");
            else if (notEnough)
                printf("Not enough observations\n");
            else {
                //printf("%d %d %d %d\n", (int)x, (int)y, (int)z, (int)((z * A + B) % MOD));
                FOR(i, 10) {
                    printf("%d", (int)(last%MOD1));
                    if (i < 9) printf(" ");
                    last = next(last);
                }
                printf("\n");
            }


        }
    }
}
