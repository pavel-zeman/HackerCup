// Start searching from the beginning and keep 3 sets - board1, board2 and symmetric difference of board1 and board2 - if the difference is empty, both sets are the same, so we add "something" to the result 
// https://www.facebook.com/hackercup/problems.php?pid=620734011349888&round=544142832342014
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <set>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1000100



using namespace std;

int board1[MAX_N];
int board2[MAX_N];

int n, m;
long long int x1, a1, b1, c1, r1;
long long int x2, a2, b2, c2, r2;

set<int> s1;
set<int> s2;
set<int> common;


int max(int a, int b) {
    return a > b ? a : b;
}

void addCommon(int a) {
    if (common.find(a) != common.end()) {
        common.erase(a);
    } else {
        common.insert(a);
    }

}
int main(void) {
    int cases;
    scanf("%d", &cases);
    for (int cc=0;cc<cases;cc++) {
        scanf("%d %d", &n, &m);
        scanf("%lld %lld %lld %lld %lld", &x1, &a1, &b1, &c1, &r1);
        scanf("%lld %lld %lld %lld %lld", &x2, &a2, &b2, &c2, &r2);

        board1[0] = x1;
        board2[0] = x2;
        int x = max(n, m);
        FORE(i, 1, x) {
            if (i < n) {
                board1[i] = (a1 * board1[(i - 1) % n] + b1 * board2[(i - 1) % m] + c1) % r1;
            }
            if (i < m) {
                board2[i] = (a2 * board1[(i - 1) % n] + b2 * board2[(i - 1) % m] + c2) % r2;
            }
        }
        /*FOR(i, n) printf("%d ", board1[i]);
        printf("\n");
        FOR(i, m) printf("%d ", board2[i]);
        printf("\n");*/

        s1.clear();
        s2.clear();
        common.clear();

        long long int total = 0;
        int p1 = 0;
        int p2 = 0;
        while (true) {
            if (common.size() == 0 && s1.size() > 0 && s2.size() > 0) {
                int p1s = p1 - 1;
                int p2s = p2 - 1;
                while (p1 < n && s1.find(board1[p1]) != s1.end()) p1++;
                while (p2 < m && s2.find(board2[p2]) != s2.end()) p2++;
                total += ((long long int)(p1 - p1s)) * (p2 - p2s);
                //printf("Adding %d-%d, %d-%d\n", p1s, p1, p2s, p2);
            }
            if (p1 == n || p2 == m) break;
            while (p1 < n && s1.find(board1[p1]) != s1.end()) p1++;
            while (p2 < m && s2.find(board2[p2]) != s2.end()) p2++;
            if (p1 < n) {
                s1.insert(board1[p1]);
                addCommon(board1[p1]);
                p1++;
            }
            if (p2 < m) {
                s2.insert(board2[p2]);
                addCommon(board2[p2]);
                p2++;
            }
            if (s1.size() != s2.size()) break;
        }

        printf("Case #%d: %lld\n", cc + 1, total);
    }
}
