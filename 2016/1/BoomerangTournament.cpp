// Dynamic programming - maintain list of possible winners for all subsets of size of power of 2
// https://www.facebook.com/hackercup/problem/1424196571244550/
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

#define MAX_N 16
vector<int> masks[5];
bool win[MAX_N][MAX_N];
vector<int> winners[1 << MAX_N];
int maxWins[MAX_N];
int resultPos[MAX_N];


int numBits(int a) {
    int res = 0;
    while (a > 0) {
        res += a & 1;
        a >>= 1;
    }
    return res;
}

int getMask(int *positions, int mask) {
    int i = 0;
    int res = 0;
    while (mask > 0) {
        if ((mask & 1) == 1) res |= 1 << positions[i];
        mask >>= 1;
        i++;
    }
    return res;
}

void calc(int mask, int order) {
    if (winners[mask].empty()) {
        int positions[MAX_N];
        int pos = 0;
        int t = mask;
        int nOrder = order - 1;
        bool result[MAX_N];
        memset(result, 0, sizeof(result));
        for(int i=0;t>0;i++) {
            if ((t & 1) == 1) positions[pos++] = i;
            t >>= 1;
        }
        FOR(i, masks[nOrder].size()) {
            int mask1 = getMask(positions, masks[nOrder][i]);
            int mask2 = mask ^ mask1;
            calc(mask1, nOrder);
            calc(mask2, nOrder);
            FOR(j, winners[mask1].size()) FOR(k, winners[mask2].size()) {
                int w1 = winners[mask1][j];
                int w2 = winners[mask2][k];
                result[win[w1][w2] ? w1 : w2] = true;
            }
        }
        FOR(j, MAX_N)
            if (result[j]) winners[mask].push_back(j);
    }
}


bool isAllTrue(int pos, int n) {
    FOR(i, n) if (i != pos && !win[pos][i]) return false;
    return true;
}

int main(void) {
    FORE(i, 1, 4) {
        int bits = 1 << i;
        FOR(j, 1 << (bits * 2 - 1)) {
            if (numBits(j) == bits) {
                masks[i].push_back(j);
            }
        }
    }
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int n = getInt();
        int temp = n >> 1;
        int order = 0;
        while (temp > 0) { order++; temp >>= 1; }

        resultPos[order] = 1;
        for(int i=order - 1, pow = 1;i>=0;i--) {
            resultPos[i] = resultPos[order] + pow;
            pow <<= 1;
        }

        FOR(i, n) FOR(j, n) win[i][j] = getInt() == 1;
        FOR(i, 1 << n) winners[i].clear();

        printf("Case #%d:\n", cc + 1);
        if (n == 1) printf("1 1\n");
        else {
            FOR(i, n) FORE(j, i + 1, n) winners[(1 << i) | (1 << j)].push_back(win[i][j] ? i : j);
            calc((1 << n) - 1, order);
            FOR(i, n) maxWins[i] = 0;
            FOR(i, 1 << n)
                if (!winners[i].empty()) {
                    int bits = numBits(i) >> 1;
                    int numWins = 0;
                    while (bits > 0) { numWins++; bits >>= 1;}
                    FOR(j, winners[i].size())
                        if (numWins > maxWins[winners[i][j]])
                            maxWins[winners[i][j]] = numWins;
                }
            FOR(i, n) {
                int worstPos = isAllTrue(i, n) ? 1 : resultPos[0];
                int bestPos = resultPos[maxWins[i]];
                printf("%d %d\n", bestPos, worstPos);
            }

        }

    }
}
