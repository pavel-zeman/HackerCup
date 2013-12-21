// A little modified conversion to base-n
// https://www.facebook.com/hackercup/problems.php?pid=637270059647812&round=1437956993099239
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)





int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        char l[100];
        char result[100];
        unsigned long long int n;
        scanf("%s %llu", l, &n);

        n--;
        int numChars = 1;
        unsigned int length = strlen(l);
        unsigned long long int lastPower = 0;
        unsigned long long int power = length;

        while (n >= power && lastPower <= power) {
            n -= power;
            lastPower = power;
            power *= length;
            numChars++;
        }

        FOR(i, numChars) {
            result[numChars - i - 1] = l[n % length];
            n /= length;
        }
        result[numChars] = 0;

        printf("Case #%d: %s\n", cc + 1, result);
    }
}
