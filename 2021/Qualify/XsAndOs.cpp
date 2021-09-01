// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2021/qualification-round/problems/B
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

#define MAX_N 100
#define X 'X'
#define O 'O'
#define EMPTY '.'
#define INF 10000
char c[MAX_N][MAX_N];
bool used[MAX_N][MAX_N];
int n;

int findEmptyRow(int row) {
    FOR(i, n) if (c[row][i] == EMPTY) return i;
    exit(1);
}

int findEmptyColumn(int column) {
    FOR(i, n) if (c[i][column] == EMPTY) return i;
    exit(1);
}


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        FOR(i, n) getString(c[i]);
        int m = INF;
        int ways = 0;
        FOR(i, n) FOR(j, n) used[i][j] = false;
        FOR(i, n) {
            int os = 0, xs = 0;
            FOR(j, n) if (c[i][j] == O) os++; else if (c[i][j] == X) xs++;
            if (os == 0) {
                if (n - xs < m) { m = n - xs; ways = 0;}
                if (n - xs == m) ways++;
                if (m == 1) used[i][findEmptyRow(i)] = true;
            }
        }
        FOR(i, n) {
            int os = 0, xs = 0;
            FOR(j, n) if (c[j][i] == O) os++; else if (c[j][i] == X) xs++;
            if (os == 0) {
                if (n - xs < m) { m = n - xs; ways = 0;}
                if (n - xs == m) {
                    ways++;
                    if (m == 1 && used[findEmptyColumn(i)][i]) ways--;
                }
            }
        }
        printf("Case #%d: ", cc + 1);
        if (m != INF) printf("%d %d\n", m, ways); else printf("Impossible\n");
    }
}
