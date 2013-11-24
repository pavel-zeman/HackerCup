#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char strings[10][20];
int m;


int compare(const char *a, const char *b) {
    char buffer1[100], buffer2[100];
    strcpy(buffer1, a);
    strcat(buffer1, b);
    strcpy(buffer2, b);
    strcat(buffer2, a);
    return strcmp(buffer1, buffer2);
}


int main(void) {
    int n;
    scanf("%d", &n);
    for(int c=1;c<=n;c++) {

        scanf("%d", &m);
        FOR(i, m) scanf("%s", strings[i]);
        qsort(strings, m, sizeof(strings[0]), (int (*)(const void *, const void *))compare);
        FOR(i, m) printf("%s", strings[i]);
        printf("\n");
    }
}
