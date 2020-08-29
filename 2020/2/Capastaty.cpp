// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-2/problems/A
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

#define MAX_N 1000010
int s[MAX_N];
int x[MAX_N];
int y[MAX_N];
int n, k;

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        k = getInt();
        FOR(i, k) s[i] = getInt();
        int a = getInt();
        int b = getInt();
        int c = getInt();
        int d = getInt();
        FORE(i, k, n) s[i] = (a * (LLI)s[i - 2] + b * (LLI)s[i - 1] + c) %d;

        FOR(i, k) x[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) x[i] = (a * (LLI)x[i - 2] + b * (LLI)x[i - 1] + c) %d;

        FOR(i, k) y[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) y[i] = (a * (LLI)y[i - 2] + b * (LLI)y[i - 1] + c) %d;

        LLI totalS = 0;
        FOR(i, n) totalS += s[i];
        LLI minS = 0;
        FOR(i, n) minS += x[i];
        LLI maxS = minS;
        FOR(i, n) maxS += y[i];
        LLI result = -1;
        if (totalS >= minS && totalS <= maxS) {
            LLI totalBelow = 0;
            FOR(i, n) if (s[i] < x[i]) totalBelow += x[i] - s[i];
            LLI totalAbove = 0;
            FOR(i, n) if (s[i] > x[i] + y[i]) totalAbove += s[i] - x[i] - y[i];
            result = totalBelow > totalAbove ? totalBelow : totalAbove;
        }

        printf("Case #%d: %lld\n", cc + 1, result);
    }
}
