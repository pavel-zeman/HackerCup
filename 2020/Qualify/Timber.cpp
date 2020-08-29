// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/C
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

#define MAX_N 800010
pair<int, int> tree[MAX_N];
unordered_map<int, int> treeMap;
unordered_map<int, int> leftResult;

int result[MAX_N][2];



int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        treeMap.clear();
        leftResult.clear();
        int n = getInt();
        FOR(i, n) {
            int p = getSignedInt();
            int h = getSignedInt();
            tree[i].first = p;
            tree[i].second = h;
        }
        sort(tree, tree + n);
        FOR(i, n) {
            treeMap.insert(make_pair(tree[i].first, i));
            result[i][0] = result[i][1] = 0;
        }

        for(int i = n - 1; i >= 0; i--) {
            // to the left
            int mx = tree[i].second;
            auto it = leftResult.find(tree[i].first);
            if (it != leftResult.end()) mx += it->second;
            result[i][0] = mx;
            it = leftResult.find(tree[i].first - tree[i].second);
            if (it == leftResult.end()) leftResult.insert(make_pair(tree[i].first - tree[i].second, mx)); else {
                if (mx > it->second) it->second = mx;
            }

            // to the right
            mx = tree[i].second;
            auto it2 = treeMap.find(tree[i].first + tree[i].second);
            if (it2 != treeMap.end()) mx += result[it2->second][1];
            it = leftResult.find(tree[i].first + tree[i].second);
            if (it != leftResult.end() && tree[i].second + it->second > mx) {
                mx = tree[i].second + it->second;
            }

            result[i][1] = mx;
        }
        int mx = 0;
        FOR(i, n) FOR(j, 2) if (result[i][j] > mx) mx = result[i][j];
        printf("Case #%d: %d\n", cc + 1, mx);
    }
}
