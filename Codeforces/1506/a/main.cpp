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
    llong n, m, x;
    cin >> n >> m >> x;
    llong u, v;
    u = (not (x % n) ? n : x % n);  
    v = (not (x % n) ? x / n : x / n + 1);
    return (u - 1) * m + v;
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
