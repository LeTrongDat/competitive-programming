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
const int N = 2e7 + 2;
int prime[N];
int cal(llong g, llong c, llong d, llong x) {
    x += d * g;
    if (x % c) return 0;
    x /= c;
    if (x % g) return 0;
    x /= g;

    if (x == 1) return 1;
    return (1 << prime[x]);
}
auto solve() {
    llong c, d, x;
    cin >> c >> d >> x;
    llong ans = 0;
    forn(i, 1, sqrt(x)) if (not (x % i)) {
        ans += cal(i, c, d, x);
        if (x / i != i) ans += cal(x / i, c, d, x);
    }
    return ans;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    forn(i, 2, N - 1) if (!prime[i]) {
        prime[i] = 1;
        for(int j = 2 * i; j < N; j += i) prime[j] ++;
    }
    int ntest; cin >> ntest;
    for(; ntest --;) {
        auto ans = solve();
        cout << ans << '\n';
    }
    return 0;
}
