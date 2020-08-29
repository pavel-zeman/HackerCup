// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/A3
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
map<int, int> steps;

int getLength(int a, int b) {
    auto it = steps.lower_bound(a);
    if (it->first > a) {
        it--;
        steps.insert(make_pair(a, it->second));
    }
    auto it2 = steps.lower_bound(b);
    if (it2->first > b) {
        it2--;
        steps.insert(make_pair(b, it2->second));
    }
    it = steps.find(a);
    LLI res = 0;

    auto prev = it;
    prev--;
    while (it->first < b) {
        if (it->second > 0) {
            auto next = it;
            next++;
            res += 2 * (next->first - it->first);
            res += abs(prev->second - it->second);
        } else {
            res += prev->second;
        }
        it++;
        prev++;
    }
    res += abs(prev->second - it->second);

    steps.erase(++steps.find(a), it);

    return res % MOD;
}


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
        steps.clear();
        steps.insert(make_pair(0, 0));
        steps.insert(make_pair(l[0], h[0]));
        steps.insert(make_pair(l[0] + w[0], 0));
        steps.insert(make_pair(2000000000, 0));

        FORE(i, 1, n) {
            p = (p - getLength(l[i], l[i] + w[i]) + MOD) % MOD;
            auto it = steps.find(l[i]);
            LLI add = 2 * w[i];
            auto prev = it;
            prev--;
            add += abs(prev->second - h[i]);
            add += abs(h[i] - steps[l[i] + w[i]]);
            steps[l[i]] = h[i];
            add %= MOD;
            p = (p + add) % MOD;
            res = res * p % MOD;
        }


        printf("Case #%d: %lld\n", cc + 1, res);
    }
}
