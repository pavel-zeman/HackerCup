// Brute force solution - generate all primes up to sqrt(max(B)) and the for each i between A and B check divisibility by all primes.
// https://www.facebook.com/hackercup/problems.php?pid=582396081891255&round=344496159068801
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_PRIME 10000
#define MAX_PRIMES 5000
#define MAX_B 10000010

bool prime[MAX_PRIME];
int primeCount;
int primes[MAX_PRIMES];
int primacity[MAX_B];

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


int getPrimacity(int x) {
    int i = 0;
    int total = 0;
    while (primes[i] * primes[i] <= x) {
        if (x % primes[i] == 0) {
            total++;
            while (x % primes[i] == 0) x = x / primes[i];
        }
        i++;
    }
    if (x > 1) total++;
    return total;
}

int main(void) {
    FOR(i, MAX_PRIME) prime[i] = true;
    int primeCount = 0;
    FORE(i, 2, MAX_PRIME) {
        if (prime[i]) {
            primes[primeCount++] = i;
            for(int j=i+i;j<MAX_PRIME;j += i) prime[j] = false;
        }
    }
    FORE(i, 2, MAX_B) primacity[i] = getPrimacity(i);

    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int a = getInt();
        int b = getInt();
        int k = getInt();

        int total = 0;
        FORE(i, a, b + 1) if (primacity[i] == k) total++;
        printf("Case #%d: %d\n", cc + 1, total);
    }
}
