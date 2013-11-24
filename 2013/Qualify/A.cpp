#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int main(void) {
    char temp[10000];
    gets(temp);
    int cases = atoi(temp);
    for (int cc = 0;cc<cases;cc++) {
        gets(temp);
        char *curr = temp;
        while (*curr++ != ' ');
        curr[-1] = 0;

        int width = atoi(temp);

        char *start = curr;
        while (*curr++ != ' ');
        curr[-1] = 0;
        int height = atoi(start);

        int wordCount = 0;
        int wordLengths[1000];

        curr--;
        *curr = ' ';
        while (*curr != 0) {
            start = ++curr;
            while (*curr != ' ' && *curr != 0) curr++;
            wordLengths[wordCount++] = curr - start;
        }

        int maxSize = 0;

        while (true) {
            maxSize++;
            int x = 0;
            int rows = 1;
            for (int i=0;i<wordCount;i++) {
                if (x + maxSize * wordLengths[i] > width) {
                    if (maxSize * wordLengths[i] > width) {
                        goto end;
                    }
                    x = 0;
                    rows++;
                }
                x += maxSize * wordLengths[i] + maxSize;
            }
            if (rows * maxSize > height) {
                goto end;
            }
        }
        end:
        printf("Case #%d: %d\n", cc + 1, maxSize - 1);
    }
}
