#include <bits/stdc++.h>
using namespace std;
#define eb                  emplace_back
#define llong               long long 
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define repn(i, a, b)       for(int i = a; i <  b; ++i)
 
#ifndef LOCAL 
#define cerr                if (0) cerr 
#endif 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 998244353;
void add(int &a, int &b) {
    a = (a + b) % MOD;
}
auto solve() {
    string x, y; cin >> x >> y;
    int n = x.length();
    int m = y.length();
    x = " " + x; y = " " + y;
    const int N = max(n, m) + 2;
    int dp[N][N][2][2][2];
    repn(i, 0, N) repn(j, 0, N) forn(end, 0, 1) forn(was_x, 0, 1) forn(was_y, 0, 1)
        dp[i][j][end][was_x][was_y] = 0;

    forn(i, 0, n) forn(j, 0, m) forn(end, 0, 1) forn(was_x, 0, 1) forn(was_y, 0, 1) {
        char c = (not end ? x[i] : y[j]);
        if (i < n and x[i+1] != c) 
            add(dp[i+1][j][0][1][was_y], dp[i][j][end][was_x][was_y]);
        
        if (j < m and y[j+1] != c)
            add(dp[i][j+1][1][was_x][1], dp[i][j][end][was_x][was_y]);
        if (i < n and x[i+1] != x[i]) dp[i+1][j][0][1][0] = dp[i][j][0][1][0] + 1;
            else dp[i+1][j][0][1][0] = 1;
        if (j < m and y[j+1] != y[j]) dp[i][j+1][1][0][1] = dp[i][j][1][0][1] + 1;
            else dp[i][j+1][1][0][1] = 1;
    }
    int ans = 0;
    forn(i, 1, n) forn(j, 1, m) forn(end, 0, 1) {
        add(ans, dp[i][j][end][1][1]);
    }
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
