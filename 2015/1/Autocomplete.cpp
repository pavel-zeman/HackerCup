// Build a trie and store total words going through each node. When typing a word, stop in a node with total words = 1.
// https://www.facebook.com/hackercup/problems.php?pid=313229895540583&round=344496159068801
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_LETTER 26


char word[1000010];

struct Node {
    int words;
    struct Node *children[MAX_LETTER];

    ~Node() {
        FOR(i, MAX_LETTER) if (children[i] != NULL) delete children[i];
    };
} root;

int getInt() {
    int d;
    scanf("%d", &d);
    return d;
}

void addWord(char *data) {
    Node *node = &root;
    while (*data != 0) {
        node->words++;
        int pos = *data - 'a';
        if (node->children[pos] == NULL) {
            Node *newNode = new Node();
            node->children[pos] = newNode;
            newNode->words = 0;
            FOR(i, MAX_LETTER) newNode->children[i] = NULL;
        }
        node = node->children[pos];
        data++;
    }
    node->words++;
}

int calcWord(char *data) {
    int total = 0;
    Node *node = &root;
    while (*data != 0) {
        if (node->words == 1) break;
        total++;
        node->words++;
        int pos = *data - 'a';
        node = node->children[pos];
        data++;
    }
    if (total == 0) total = 1;
    return total;
}

int main(void) {
    int cases = getInt();
    for (int cc=0;cc<cases;cc++) {
        root.words = 0;
        FOR(i, MAX_LETTER) if (root.children[i] != NULL) {
            delete root.children[i];
            root.children[i] = NULL;
        }

        int n = getInt();
        int total = 0;
        FOR(i, n) {
            scanf("%s", word);
            addWord(word);
            total += calcWord(word);
        }

        printf("Case #%d: %d\n", cc + 1, total);
    }
}
