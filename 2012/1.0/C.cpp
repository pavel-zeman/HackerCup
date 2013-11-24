#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <gmpxx.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


struct fraction {
    mpz_class v1, v2;

    fraction() {
    }

    fraction(int v) {
        v1 = v - 1;
        v2 = v;
    }

    fraction(int v1, int v2) {
        this->v1 = v1;
        this->v2 = v2;
    }

    fraction operator*(fraction &input) {
        fraction res;
        res.v1 = v1 * input.v1;
        res.v2 = v2 * input.v2;
        return res;
    }

    bool operator<(fraction &input) {
        return v1 * input.v2 < v2 * input.v1;
    }

    bool operator==(const fraction &input) {
        return v1 == input.v1 && v2 == input.v2;
    }

    void reduce() {
        mpz_class a = v1, b = v2;
        while (b > 0) {
            mpz_class c = a % b;
            a = b;
            b = c;
        }
        v1 /= a;
        v2 /= a;
    }

    const static fraction ZERO;

};

const fraction fraction::ZERO(0, 0);

int r, t;
int overtakeProb[100];
int noOvertakeProb[100];
fraction result[100][100];


fraction & calculate(int pos, int toOvertake) {
    if (result[pos][toOvertake] == fraction::ZERO) {
        fraction res;
        if (pos == t - 1) {
            if (toOvertake == 0) {
                res = fraction(noOvertakeProb[pos]);
            } else if (toOvertake == 1) {
                res = fraction(overtakeProb[pos]);
            } else {
                res = fraction(1);
            }
        } else {
            if (toOvertake == 0) {
                res = fraction(noOvertakeProb[pos]) * calculate(pos + 1, toOvertake);
            } else {
                fraction f1 = fraction(noOvertakeProb[pos]) * calculate(pos + 1, toOvertake);
                fraction f2 = fraction(overtakeProb[pos]) * calculate(pos + 1, toOvertake - 1);
                res = f1 < f2 ? f2 : f1;
            }
        }
        result[pos][toOvertake] = res;
    }
    return result[pos][toOvertake];
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        scanf("%d%d", &r, &t);
        FOR(i, t) scanf("%d %d", &overtakeProb[i], &noOvertakeProb[i]);
        FOR(i, t) FOR(j, r) result[i][j] = fraction::ZERO;

        fraction res = calculate(0, r - 1);
        res.reduce();
        printf("%s/%s\n", res.v1.get_str().c_str(), res.v2.get_str().c_str());
    }
}
