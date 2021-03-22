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
vector<int> res;
auto solve() {
    int n, m; cin >> n >> m;
    vector< vector<int> > days(m + 1, vector<int>());
    res.resize(m, 0);
    repn(i, 0, m) {
        int k; cin >> k;
        repn(j, 0, k) {
            int fr; cin >> fr;
            days[i].eb(fr);
        }
    }

    vector<int> cnt(n + 1, 0);
    repn(i, 0, m) if (days[i].size() == 1) {
        cnt[*days[i].begin()] ++;

        res[i] = *days[i].begin();

        if (cnt[*days[i].begin()] > (m + 1) / 2) return "NO";
    }

    repn(i, 0, m) if (days[i].size() > 1) {
        for(auto fr: days[i]) if (cnt[fr] < (m + 1) / 2) {
            cnt[fr] ++;
            res[i] = fr;
            break;
        }
    }
    return "YES";
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
        if (ans == "YES") {
            for(auto fr: res) cout << fr << ' ';
            cout << '\n';
        }
    }
    return 0;
}
