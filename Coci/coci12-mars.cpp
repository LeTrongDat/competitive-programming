/*
    Author: Le Trong Dat
    Idea: http://hsin.hr/coci/archive/2012_2013/ 
    Contest 1.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)          for(int i=a; i<=b; ++i) 
typedef long long llong;
const llong INF = 0x3f3f3f3f3f3f3f3f;
const int maxN = 513;
const int maxK = 10;
int N, K;
int pw[maxK];
llong dp[maxN][maxN], Len[maxN][maxN];
void minimize(llong &a, llong b) {
    a = min(a, b);
}
int inside(int p1, int p2, int lg) {
    if (p1 > p2) swap(p1, p2);
    int x = (p2+pw[lg]-1) / pw[lg];
    if (pw[lg]*(x-1) +1 <= p1) return x;
    return 0;
}
int main() {
   ios::sync_with_stdio(0);
   cin >> K;
   pw[0] = 1;
   forn(i, 1, K) pw[i] = pw[i-1] * 2;
   N = (1 << K);
   forn(i, 1, N) forn(j, 1, N) cin >> Len[i][j];
    memset(dp, 0x3f, sizeof dp);
   forn(i, 1, N) dp[1][i] = 0;
    forn(i, 1, N) forn(j, 1, N) if (dp[i][j] != INF) {
       int x;
       forn(lg, 1, K) if (inside(i, i+1, lg)) {
            x = inside(j, j, lg);
            forn(k, pw[lg]*(x-1)+1, pw[lg]*x) if (k!=j && !inside(j, k, lg-1)) 
                minimize(dp[i+1][k], dp[i][j] + Len[j][k]);
           break;
       }
    }
    llong result = INF;
    forn(i, 1, N) minimize(result, dp[N][i]);
    cout << result;
}
