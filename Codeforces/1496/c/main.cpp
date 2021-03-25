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
auto solve() {
    int n; cin >> n;
    vector<double> miners;
    vector<double> mines;
    repn(i, 0, 2 * n) {
        int x, y; cin >> x >> y;
        if (not x) miners.eb(fabs(y));
        else mines.eb(fabs(x));
    }

    sort(miners.begin(), miners.end());
    sort(mines.begin(), mines.end());
    double ans = 0;
    repn(i, 0, n) ans += sqrt(miners[i] * miners[i] + mines[i] * mines[i]);
    return ans;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest; cin >> ntest;
    for(; ntest --;) {
        auto ans = solve();
        cout << fixed << setprecision(18) << ans << '\n';
    }
    return 0;
}
