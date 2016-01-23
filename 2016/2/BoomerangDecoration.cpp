// "Running sums" from both ends
// https://www.facebook.com/hackercup/problem/424794494381569/
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000007


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
}


int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 100010

char a[MAX_N];
char b[MAX_N];

int startChanges[MAX_N];
int endChanges[MAX_N];
int minStart[MAX_N];
int minEnd[MAX_N];

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int n = getInt();
        getString(a);
        getString(b);
        startChanges[0] = 1;
        FORE(i, 1, n) startChanges[i] = startChanges[i - 1] + (b[i] == b[i - 1] ? 0 : 1);
        endChanges[n - 1] = 1;
        for(int i=n-2;i>=0;i--) endChanges[i] = endChanges[i + 1] + (b[i] == b[i + 1] ? 0 : 1);

        minStart[0] = a[0] == b[0] ? 0 : 1;
        FORE(i, 1, n) minStart[i] = a[i] == b[i] ? minStart[i - 1] : startChanges[i];

        minEnd[n - 1] = a[n - 1] == b[n - 1] ? 0 : 1;
        for(int i=n-2;i>=0;i--) minEnd[i] = a[i] == b[i] ? minEnd[i + 1] : endChanges[i];

        int res = min(minStart[n - 1], minEnd[0]);
        FOR(i, n - 1) res = min(res, max(minStart[i], minEnd[i + 1]));

        printf("Case #%d: %d\n", cc + 1, res);
    }
}
