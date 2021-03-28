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
    int x, y; cin >> x >> y;
    string s; cin >> s;
    int n = s.length(), cnt_ques = 0;
    // repn(i, 0, n) cnt_ques += s[i] == '?';
    // if (cnt_ques == n) return 0LL;
    auto cost = [x, y](int a, int b) {
        if (a == b) return 0;
        return (a == 0 ? x : y);
    };
    vector< vector<int> > dp(n + 1, vector<int>(2, INT_MAX / 2)); 
    repn(i, 0, n) {
        if (s[i] == 'C') s[i] = '0';
        if (s[i] == 'J') s[i] = '1';
    }
    
    if (s[0] != '?') dp[0][s[0] - '0'] = 0;
    else dp[0][0] = dp[0][1] = 0;

    repn(i, 1, n) repn(prv, 0, 2) if (dp[i-1][prv] != INT_MAX / 2) {
        if (s[i] != '?') {
            dp[i][s[i] - '0'] = min(dp[i][s[i] - '0'], dp[i-1][prv] + cost(prv, s[i] - '0'));
            continue;
        }
        dp[i][0] = min(dp[i][0], dp[i-1][prv] + cost(prv, 0));
        dp[i][1] = min(dp[i][1], dp[i-1][prv] + cost(prv, 1));
    }
    return min(dp[n-1][0], dp[n-1][1]);

    // llong ans = 0;
    // repn(i, 1, n) {
    //     if (s[i-1] == '?') continue;
    //     if (s[i] != '?') {
    //         ans += cost(s[i-1], s[i]);
    //         continue;
    //     }
    //     s[i] = s[i-1];
    // }
    // return ans;
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
