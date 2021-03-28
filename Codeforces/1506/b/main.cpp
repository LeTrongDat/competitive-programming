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
    int n, k; cin >> n >> k;
    string s; cin >> s;
    int ft, ls;
    repn(i, 0, n) if (s[i] == '*') { ft = i; break; }
    int ans = 1;
    while (true) {
        bool ap = false;
        int tmp;
        repn(i, ft + 1, n) if (s[i] == '*') {
            if (i - ft <= k) {
                ap = true;
                tmp = i;
            } else break;
        }
        if (not ap) break; else { ans ++; ft = tmp; }
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
