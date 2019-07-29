/*
    Author: Le Trong Dat
    Idea: 
    dp[i] = The expected number of roads you have to walk from 
    conjunction i-th.
    dp[i] = 1 + dp[u] * p[u] ( With u being the vertex directly connected from i and p(u) 
    is the probability to go into u.)
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define ford(i, a, b)           for(int i=a; i>=b; --i)
#define repn(i, a, b)           for(int i=a; i <b; ++i)
#define pb                      push_back
#define ft                      first
#define nd                      second
typedef long double ldb;
const int N = 17;
vector< pair<int, ldb> > e[N];
ldb a[N][N], sum[N], ans[N];
int st, en, n;
int main() {
    ios::sync_with_stdio(0);
    int T; cin >> T;
    for(; T; T--) {
        cin >> n >> st >> en;
        forn(i, 1, n) e[i].clear(), sum[i] = 0;
        repn(i, 1, n) {
            int u, v, c; 
            cin >> u >> v >> c;
            sum[u] += c;
            sum[v] += c;
            e[u].pb({v, c});
            e[v].pb({u, c});
        }
        memset(a, 0, sizeof a);
        forn(i, 1, n) if (i == en) a[i][i] = 1;
            else {
                a[i][i] = a[i][n+1] = -1;
                for(auto ss: e[i]) a[i][ss.ft] = ss.nd / sum[i];
            }
        int col = 1;
        forn(i, 1, n) {
            forn(j, i, n) if (a[j][col]) {
                swap(a[i], a[j]);
                break;
            }
            if (!a[i][col]) {
                col ++;
                i --;
                if (col > n) break;
                continue;
            }
            forn(j, i+1, n) {
                forn(k, 1, n+1) if (k != col) a[j][k] -= a[i][k] * (a[j][col] / a[i][col]);
                a[j][col] = 0;
            }
            col ++;
        }
        ford(i, n, 1) {
            forn(j, i+1, n) a[i][n+1] -= ans[j] * a[i][j];
            ans[i] = a[i][n+1] / a[i][i];
        }
        cout << fixed << setprecision(5) << ans[st] << '\n';
    }
}
