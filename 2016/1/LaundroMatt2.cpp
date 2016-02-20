// Faster approach using heaps 
// https://www.facebook.com/hackercup/problem/1611251319125133/
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


#define MAX_N 100010
#define MAX_L 1000010
int w[MAX_N];
LLI washTime[MAX_L];


#define MAX_HEAP_ITEMS MAX_L
class HeapItem {
public:
    LLI value;
    int index; // index of the value in some external array

    HeapItem() {}

    HeapItem(LLI value, int index) {
        this->value = value;
        this->index = index;
    }
};


class MinHeap {
public:
    HeapItem data[MAX_HEAP_ITEMS];
    int size;

    MinHeap() {
        size = 0;
    }

    void clear() {
        size = 0;
    }

    int getSon(int a) {
        return (a << 1) + 1;
    }

    int getParent(int a) {
        return (a - 1) >> 1;
    }

    void up(int pos) {
        int parent = getParent(pos);
        HeapItem temp = data[pos];
        while (pos > 0 && temp.value < data[parent].value) {
            data[pos] = data[parent];
            pos = parent;
            parent = getParent(pos);
        }
        data[pos] = temp;
    }

    void down(int pos) {
        int son = getSon(pos);
        HeapItem temp = data[pos];
        while ((son < size && data[son].value < temp.value) || (son + 1 < size && data[son + 1].value < temp.value)) {
            int maxSon = son;
            if (son + 1 < size && data[son + 1].value < data[son].value) maxSon = son + 1;

            data[pos] = data[maxSon];

            pos = maxSon;
            son = getSon(pos);
        }
        data[pos] = temp;
    }

    void add(LLI value, int index) {
        int pos = size++;
        data[pos].index = index;
        data[pos].value = value;
        up(pos);
    }

    HeapItem removeTop() {
        HeapItem result = data[0];
        data[0] = data[--size];
        down(0);
        return result;
    }


    LLI minValue() {
        return data[0].value;
    }

    bool empty() {
        return size == 0;
    }

    void checkIntegrity() {
        FORE(i, 1, size) if (data[i].value < data[getParent(i)].value) {
            printf("Value at %d is less than value at %d\n", i, getParent(i));
            fail();
        }
    }
};

MinHeap heap;


int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        int l = getInt();
        int n = getInt();
        int m = getInt();
        int d = getInt();
        heap.clear();
        FOR(i, n) {
            w[i] = getInt();
            heap.add(w[i], i);
        }

        FOR(i, l) {
            HeapItem item = heap.removeTop();
            washTime[i] = item.value;
            heap.add(item.value + w[item.index], item.index);
        }

        heap.clear();
        int tt = min(l, m);
        LLI result = 0;
        FOR(i, tt) {
            result = washTime[i] + d;
            if (l - i > heap.size + tt) heap.add(result, 0);
        }

        FORE(i, tt, l) {
            HeapItem item = heap.removeTop();
            result = max(item.value, washTime[i]) + d;
            if (l - i > heap.size) heap.add(result, 0);
        }

        printf("Case #%d: %lld\n", cc + 1, result);
    }
}
