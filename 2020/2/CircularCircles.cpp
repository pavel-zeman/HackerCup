// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-2/problems/C
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
int x[MAX_N];
int y[MAX_N];
int ii[MAX_N];
int w[MAX_N];
int ww[MAX_N];
int n, m, e, k;
int component[MAX_N];
int comps[MAX_N];
set<pair<int, int> > gc, sc[MAX_N][2], sc1, sc2;


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        m = getInt();
        e = getInt();
        k = getInt();

        FOR(i, k) x[i] = getInt();
        int a = getInt();
        int b = getInt();
        int c = getInt();
        FORE(i, k, n) x[i] = (a * (LLI)x[i - 2] + b * (LLI)x[i - 1] + c) % m;

        FOR(i, k) y[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        FORE(i, k, n) y[i] = (a * (LLI)y[i - 2] + b * (LLI)y[i - 1] + c) % m;

        FOR(i, k) ii[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        FORE(i, k, e) ii[i] = (a * (LLI)ii[i - 2] + b * (LLI)ii[i - 1] + c) % (n * m + n);

        FOR(i, k) ww[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        FORE(i, k, e) ww[i] = (a * (LLI)ww[i - 2] + b * (LLI)ww[i - 1] + c) % 1000000000;

        FOR(i, m * n + n) w[i] = 1;

        gc.clear();
        FORE(i, n * m, n * m + n) gc.insert(make_pair(w[i], i));

        FOR(i, n) {
            sc[i][0].clear();
            sc[i][1].clear();

            if (x[i] == y[i]) {
                FOR(j, m) component[i * m + j] = 0;
                FOR(j, m) sc[i][0].insert(make_pair(w[i * m + j], i * m + j));
                comps[i] = 1;
            } else {
                comps[i] = 2;
                int j = x[i];
                while (j != y[i]) {
                    component[i * m + j] = 0;
                    j++;
                    j %= m;
                }
                while (j != x[i]) {
                    component[i * m + j] = 1;
                    j++;
                    j %= m;
                }
                FOR(j, m) {
                    int tt = i * m + j;
                    sc[i][component[tt]].insert(make_pair(w[tt], tt));
                }
            }
        }
        LLI totalW = 0;
        LLI totalWGreat = 0;
        LLI totalW1 = 0;
        LLI totalDegen = 0;
        FOR(i, m * n + n) totalW += w[i];
        FORE(i, m * n, m * n + n) totalWGreat += w[i];
        sc1.clear();
        sc2.clear();
        FOR(i, n)
            if (comps[i] == 2) {
                auto w1 = *sc[i][0].rbegin();
                auto w2 = *sc[i][1].rbegin();
                if (w1.first < w2.first) {
                    pair<int, int> w3 = w1;
                    w1 = w2;
                    w2 = w3;
                }
                totalW1 += w1.first;
                sc1.insert(w1);
                sc2.insert(w2);
            } else {
                totalDegen += sc[i][0].rbegin()->first;
            }

        LLI result = 1;
        FOR(i, e) {
            int edge = ii[i];
            int neww = ww[i];

            pair<int, int> origEdge = make_pair(edge, w[edge]);
            if (edge < m * n) {
                // small circle
                int j = edge / m;
                if (comps[j] == 1) {
                    totalDegen -= sc[j][0].rbegin()->first;
                    sc[j][0].erase(make_pair(w[edge], edge));
                    sc[j][0].insert(make_pair(neww, edge));
                    totalDegen += sc[j][0].rbegin()->first;
                } else {
                    auto w1 = *sc[j][0].rbegin();
                    auto w2 = *sc[j][1].rbegin();
                    if (w1.first < w2.first) {
                        pair<int, int> w3 = w1;
                        w1 = w2;
                        w2 = w3;
                    }
                    totalW1 -= w1.first;
                    if (component[edge] == 0) {
                        sc[j][0].erase(make_pair(w[edge], edge));
                        sc[j][0].insert(make_pair(neww, edge));
                    } else {
                        sc[j][1].erase(make_pair(w[edge], edge));
                        sc[j][1].insert(make_pair(neww, edge));
                    }
                    sc1.erase(w1);
                    sc2.erase(w2);

                    w1 = *sc[j][0].rbegin();
                    w2 = *sc[j][1].rbegin();
                    if (w1.first < w2.first) {
                        pair<int, int> w3 = w1;
                        w1 = w2;
                        w2 = w3;
                    }
                    totalW1 += w1.first;
                    sc1.insert(w1);
                    sc2.insert(w2);
               }
            } else {
                // great circle
                gc.erase(make_pair(w[edge], edge));
                gc.insert(make_pair(neww, edge));
                totalWGreat += neww - w[edge];
            }
            totalW += neww - w[edge];
            w[edge] = neww;

            LLI currentW = totalW - totalW1 - totalDegen;
            if (sc2.empty() || gc.rbegin()->first > sc2.rbegin()->first) currentW -= gc.rbegin()->first; else currentW -= sc2.rbegin()->first;
            result = result * (currentW % MOD) % MOD;
        }


        printf("Case #%d: %lld\n", cc + 1, result);
    }
}
