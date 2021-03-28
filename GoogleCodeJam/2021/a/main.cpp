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
    vector<int> l(n);
    repn(i, 0, n) cin >> l[i];
    llong ans = 0;
    repn(i, 0, n - 1) {
        int mn = i;
        repn(j, i + 1, n) if (l[mn] > l[j]) mn = j;
        ans += mn - i + 1;
        reverse(l.begin() + i, l.begin() + mn + 1);
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
    forn(i, 1, ntest) {
        auto ans = solve();
        cout << "Case #" << i << ": " << ans << '\n';
    }
    return 0;
}
