/*
    Author: Le Trong Dat
    Idea:
        * W(C, R, T) = True/False. True if Cop wins and False if Cop loses.
        * W(i, i, 0/1) = true because Cop already won.
        * W(C, R, 0) = True <=> Exists one state W(X, R, 1) = true.
        * W(C, R, 1) = true <=> All states W(C, X, 0) = true.
*/
#include "coprobber.h"
#include <bits/stdc++.h>
const int maxN = 500;
using namespace std;
#define forn(i, a, b)   for(int i=a; i<=b; ++i)
#define repn(i, a, b)   for(int i=a; i <b; ++i)

int cur;
int mov[maxN][maxN], deg[maxN][maxN];
int W[maxN][maxN][2];
int start(int N, bool A[maxN][maxN]) {
    queue < tuple < int, int, int > > q;
    repn(i, 0, N) repn(j, 0, N) repn(k, 0, N) deg[i][j] += A[j][k];
    repn(i, 0, N) forn(turn, 0, 1) {
        W[i][i][turn] = 1;
        q.push({i, i, turn});
    }
    while (q.size()) {
        int c, r, t;
        tie(c, r, t) = q.front();
        q.pop();
        repn(i, 0, N) { 
            if (t) {
                if ( (A[c][i] || i == c) && !W[i][r][0]) {
                    mov[i][r] = c;
                    W[i][r][0] = true;
                    q.push({i, r, 0});
                }
                continue;
            }
            if (A[r][i] && !W[c][i][1] && --deg[c][i] < 1) {
                W[c][i][1] = true;
                q.push({c, i, 1});
            }
        }
    }
    bool ok = true;
    repn(i, 0, N) ok &= W[0][i][0];
    return (ok ? 0 : -1);
}
int nextMove(int R) {
    return cur = mov[cur][R];
}