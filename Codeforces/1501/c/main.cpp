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
const int N = 5e6 + 10;
bool brute_force(vector<int> &indices, vector<int> &ans, vector<int> &a) {
    for(auto i1: indices) for(auto i2: indices) for(auto i3: indices) for(auto i4: indices) 
        if (i1 != i2 and i1 != i3 and i1 != i4 and i2 != i3 and i2 != i4 and i3 != i4) {
            if (a[i1] + a[i2] == a[i3] + a[i4]) {
                ans = {i1, i2, i3, i4};
                return true;
            }
        }
    return false;
}
auto solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector< vector<int> > sum(N + 1, vector<int>());

    repn(i, 0, n) cin >> a[i];

    vector<int> ans;
    repn(i, 0, n) if (ans.empty()) repn(j, i+1, n) {
        int s = a[i] + a[j];
        if (sum[s].size() >= 8) {
            brute_force(sum[s], ans, a);
            break;
        }
        sum[s].eb(i); sum[s].eb(j);
    }
    if (ans.empty()) {
        repn(i, 0, N) if (brute_force(sum[i], ans, a)) break;
    }
    return ans;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest = 1;
    for(; ntest --;) {
        auto ans = solve();
        cout << (ans.empty() ? "NO\n" : "YES\n");
        if (ans.size()) {
            for(auto indices: ans) cout << indices + 1 << ' ';
            cout << '\n';
        }
    }
    return 0;
}
