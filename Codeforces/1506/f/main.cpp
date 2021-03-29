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
int cost(int r1, int c1, int r2, int c2) {
    function<bool(int, int)> is_odd = [](int r1, int c1) { return (r1 + c1) % 2; };
    function<bool(int, int)> is_even = [is_odd](int r1, int c1) { return not is_odd(r1, c1); };
    if (r1 - c1 == r2 - c2) return (is_odd(r1, c1) ? 0 : abs(r1 - r2));
    r1++;
    if (is_odd(r1-1, c1)) c1++;

    int r3 = r1 - c1 + c2;
    int c3 = c2;

    return cost(r1, c1, r3, c3) + (is_even(r3, c3) ? (r2-r3)/2 : (r2-r3+1)/2);
}
auto solve() {
    int n; cin >> n;
    vector<int> r(n), c(n);
    repn(i, 0, n) cin >> r[i];
    repn(i, 0, n) cin >> c[i];

    vector<tuple<int, int>> points;
    repn(i, 0, n) points.eb(r[i], c[i]);
    sort(points.begin(), points.end());

    int cur_r = 1, cur_c = 1;
    llong ans = 0;
    for(auto [nxt_r, nxt_c]: points) {
        if (nxt_r == 1 and nxt_c == 1) continue;
        ans += cost(cur_r, cur_c, nxt_r, nxt_c);
        cur_r = nxt_r;
        cur_c = nxt_c;
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
