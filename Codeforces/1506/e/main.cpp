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
    vector<int> p_min(n + 1), p_max(n + 1), mark(n + 1);
    repn(i, 0, n) {
        int q; cin >> q;
        if (!mark[q]) {
            p_min[i+1] = p_max[i+1] = q;
            mark[q] = i + 1;
        } 
    }
    for(int i = 1, pos = 1; i <= n; ++i) if (!mark[i]) {
        while (p_min[pos]) pos++;
        p_min[pos] = i;
    }


    set<int> remainings;
    for(int i = 1; i <= n; ++i) if (!mark[i])
        remainings.emplace(i);
    int pos_prv = 0;
    for(int i = 1; i <= n; ++i) if (mark[p_max[i]]) {
        forn(j, pos_prv + 1, i - 1) {
            auto it = prev(remainings.lower_bound(p_max[pos_prv]));
            p_max[j] = *it;
            remainings.erase(it);
        }
        pos_prv = i;
    }
    forn(i, pos_prv + 1, n) {
        p_max[i] = *prev(remainings.end());
        remainings.erase(prev(remainings.end()));
    }
    p_min.erase(p_min.begin());
    p_max.erase(p_max.begin());
    return make_tuple(p_min, p_max);
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
        for(auto x: get<0>(ans)) cout << x << ' ';
        cout << '\n';
        for(auto x: get<1>(ans)) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
