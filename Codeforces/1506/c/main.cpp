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
    string a, b; cin >> a >> b;
    int n = a.size(); 
    int m = b.size();
    int ans = n + m;

    repn(i1, 0, n) {
        string s1 = "";
        repn(i2, i1, n) {
           s1 += a[i2];
           repn(j1, 0, m) {
               string s2 = "";
               repn(j2, j1, m) {
                   s2 += b[j2];
                   if (s1 == s2) ans = min(ans, (int)(n + m - s1.size() - s2.size()));
               }
           }
        }
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
