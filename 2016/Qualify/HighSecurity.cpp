// Handle gaps of size 1 in a special way (place the guard in the other row in the same column). Then add guards to remaining free space.
// https://www.facebook.com/hackercup/problem/1527664744192390/
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

#define MAX_N 1010
#define EMPTY '.'
#define GUARD 'G'
char data[2][MAX_N];
int n;

int getLength(int row, int column) {
    int res = 0;
    while (column < n && data[row][column] == EMPTY) column++, res++;
    return res;
}

void fillGuards(int row, int column) {
    if (data[row][column] == EMPTY) {
        FORE(i, column, n) if (data[row][i] == EMPTY) data[row][i] = GUARD; else break;
        column--;
        while (column >= 0 && data[row][column] == EMPTY) {
            data[row][column] = GUARD;
            column--;
        }
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        getString(data[0]);
        getString(data[1]);

        int guards = 0;
        FOR(i, 2) FOR(j, n) {
            int l = getLength(i, j);
            if (l == 1) {
                guards++;
                data[i][j] = GUARD;
                fillGuards((i + 1)&1, j);
            }
            j += l;
        }
        FOR(i, 2) FOR(j, n) {
            int l = getLength(i, j);
            if (l > 0) guards++;
            j += l;
        }

        printf("Case #%d: %d\n", cc + 1, guards);
    }
}
