#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int n;
char sequence[1000000];
int data [100000];
int data2[100000];
int inputPos;
int result[100000];


void merge(int from, int mid, int to) {
    int count1 = mid;
    int count2 = to - from - mid + 1;
    int pos1 = from;
    int pos2 = from + mid;
    int resPos = from;

    while (count1 > 0 && count2 > 0) {
        if (sequence[inputPos++] == '1') {
            data2[resPos] = data[pos1++];
            count1--;
        } else {
            data2[resPos] = data[pos2++];
            count2--;
        }
        resPos++;
    }

    while (count1-- > 0) data2[resPos++] = data[pos1++];
    while (count2-- > 0) data2[resPos++] = data[pos2++];
    FORE(i, from, to+1) data[i] = data2[i];
}

void sort(int from, int to) {
    if (from == to) return;

    int mid = (to - from + 1) / 2;
    sort(from, from + mid - 1);
    sort(from + mid, to);
    merge(from, mid, to);
}




int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        scanf("%d %s", &n, sequence);
        inputPos = 0;
        FOR(i, n) data[i] = i;
        sort(0, n - 1);
        FOR(i, n) {
            result[data[i]] = i + 1;
        }
        int res = 1;
        FOR(i, n) {
            res = (31 * res + result[i]) % 1000003;
        }

        printf("Case #%d: %d\n", cc + 1, res);
    }
}
