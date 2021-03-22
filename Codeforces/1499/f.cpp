#include <bits/stdc++.h>
using namespace std;
#define eb                  emplace_back
#define llong               long long 
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define ford(i, a, b)       for(int i = a; i >= b; --i)
#define repn(i, a, b)       for(int i = a; i <  b; ++i)
 
#ifndef LOCAL 
#define cerr                if (0) cerr 
#endif 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 998244353;
const int N = 5010;
int n, k;
vector<int> adj[N];
llong high[N], dp[N][N];
void dfs(int u, int par) {
    dp[u][0] = 1;
    for(auto v: adj[u]) if (v != par) {
        dfs(v, u);
        vector<llong> tmp(max(high[v] + 1, high[u]) + 1, 0);
        ford(lenu, high[u], 0) ford(lenv, high[v], 0) 
            if (lenu + lenv + 1 <= k) 
                tmp[max(lenv+1, lenu)] = (tmp[max(lenv+1, lenu)] + 
                                dp[u][lenu] * dp[v][lenv]) % MOD;
        
        int tot = 0;
        forn(lenv, 0, high[v]) tot = (tot + dp[v][lenv]) % MOD;
        forn(lenu, 0, max(high[v] + 1, high[u])) dp[u][lenu] = (dp[u][lenu] * tot + tmp[lenu]) % MOD;
        high[u] = max(high[u], high[v] + 1);
    }
}
auto solve() {
    cin >> n >> k;
    repn(i, 1, n) {
        int u, v; cin >> u >> v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    dfs(1, -1);
    int ans = 0;
    forn(i, 0, k) ans = (ans + dp[1][i]) % MOD;
    return ans;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest = 1;
    for(; ntest --;) {
        auto ans = solve();
        cout << ans << '\n';
    }
    return 0;
}