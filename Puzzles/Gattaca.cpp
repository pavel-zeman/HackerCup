#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)



int n, g;
char inputData[100];


struct item {
    int start, stop, score;
} items[10000];

int maxScore[sizeof(items) / sizeof(items[0])];

int compare(const item *a, const item *b) {
    if (a->start != b->start) return a->start - b->start;
    return a->stop - b->stop;
}


int solve(int start, int afterEnd) {
    int current = afterEnd - 1;
    maxScore[current] = items[current].score;
    while (--current >= start) {
        int v1 = maxScore[current + 1];
        int next = current + 1;
        while (next < afterEnd && items[next].start <= items[current].stop) {
            next++;
        }
        int v2 = items[current].score + (next == afterEnd ? 0 : maxScore[next]);
        maxScore[current] = v1 > v2 ? v1 : v2;
    }
    return maxScore[start];
}

int main(void) {
    scanf("%d", &n);
    FOR(i, (n - 1)/80 + 1) scanf("%s", inputData);
    scanf("%d", &g);
    FOR(i, g) scanf("%d %d %d", &items[i].start, &items[i].stop, &items[i].score);
    qsort(items, g, sizeof(items[0]), (int (*)(const void *, const void *))compare);

    int i = 0, score = 0;
    while (i < g) {
        int first = i, lastPosition = items[i].stop;
        while (++i < g && items[i].start <= lastPosition) {
            if (items[i].stop > lastPosition) lastPosition = items[i].stop;
        }
        score += solve(first, i);
    }
    printf("%d\n", score);
}
