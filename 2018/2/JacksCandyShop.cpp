// Description
// https://www.facebook.com/hackercup/problem/638251746380051/
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

#define MAX_N 200010
#define MAX_M 1000010
int value[MAX_N];
int n, m, a, b;
int vPos;

struct Node {
    int depth;
    int s, e;
} nodes[MAX_N];

pair<int, int> customer[MAX_M];
int tree[3 * MAX_N];
int treePos[3 * MAX_N];
vector<int> children[MAX_N];


int buildTree(int node, int l, int r) {
    if (l == r) {
        tree[node] = value[l];
        treePos[node] = l;
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        int res1 = buildTree(childNode, l, middle);
        int res2 = buildTree(childNode + 1, middle + 1, r);
        tree[node] = max(res1, res2);
        treePos[node] = res1 > res2 ? treePos[childNode] : treePos[childNode + 1];
    }
    return tree[node];
}

int gatherResult(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return n;
    else {
        if (l >= start && r <= end) return treePos[node];
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        int res1 = gatherResult(childNode, l, middle, start, end);
        int res2 = gatherResult(childNode + 1, middle + 1, r, start, end);
        return value[res1] > value[res2] ? res1 : res2;
    }
}

int updateTree(int node, int l, int r, int pos) {
    if (pos < l || pos > r) return tree[node];
    if (l == r) {
        tree[node] = value[pos];
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        int res1 = updateTree(childNode, l, middle, pos);
        int res2 = updateTree(childNode + 1, middle + 1, r, pos);
        tree[node] = max(res1, res2);
        treePos[node] = res1 > res2 ? treePos[childNode] : treePos[childNode + 1];
    }
    return tree[node];
}

void fillValues(int node, int d) {
    nodes[node].s = vPos;
    nodes[node].depth = d;
    value[vPos++] = node;
    FOR(i, children[node].size()) fillValues(children[node][i], d + 1);
    nodes[node].e = vPos - 1;
}


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        n = getInt();
        m = getInt();
        a = getInt();
        b = getInt();
        value[n] = -1;

        FOR(i, n) children[i].clear();
        FORE(i, 1, n) {
            int p = getInt();
            children[p].push_back(i);
        }
        vPos = 0;
        fillValues(0, 0);
        buildTree(0, 0, n - 1);


        FOR(i, m) {
            int c = (a * (LLI)i + b) % n;
            customer[i].first = nodes[c].depth;
            customer[i].second = i;
        }
        sort(customer, customer + m);

        LLI total = 0;
        for(int i = m - 1; i >=0; i--) {
            int c = (a * (LLI) customer[i].second + b) % n;
            int resultPos = gatherResult(0, 0, n - 1, nodes[c].s, nodes[c].e);
            if (value[resultPos] >= 0) {
                total += value[resultPos];
                value[resultPos] = -1;
                updateTree(0, 0, n - 1, resultPos);
            }
        }


        printf("Case #%d: %lld\n", cc + 1, total);
    }
}
