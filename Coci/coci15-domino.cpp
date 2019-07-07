/*
    Author: Le Trong Dat.
    Idea: http://hsin.hr/coci/archive/2015_2016/.
    Contest 3. Problem 6.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
const int maxN = 2010;
const int maxK = 55;
const int INF = 1e8;
const int maxMask = (1 << 20) +2;
const int maxNode = 2 * maxN * maxN;
int N, K;
int nNode, sz1, sz2;
int Num[maxN][maxN];
int dp[maxMask];
long long Sum;
int result;
int dx[] = {0, -1};
int dy[] = {-1, 0};
bool edge[3][maxK][maxK];
bool equal(int x1, int y1, int x2, int y2) {
    return (x1 == x2 && y1 == y2);
}
struct Domino {
    int x1, y1, x2, y2;
    int id;
    int value;
    Domino(){};
    Domino(int x1, int y1, int x2, int y2, int id, int value) :
                 x1(x1), y1(y1), x2(x2), y2(y2), id(id), value(value) {};
    bool overlaps(const Domino& oo) {
        if (equal(this->x1, this->y1, oo.x1, oo.y1)) return true;
        if (equal(this->x1, this->y1, oo.x2, oo.y2)) return true;
        if (equal(this->x2, this->y2, oo.x1, oo.y1)) return true;
        if (equal(this->x2, this->y2, oo.x2, oo.y2)) return true;
        return false;
    }
    bool operator < (const Domino& oo) {
        return this->value < oo.value;
    }
} domino[maxNode], A[maxK], B[maxK];
int gBit(int mask, int i) {
    return (mask >> i & 1);
}
bool isClique(int mask) {
    forn(i, 0, sz1-1) if (gBit(mask, i)) {
        forn(j, i+1, sz1-1) if (gBit(mask, j) && !edge[0][i+1][j+1]) return false;
    }
    return true;
}
int gSum(int mask) {
    int S = 0;
    repn(i, 0, sz1) if (gBit(mask, i)) S += A[i+1].value;
    return S;
}
void buildGraph()
{
    forn(i, 1, sz1) forn(j, i+1, sz1) if (!A[i].overlaps(A[j])) edge[0][i][j] = edge[0][j][i] = true;
    forn(i, 1, sz2) forn(j, i+1, sz2) if (!B[i].overlaps(B[j])) edge[1][i][j] = edge[1][j][i] = true;
    forn(i, 1, sz1) forn(j, 1, sz2) if (!A[i].overlaps(B[j])) edge[2][i][j] = true;
}
void backtrack(int i, int choosen, int tot, int limit, vector<int> &s) {
    if (i == sz2) {
        if (choosen != limit) return;
        int mask = 0;
        forn(j, 1, sz1) {
            bool ok = true;
            for(auto u: s) if (!edge[2][j][u]) ok = false;
            if (ok) mask = (mask | (1 << (j-1)));
        }
        result = max(result, tot + dp[mask]);
        return;
    }
    bool ok = true;
    for(auto u: s) if (!edge[1][i+1][u]) {
        ok = false;
        break;
    }
    if (ok && choosen < limit) {
        s.push_back(i+1);
        backtrack(i+1, choosen+1, tot + B[i+1].value, limit, s);
        s.pop_back();
    }
    backtrack(i+1, choosen, tot, limit, s);

}
void Calculate(int D) {
    repn(mask, 0, 1<<sz1) dp[mask] = -INF;
    repn(mask, 0, 1<<sz1) if (__builtin_popcount(mask) == D && isClique(mask)) dp[mask] = gSum(mask); 
        else if (__builtin_popcount(mask) > D) {
            forn(i, 0, sz1-1) if (gBit(mask, i)) dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
        }
    if (D == K) result = max(result, dp[(1<<sz1) -1]);
    vector<int> s;
    backtrack(0, 0, 0, K-D, s);
}
int main() {
    ios::sync_with_stdio(0);
    cin >> N >> K;
    nNode = 0; Sum = 0;
    forn(i, 1, N) forn(j, 1, N) {
        cin >> Num[i][j];
        Sum += Num[i][j];
        forn(ord, 0, 1) {
            int x = i + dx[ord], y = j + dy[ord];
            nNode ++;
            domino[nNode] = {i, j, x, y, nNode, Num[i][j] + Num[x][y]};
        }
    }
    sort(domino+1, domino +nNode+1);
    reverse(domino+1, domino +nNode+1);
    nNode = min(nNode, 7 * (K-1) + 1);
    sz1 = min(20, nNode);
    sz2 = nNode - sz1;
    forn(i, 1, sz1) A[i] = domino[i];
    forn(i, sz1+1, nNode) B[i-sz1] = domino[i];
    buildGraph();
    forn(D, 0, K) Calculate(D);
    cout << Sum - result;
    return 0;
}
