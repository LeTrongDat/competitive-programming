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
    vector<int> r(n), c(n);
    repn(i, 0, n) cin >> r[i];
    repn(i, 0, n) cin >> c[i];

    vector<tuple<int, int>> vertices;

    repn(i, 0, n) vertices.eb(r[i], c[i]);

    sort(vertices.begin(), vertices.end());

    int cur_r = 1, cur_c = 1;
    llong ans = 0;
    for(auto [nxt_r, nxt_c]: vertices) {
        if (nxt_r == 1 and nxt_c == 1) continue;
        int odd = nxt_r - cur_r;
        odd -= not ((cur_r + cur_c) % 2);
        int even = nxt_r - cur_r - odd;

        if (cur_c + odd >= )

        cur_r = nxt_r; cur_c = nxt_c;
    }
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
        cout << ans << '\n';
    }
    return 0;
}
