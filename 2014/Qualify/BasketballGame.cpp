// Simple simulation of the algorithm
// https://www.facebook.com/hackercup/problems.php?pid=740733162607577&round=598486203541358
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define FOR(c, m) for(int c=0;c<((int)m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


using namespace std;

int n, m, p;

struct Player {
    string name;
    int shotPercentage;
    int height;
    int draftNum;
    int minutes;
    bool plays;
};

vector<Player> players, team1, team2;

bool compareStats(const Player &player1, const Player &player2) {
    return player1.shotPercentage > player2.shotPercentage || (player1.shotPercentage == player2.shotPercentage && player1.height > player2.height);
}

bool compareName(const Player &player1, const Player &player2) {
    return player1.name < player2.name;
}


void rotate(vector<Player> & v) {
    FOR(i, v.size()) if (v[i].plays) v[i].minutes++;

    if (v.size() > (unsigned int)p) {
        int leaves = -1;
        int maxPlayed = 0;
        FOR(i, v.size()) {
            if (v[i].plays && v[i].minutes >= maxPlayed) {
                leaves = i;
                maxPlayed = v[i].minutes;
            }
        }
        v[leaves].plays = false;

        int enters = -1;
        int minPlayed = v[leaves].minutes + 1;
        FOR(i, v.size()) {
            if (!v[i].plays && v[i].minutes < minPlayed) {
                enters = i;
                minPlayed = v[i].minutes;
            }
        }
        v[enters].plays = true;
    }
}

void add(vector<Player> &src, vector<Player> &dest) {
    FOR(i, src.size()) if (src[i].plays) dest.push_back(src[i]);
}

int main(void) {
    int cases;
    cin >> cases;
    for (int cc=0;cc<cases;cc++) {
        cin >> n >> m >> p;
        players.clear();

        FOR(i, n) {
            Player player;
            cin >> player.name >> player.shotPercentage >> player.height;
            player.minutes = 0;
            players.push_back(player);
        }
        sort(players.begin(), players.end(), compareStats);
        team1.clear();
        team2.clear();
        FOR(i, players.size()) {
            players[i].draftNum = i;
            if ((i & 1) == 0) team1.push_back(players[i]); else team2.push_back(players[i]);
        }
        FOR(i, p) team2[i].plays = team1[i].plays = true;
        FOR(i, m) {
            rotate(team1);
            rotate(team2);
        }

        players.clear();
        add(team1, players);
        add(team2, players);
        sort(players.begin(), players.end(), compareName);
        cout << "Case #" << (cc + 1) << ":";
        FOR(i, players.size()) cout << " " << players[i].name;
        cout << endl;
    }
}
