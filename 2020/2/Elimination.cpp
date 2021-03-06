// Description
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-2/problems/B
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

#define MAX_N 8192

double p;
double em[MAX_N][MAX_N];
double el[MAX_N][MAX_N];

double expectedLoss(int i, int n) {
    int total = n * (n - 1) / 2;
    return (1 - p) * i / total + p * (n - 1 - i) / total;
}

double expectedMatches(int i, int n) {
    double result = el[i][n];
    if (i > 0) result -= el[i - 1][n];
    if (i > 0) result += el[i - 1][n] * (1 + em[i - 1][n - 1]);
    if (i < n - 1) result += (el[n - 1][n] - el[i][n]) * (1 + em[i][n - 1]);
    return result;
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        int n;
        scanf("%d", &n);
        scanf("%lf", &p);

        FORE(i, 1, n + 1) FOR(j, i) {
            el[j][i] = expectedLoss(j, i);
            if (j > 0) el[j][i] += el[j - 1][i];
        }
        em[0][1] = 0;
        FORE(i, 2, n + 1) FOR(j, i) em[j][i] = expectedMatches(j, i);

        printf("Case #%d:\n", cc + 1);
        FOR(i, n) printf("%.10lf\n", em[i][n]);
    }
}
