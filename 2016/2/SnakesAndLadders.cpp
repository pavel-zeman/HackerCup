// Maintain ordered set of ladders, that can be still used, and update it with each new ladder
// https://www.facebook.com/hackercup/problem/1640119959603837/
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

#define MAX_N 200010
int x[MAX_N], h[MAX_N];
int n;
set<int> used;
int counts[MAX_N];
LLI sums[MAX_N], sums2[MAX_N];
int lastPos[MAX_N];

void renum() {
    map<int, int> t;
    FOR(i, n) t[h[i]] = 0;
    int ind = 0;
    for(map<int, int>::iterator it = t.begin(); it != t.end(); it++) {
        it->second = ind++;
    }
    FOR(i, n) h[i] = t[h[i]];
}

LLI sq(LLI a) {
    return a * a % MOD;
}

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        vector<pair<int, int> > data;
        FOR(i, n) {
            x[i] = getInt();
            h[i] = getInt();
            data.push_back(make_pair(x[i], h[i]));
        }
        sort(data.begin(), data.end());
        FOR(i, n) {
            x[i] = data[i].first;
            h[i] = data[i].second;
        }
        renum();
        used.clear();
        FOR(i, n) counts[i] = sums[i] = 0;

        LLI total = 0;
        FOR(i, n) {
            int curH = h[i];
            if (used.find(curH) == used.end()) {
                counts[curH] = 0;
                sums[curH] = 0;
                lastPos[curH] = x[i];
                sums2[curH] = 0;
                used.insert(curH);
            } else {
                int dist = x[i] - lastPos[curH];
                LLI sumsLocal = (sums2[curH] + 2 * dist * sums[curH] % MOD + counts[curH] * sq(dist) % MOD) % MOD;
                sumsLocal = (sumsLocal + sq(dist)) % MOD;
                total = (total + sumsLocal) % MOD;
                sums[curH] = (sums[curH] + counts[curH] * (LLI)dist + dist) % MOD;
                lastPos[curH] = x[i];
                sums2[curH] = sumsLocal;
                counts[curH]++;
            }
            for(set<int>::iterator it = used.begin(); ;){
                if (*it < curH) {
                    set<int>::iterator it2 = it;
                    it2++;
                    used.erase(it);
                    it = it2;
                } else
                    break;
            }
        }

        printf("Case #%d: %lld\n", cc + 1, total);
    }
}
