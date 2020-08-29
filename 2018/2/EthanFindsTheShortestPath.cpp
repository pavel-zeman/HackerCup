//
// https://www.facebook.com/hackercup/problem/988017871357549/
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

struct Edge {
    int a, b;
    int w;

    Edge(int a, int b, int w) {
        this->a = a;
        this->b = b;
        this->w = w;
    }
};

vector<Edge> edges;

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int n = getInt();
        int k = getInt();
        int result;
        edges.clear();
        edges.push_back(Edge(1, n, k));
        if (k == 1 || n == 2) {
            result = 0;
        } else {
            int res1 = k;
            int res2 = 0;
            int r = k - 1;
            FORE(i, 1, n) {
                res2 += r;
                if (r == 1) {
                    edges.push_back(Edge(i, n, r));
                    break;
                } else edges.push_back(Edge(i, i + 1, r));
                r--;
            }
            if (res2 <= res1) {
                result = 0;
                edges.clear();
                edges.push_back(Edge(1, n, k));
            } else {
                result = res2 - res1;
            }
        }
        printf("Case #%d: %d\n", cc + 1, result);
        printf("%d\n", edges.size());
        FOR(i, edges.size())
            printf("%d %d %d\n", edges[i].a, edges[i].b, edges[i].w);
    }
}
