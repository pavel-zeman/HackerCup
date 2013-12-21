// The gifts should be different and equal or greater than age - so try to start with the smallest numbers and try all the possibilities until reaching a prime number
// https://www.facebook.com/hackercup/problems.php?pid=1420024724897316&round=1437956993099239
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <algorithm>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

using namespace std;

#define MAX_N 30
#define MIN 1000000000
#define PRIMES 200

int n, k;
int a[MAX_N], b[MAX_N], c[MAX_N];

int result;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

bool isPrime[PRIMES];
long long int bits[PRIMES];

void check(int pos, int startValue, long long int ored, int currentValue) {
    if (pos == n) {
        if (currentValue < result) {
            result = currentValue;
            //FOR(i, n) printf("%d ", c[i]);
            //printf("\n");
        }
    } else {
        int start = b[pos];
        if (start < startValue) start = startValue;
        int numPrimes = 0;
        while (true) {
            c[pos] = start;
            if ((ored & bits[start]) == 0) check(pos + 1, start + 1, ored | bits[start], currentValue + start - b[pos]);
            if (isPrime[start]) numPrimes++;
            if (numPrimes >= 1) break;
            start++;
        }
    }
}

int main(void) {
    FOR(i, PRIMES) isPrime[i] = false;
    FOR(i, ((int)(sizeof(primes) / sizeof(primes[0])))) isPrime[primes[i]] = true;
    FOR(i, PRIMES) {
        long long int result = 0;
        long long int value = 1;
        FOR(j, ((int)(sizeof(primes) / sizeof(primes[0])))) {
            if (i % primes[j] == 0) result |= value;
            value <<= 1;
        }
        bits[i] = result;
    }

    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        scanf("%d %d", &n, &k);
        FOR(i, n) scanf("%d", &a[i]);

        int add = 0;
        sort(a, a + n);
        FOR(i, n) {
            if (a[i] % k != 0) {
                add += k - a[i] % k;
                a[i] += k - a[i] % k;
            }
        }
        FOR(i, n) b[i] = a[i] / k;
        FORE(i, 1, n) if (b[i] == 0) b[i] = 1;
        if (b[n - 1] > 1 && b[0] == 0) b[0] = 1;

        int index = 0;
        result = MIN;

        while (b[index] <= 1 && index < n) index++;
        if (index < n) {
            check(index, b[index], 0, 0);
        }
        if (result == MIN) result = 0;
        FOR(i, index) result += b[i] - a[i] / k;

        printf("Case #%d: %d\n", cc + 1, add + result * k);
    }
}
