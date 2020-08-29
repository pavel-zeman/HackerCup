// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/A2
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
int n, k;

int l[MAX_N];
int h[MAX_N];
int w[MAX_N];
map<int, int> fragments;


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        k = getInt();
        FOR(i, k) l[i] = getInt();
        LLI a, b, c;
        int d;
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) l[i] = (a * l[i - 2] + b * l[i - 1] + c) % d + 1;

        FOR(i, k) w[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) w[i] = (a * w[i - 2] + b * w[i - 1] + c) % d + 1;

        FOR(i, k) h[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        d = getInt();
        FORE(i, k, n) h[i] = (a * h[i - 2] + b * h[i - 1] + c) % d + 1;

        LLI p = (w[0] * 2 + h[0] * 2) % MOD;
        LLI res = p;
        fragments.clear();
        fragments.insert(make_pair(0, l[0]));
        fragments.insert(make_pair(l[0] + w[0], 2000000000));

        FORE(i, 1, n) {
            int f1 = l[i];
            int f2 = l[i] + w[i];
            auto it = fragments.lower_bound(f1);
            if (it != fragments.begin()) it--;
            while (f1 < f2) {
                if (it->second <= f1) it++;
                else if (it->first >= f2) break;
                else if (it->first >= f1 && it->second <= f2) {
                    // remove all
                    p = (p - 2 * h[i] + MOD) % MOD;
                    p = (p + 2 * (it->second - it->first)) % MOD;
                    f1 = it->second;
                    it = fragments.erase(it);
                } else if (it->first < f1 && it->second <= f2) {
                    p = (p + 2 * (it->second - f1)) % MOD;
                    int origits = it->second;
                    it->second = f1;
                    f1 = origits;
                    it++;
                } else if (it->first >= f1 && it->second > f2) {
                    p = (p + 2 * (f2 - it->first)) % MOD;
                    int origits = it->second;
                    fragments.erase(it);
                    fragments.insert(make_pair(f2, origits));
                    f1 = f2;
                } else {
                    p = (p + 2 * (f2 - f1) + 2 * h[i]) % MOD;
                    int origits = it->second;
                    it->second = f1;
                    fragments.insert(make_pair(f2, origits));
                    f1 = f2;
                }
            }

            p %= MOD;
            res = res * p % MOD;
        }


        printf("Case #%d: %lld\n", cc + 1, res);
    }
}
