// Simulate the laundry using ordered set and ordered map
// https://www.facebook.com/hackercup/problem/1611251319125133/
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
#define MAX_L 1000010
int w[MAX_N];
LLI washTime[MAX_L];

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int l = getInt();
        int n = getInt();
        int m = getInt();
        int d = getInt();
        set<pair<LLI, int> > washEnd;
        FOR(i, n) {
            w[i] = getInt();
            washEnd.insert(make_pair(w[i], i));
        }

        FOR(i, l) {
            pair<LLI, int> first = *washEnd.begin();
            washTime[i] = first.first;
            washEnd.erase(washEnd.begin());
            washEnd.insert(make_pair(first.first + w[first.second], first.second));
        }

        LLI result = 0;
        int remain = m;
        map<LLI, int> available;
        FOR(i, l) {
            while (!available.empty() && available.begin()->first <= washTime[i]) {
                remain += available.begin()->second;
                available.erase(available.begin());
            }
            if (remain > 0) {
                result = washTime[i] + d;
                remain--;
            } else {
                pair<LLI, int> first = *available.begin();
                if (first.second > 1)
                    available.begin()->second--;
                else
                    available.erase(available.begin());
                result = first.first + d;
            }
            available[result]++;
        }

        printf("Case #%d: %lld\n", cc + 1, result);
    }
}
