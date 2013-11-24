#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    char temp[10000];
    gets(temp);
    int cases = atoi(temp);
    for (int cc = 0;cc<cases;cc++) {
        int freq[26];
        FOR(i, 26) freq[i] = 0;
        gets(temp);
        char *start = temp;
        while (*start) {
            if (*start >= 'A' && *start <= 'Z') freq[*start - 'A']++;
            start++;
        }

        int s = freq['H' - 'A'];
        s = min(s, freq['A' - 'A']);
        s = min(s, freq['C' - 'A'] / 2);
        s = min(s, freq['K' - 'A']);
        s = min(s, freq['E' - 'A']);
        s = min(s, freq['R' - 'A']);
        s = min(s, freq['U' - 'A']);
        s = min(s, freq['P' - 'A']);

        printf("Case #%d: %d\n", cc + 1, s);
    }
}
