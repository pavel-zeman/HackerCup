// Description
// https://www.facebook.com/hackercup/problem/232395994158286/
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

#define MAX_N 2048
int n, k;
int children[MAX_N][2];

int preOrderPos;
int preOrderIndex[MAX_N];
int postOrderPos;
int postOrderIndex[MAX_N];
int l[MAX_N];


void preOrder(int node) {
    preOrderIndex[preOrderPos++] = node;
    FOR(i, 2) if (children[node][i] != 0) preOrder(children[node][i]);
}

void postOrder(int node) {
    FOR(i, 2) if (children[node][i] != 0) postOrder(children[node][i]);
    postOrderIndex[postOrderPos++] = node;
}




int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int n = getInt();
        int k = getInt();
        FOR(i, n) {
            children[i + 1][0] = getInt();
            children[i + 1][1] = getInt();
            l[i + 1] = 0;
        }
        preOrderPos = 0;
        postOrderPos = 0;
        preOrder(1);
        postOrder(1);
        int curK = 1;
        bool possible = true;
        bool allK = false;

        FOR(i, n) {
            if (!l[preOrderIndex[i]]) {
                int pos = i;
                while (true) {
                    l[preOrderIndex[pos]] = curK;
                    if (l[postOrderIndex[pos]] == curK) break;
                    if (l[postOrderIndex[pos]] > 0) {
                        possible = false;
                        goto e;
                    }
                    FOR(j, n) if (preOrderIndex[j] == postOrderIndex[pos]) {
                        pos = j;
                        break;
                    }
                }
                if (curK < k) curK++; else allK = true;
            }
        }
        e:

        printf("Case #%d:", cc + 1);
        if (possible && allK) {
            FOR(i, n) printf(" %d", l[i + 1]);
            /*FOR(i, n) if (l[preOrderIndex[i]] != l[postOrderIndex[i]]) {
                printf("Error at pos: %d\n", i);
                return 1;
            }*/
        }
        else printf(" Impossible");
        printf("\n");
    }
}
