#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX 250000

int n, a1, a2, a3, a4, a5;
int m, b1, b2, b3, b4, b5;

int counta[MAX], countb[MAX];
int p, l;

void generate(int c, int x1, int x2, int x3, int x4, int x5, int *counts) {
    FOR(i, p) counts[i] = 0;
    long long int first = x1;
    long long int next = x2;
    counts[x1]++;
    counts[x2]++;
    c -= 2;
    while (c-- > 0) {
        long long int gen = (first * x3 + next * x4 + x5) % p;
        counts[gen]++;
        first = next;
        next = gen;
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d%d", &p, &l);
        scanf("%d%d%d%d%d%d", &n, &a1, &a2, &a3, &a4, &a5);
        scanf("%d%d%d%d%d%d", &m, &b1, &b2, &b3, &b4, &b5);
        generate(n, a1, a2, a3, a4, a5, counta);
        generate(m, b1, b2, b3, b4, b5, countb);

        long long int total = 0;
        for(int i = 0;i<p;i++) {
            //if (i > 0 && i % 1000 == 0) printf("%d\n", i);
            if (counta[i] > 0) {
                int subtotal = 0;
                int current = 0;
                FOR(j, p) {
                    if (current < l)
                        subtotal += countb[j];
                    current += i;
                    if (current >= p) current -= p;
                    //current %= p;
                }
                total += ((long long int)subtotal) * counta[i];
            }
        }
        printf("%lld\n", total);
    }
}
