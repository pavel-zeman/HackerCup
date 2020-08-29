// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/A1
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
int n, k, w;

int l[MAX_N];
int h[MAX_N];


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        k = getInt();
        w = getInt();
        FOR(i, k) l[i] = getInt();
        LLI a, b, c;
        int d;
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) l[i] = (a * l[i - 2] + b * l[i - 1] + c) % d + 1;

        FOR(i, k) h[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) h[i] = (a * h[i - 2] + b * h[i - 1] + c) % d + 1;

        LLI res = 1;
        LLI p = 0;
        FOR(i, n) {
            if (i == 0 || l[i] > l[i - 1] + w) p += (w * 2 + h[i] * 2) % MOD;
            else {
                p = (p + 2 * (l[i] - l[i - 1])) % MOD;
                int j = i - 1;
                while (j >= 0 && h[i] > h[j] && l[j] + w >= l[i]) j--;
                if (j <  0 || l[j] + w < l[i]) {
                    // all smaller
                    int mx = 0;
                    FORE(xx, j + 1, i) if (h[xx] > mx) mx = h[xx];
                    p = (p + 2 * (h[i] - mx)) % MOD;
                }
            }

            p %= MOD;
            res = res * p % MOD;
        }


        printf("Case #%d: %lld\n", cc + 1, res);
    }
}
