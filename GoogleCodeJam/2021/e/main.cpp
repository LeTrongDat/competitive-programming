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
const int N = 1e4 + 10;
int p;
int n = 100;
int n_ques = 10000;
string s[N];
auto solve() {
    repn(i, 0, n) {
        cin >> s[i]; 
    }
    vector<int> right(n);
    int mx = 0;
    repn(i, 0, n) {
        for(auto c: s[i]) right[i] += (c == '1');
        if (right[i] > right[mx]) mx = i;
    }
    return mx + 1;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest; cin >> ntest >> p;
    forn(i, 1, ntest) {
        auto ans = solve();
        cout << "Case #" << i << ": ";
        cout << ans << '\n';
    }
    return 0;
}
