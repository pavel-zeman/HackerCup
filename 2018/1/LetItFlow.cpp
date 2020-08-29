// Description
// https://www.facebook.com/hackercup/problem/180494849326631/
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

#define MAX_N 1024
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
bool gridEmpty[3][MAX_N];
int n;
char line[MAX_N];
int result[3][MAX_N][3];


int getResult(int r, int c, int dir) {
    if (r < 0 || r >= 3) return 0;
    if (c < 0) return 0;
    int localRes = result[r][c][dir];
    if (localRes == -1) {
        if (!gridEmpty[r][c]) localRes = 0;
        else {
            switch (dir) {
            case TOP:
            case BOTTOM:
                localRes = getResult(r, c - 1, RIGHT);
                break;
            case RIGHT:
                localRes = (getResult(r - 1, c, BOTTOM) + getResult(r + 1, c, TOP)) % MOD;
                break;
            }
        }
        result[r][c][dir] = localRes;
    }
    return localRes;
}

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        FOR(i, 3) {
            getString(line);
            FOR(j, n) gridEmpty[i][j] = line[j] == '.';
        }
        FOR(i, 3) FOR(j, n) FOR(k, 3) result[i][j][k] = -1;
        result[0][0][BOTTOM] = gridEmpty[0][0] ? 1 : 0;
        result[0][0][TOP] = result[0][0][RIGHT] = 0;

        printf("Case #%d: %d\n", cc + 1, getResult(2, n - 1, RIGHT));
    }
}
