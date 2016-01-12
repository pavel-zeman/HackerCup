// Build the tree and recursively calculate the minimum sums for subtree of each node provided that the gift price for the node is a value from 1 to 19 (in reality 1 to 11 is sufficient)
// https://www.facebook.com/hackercup/problems.php?pid=759650454070547&round=344496159068801
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 200010
#define MAX_VALUE 20
#define INVALID -1

struct Node {
    vector<int> children;
    int result[MAX_VALUE];
} nodes[MAX_N];



char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


void calc(int node) {
    FOR(i, (int)nodes[node].children.size()) calc(nodes[node].children[i]);
    FORE(i, 1, MAX_VALUE) {
        int childrenTotal = 0;
        FOR(j, (int)nodes[node].children.size()) {
            int child = nodes[node].children[j];
            int localMin = INT_MAX;
            FORE(k, 1, MAX_VALUE)
                if (i != k && nodes[child].result[k] < localMin) localMin = nodes[child].result[k];
            childrenTotal += localMin;
        }
        nodes[node].result[i] = childrenTotal + i;
    }
}

int getMaxNumber(int node, int avoid) {
    int localValue = -1;
    int min = INT_MAX;
    FORE(i, 1, MAX_VALUE) if (i != avoid && nodes[node].result[i] < min) {
        min = nodes[node].result[i];
        localValue = i;
    }

    int localMax = localValue;
    FOR(i, (int)nodes[node].children.size()) {
        int temp = getMaxNumber(nodes[node].children[i], localValue);
        if (temp > localMax) localMax = temp;
    }
    return localMax;
}


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int n = getInt();
        FOR(i, MAX_N) {
            nodes[i].children.clear();
            FOR(j, MAX_VALUE) nodes[i].result[j] = INT_MAX;
        }
        FOR(i, n) {
            int parent = getInt() - 1;
            if (i != 0) nodes[parent].children.push_back(i);
        }
        calc(0);

        int min = INT_MAX;
        FOR(i, MAX_VALUE) if (nodes[0].result[i] < min) min = nodes[0].result[i];

        printf("Case #%d: %d\n", cc + 1, min);
        //printf("AA: %d\n", getMaxNumber(0, 0));
    }
}
