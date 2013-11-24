#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int n, d;
int totalNeighbors;
struct {
    int a;
    int b;
    int aFirst;
    int bFirst;
} mergers[100000];


struct {
    int neighbor;
    int merger;
    int next;
} neighbors[100000];

int count[100000];


void addNeighbor(int from, int to, int merger) {
    int item;
    if (neighbors[from].neighbor == -1) {
        item = from;
    } else {
        int curr = from;
        while (neighbors[curr].next != -1) {
            curr = neighbors[curr].next;
        }
        neighbors[curr].next = ++totalNeighbors;
        item = totalNeighbors;
    }
    neighbors[item].neighbor = to;
    neighbors[item].merger = merger;
    neighbors[item].next = -1;
}

void calc(int merger, bool aFirst);


int getMax(int root, int parent) {
    int item = root;
    int max = 1;
    while (item != -1) {
        if (neighbors[item].neighbor != parent) {
            int merger = neighbors[item].merger;
            calc(merger, mergers[merger].a == root);
            int res = (mergers[merger].a == root ? mergers[merger].aFirst : mergers[merger].bFirst) + 1;
            if (res > max) max = res;
        }
        item = neighbors[item].next;
    }
    printf("Getting max: %d %d: %d\n", root, parent, max);
    return max;
}

void calc(int merger, bool aFirst) {
    if (aFirst && mergers[merger].aFirst == -1) {
        mergers[merger].aFirst = getMax(mergers[merger].b, mergers[merger].a);
        printf("Calc merger: %d\n", merger);
    }
    if (!aFirst && mergers[merger].bFirst == -1) {
        mergers[merger].bFirst = getMax(mergers[merger].a, mergers[merger].b);
        printf("Calc merger: %d\n", merger);
    }
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        scanf("%d %d", &n, &d);
        FOR(i, n-1) {
            scanf("%d %d", &mergers[i].a, &mergers[i].b);
            mergers[i].aFirst = -1;
            mergers[i].bFirst = -1;
        }
        FOR(i, n) neighbors[i + 1].neighbor = -1;

        totalNeighbors = n + 1;

        printf("Adding neightbors\n");
        FOR(i, n-1) {
            addNeighbor(mergers[i].a, mergers[i].b, i);
            addNeighbor(mergers[i].b, mergers[i].a, i);
        }

        printf("Calc\n");
        FOR(i, n - 1) {
            calc(i, true);
            calc(i, false);
        }

        printf("Counts\n");
        FORE(i, 1, n + 1) {
            count[i] = 0;
            int item = i;
            while (item != -1) {
                count[i]++;
                item = neighbors[item].next;
            }
        }

        int min = n;
        FORE(i, 1, n + 1) {
            if (count[i] > d + 1) {
                printf("Error: %d %d\n", i, count[i]);
            } else if (count[i] <= d) {
                int max = getMax(i, -1);
                if (max < min) min = max;
            }
        }

        printf("Case #%d: %d\n", cc + 1, min);
    }
}
