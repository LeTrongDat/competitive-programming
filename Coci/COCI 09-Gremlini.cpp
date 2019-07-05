/*
        Author: Le Trong Dat.
        Idea: 
         dp[lg][u][v] = Minimum time to produce 2^lg ancestrals, ending by type i-th 
         and start by type j-th.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
typedef long long llong;
const int maxN = 101;
const int maxK = 1010;
const int maxLg = 51;
const llong INF = 1e15 +10;
llong N, T;
llong cur[maxN], nxt[maxN];
llong dp[maxLg][maxN][maxN];
llong Type[maxK], Time[maxK];
void minimize(llong &a, llong b)
{
    a = min(a, b);
}
int main()
{
    ios::sync_with_stdio(0);
    cin >> N >> T;
    repn(lg, 0, maxLg) repn(i, 0, maxN) repn(j, 0, maxN) dp[lg][i][j] = INF;
    forn(row, 1, N)
    {
        int K, Y;
        cin >> K >> Y;
        forn(i, 1, K) cin >> Type[i];
        forn(i, 1, K) 
        {
            cin >> Time[i];
            minimize(dp[0][row][Type[i]], Y + Time[i]);
        }
    }
    repn(lg, 1, maxLg)
    {
        forn(i, 1, N) forn(j, 1, N)
        {
            forn(k, 1, N) minimize(dp[lg][i][j], dp[lg-1][i][k] + dp[lg-1][k][j]);
        }
        \
    }
    llong result = 0, cnt = 0;
    for(int bit = 50; bit >= 0; --bit)
    {
        forn(i, 1, N) nxt[i] = INF;
        bool ok = false;
        forn(i, 1, N)
        {
            forn(j, 1, N) if (cur[i] + dp[bit][i][j] <= T)
            {
                ok = true;
                minimize(nxt[j], cur[i] + dp[bit][i][j]);
            }
        }
        if (ok) result += (1LL<<bit);
        forn(i, 1, N) cur[i] = (ok ? nxt[i] : cur[i]);
    }
    cout << result;
}
