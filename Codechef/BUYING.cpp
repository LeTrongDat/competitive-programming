/*
        Author: Le Trong Dat.
        Idea: Take m smallest numbers. Now we will replace each number in this set by
            each number which is not in there. 
            Call the number needed to replace is W.
            => W <= 2*k-2 => We can Dp.
            Prove of this:
                - https://discuss.codechef.com/t/buying-editorial/957.
                - https://bit.ly/2xkC0Pg
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
#define ford(i, a, b)       for(int i=a; i>=b; --i)
#define repn(i, a, b)       for(int i=a; i <b; ++i)
#define repd(i, a, b)       for(int i=(int)a-1; i>=b; --i)
typedef long long llong;
const int N = 100;
const int sizeN = 5e4 +100;
llong INF = 0x3f3f3f3f3f3f3f3f;
llong f[N][N][N], g[N][N][N];
vector<int> mod[N];
llong a[sizeN];
llong rez, n, m, k;
template<class T, class U> 
T min(T a, U b) { return a>b?b:a; }
void maximize(llong &A, llong B) { A = max(A, B); }
void minimize(llong &A, llong B) { A = min(A, B); }
template<size_t T>
void dynamic(llong (&dp)[T][T][T], int id)
{
    llong inf;
    if (id) {
        inf = -1;
        memset(dp, -1, sizeof dp);
        dp[0][0][0] = 0;
    } else {
        inf = INF;
        memset(dp, 0x3f, sizeof dp);
        dp[0][0][0] = 0;
    }

    repn(i, 0, k) forn(remove, 0, min(2*k-2, m)) repn(modul, 0, k) if (dp[i][remove][modul] != inf)
    {
        if (id) maximize(dp[i+1][remove][modul], dp[i][remove][modul]); 
            else minimize(dp[i+1][remove][modul], dp[i][remove][modul]);
        llong add = 0;
        forn(j, 1, min(min(2*k-2, m) -remove, mod[i].size()))
        {
            add += mod[i][j-1];
            llong newMod = (modul + j * i) % k;
            if (id) maximize(dp[i+1][remove+j][newMod], dp[i][remove][modul] + add);
                else minimize(dp[i+1][remove+j][newMod], dp[i][remove][modul] + add);
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE 
    freopen("buying.inp", "r", stdin);
#endif //ONLINE_JUDGE
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int Test; 
    cin >> Test;
    for(; Test; Test --)
    {
        rez = INF;
        llong current = 0;
        cin >> n >> m >> k;
        forn(i, 0, k) mod[i].clear();
        forn(i, 1, n) cin >> a[i];
        sort(a +1, a +n+1);
        forn(i, 1, m) 
        {
            mod[a[i] % k].push_back(a[i]);
            current += a[i];
        }
        repn(i, 0, k) reverse(mod[i].begin(), mod[i].end());
        dynamic<N>(f, 1);
        repn(i, 0, k) mod[i].clear();
        forn(i, m+1, n) mod[a[i] % k].push_back(a[i]);
        dynamic<N>(g, 0);
        forn(remove, 0, min(m, 2*k-2)) repn(modul, 0, k) 
        {
            llong x = (modul - current % k + k) % k;
            if (f[k][remove][modul] != -1 && g[k][remove][x] != INF) 
                minimize(rez, current-f[k][remove][modul]+g[k][remove][x]);
        }
        cout << (rez == INF ? -1 : rez) << '\n';
    }
    return 0;
}
