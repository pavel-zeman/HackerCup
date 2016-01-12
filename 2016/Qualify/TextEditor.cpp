// Sort the list of words and then use dynamic programming to select subset of size K
// https://www.facebook.com/hackercup/problem/1525154397757404/
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

#define MAX_N 310
#define MAX_LENGTH 100010
#define MAX_RES 10000000
int commonPrefix[MAX_N][MAX_N];
int pos[MAX_N];
char data[MAX_LENGTH];
int order[MAX_N];
int res[MAX_N][MAX_N];
int length[MAX_N];

int getCommonPrefix(int a, int b) {
    int pos1 = pos[a];
    int pos2 = pos[b];
    int res = 0;
    while (data[pos1++] == data[pos2++]) res++;
    return res;
}

int cmp(const void *v1, const void *v2) {
     int o1 = *(int *)v1;
     int o2 = *(int *)v2;
     return data[pos[o1] + commonPrefix[o1][o2]] - data[pos[o2] + commonPrefix[o1][o2]];
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        int n = getInt();
        int k = getInt();
        pos[0] = 0;
        FOR(i, n) {
            length[i] = getString(data + pos[i]);
            pos[i + 1] = pos[i] + length[i] + 1;
        }
        FOR(i, n) FORE(j, i + 1, n) commonPrefix[i][j] = commonPrefix[j][i] = getCommonPrefix(i, j);
        FOR(i, n) order[i] = i;
        qsort(order, n, sizeof(order[0]), cmp);
        int t;
        FOR(i, n + 1) FOR(j, n + 1) res[i][j] = MAX_RES;
        FOR(i, n) {
            res[i][1] = length[order[i]] + 1;
            FORE(j, 2, k + 1) {
                t = MAX_RES;
                int l = i - 1;
                while (l + 1 >= j - 1) {
                    t = min(t, length[order[i]] + length[order[l]] - 2 * commonPrefix[order[i]][order[l]] + 1 + res[l][j - 1]);
                    l--;
                }
                res[i][j] = t;
            }
        }

        t = MAX_RES;
        FOR(i, n) t = min(t, res[i][k] + length[order[i]]);

        printf("Case #%d: %d\n", cc + 1, t);
    }
}
