// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/B
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
int n, m, k, s;
int p[MAX_N];
int q[MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}

LLI getTotal(int from, int a, int b) {
    int q1 = q[a];
    int q2 = q[b];
    LLI res = (b - a + 1) * (LLI)s;
    if (from <= q1) return res + q2 - from;
    else if (from >= q2) return res + from - q1;
    else {
        int c1 = q2 - from;
        int c2 = from - q1;
        return res + min(c1, c2) * 2 + max(c1, c2);
    }
}

bool isPossible(LLI t) {
    int nm = 0;
    FOR(i, n) {
        int fm = nm;
        while (nm < m && getTotal(p[i], fm, nm) <= t) nm++;
    }
    return nm == m;
}

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        m = getInt();
        k = getInt();
        s = getInt();
        FOR(i, k) p[i] = getInt();

        LLI a, b, c;
        int d;
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) p[i] = (a * p[i - 2] + b * p[i - 1] + c) % d + 1;
        sort(p, p + n);

        FOR(i, k) q[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, m) q[i] = (a * q[i - 2] + b * q[i - 1] + c) % d + 1;
        sort(q, q + m);

        LLI l = 0, r = 2 * 1000 * 1000 * 1000 + m * (LLI)s;
        while (l < r - 1) {
            LLI mid = (l + r) >> 1;
            if (isPossible(mid)) r = mid; else l = mid;
        }
        printf("Case #%d: %lld\n", cc + 1, r);
    }
}
