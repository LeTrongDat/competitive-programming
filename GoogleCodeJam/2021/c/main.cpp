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
const int N = 110;
const int C = 1010;
vector<int> s[N][C];
bool is_valid[N][C];
bool visited[N][C];
void get_permutation(int len, int cost) {
    if (visited[len][cost]) return;
    visited[len][cost] = true;
    if (len == 2) {
        switch (cost) {
            case 2: 
                is_valid[len][cost] = true;
                s[len][cost] = {2, 1};
                return;
            case 1:
                is_valid[len][cost] = true;
                s[len][cost] = {1, 2};
                return;
        }
        is_valid[len][cost] = false;
        return;
    }
    if (len - 1 > cost) {
        is_valid[len][cost] = false;
        return;
    }

    if (cost == len - 1) {
        is_valid[len][cost] = true;
        forn(i, 1, len) s[len][cost].eb(i);
        return;
    }

    forn(i, 1, len) {
        if (!visited[len-1][cost-i]) get_permutation(len - 1, cost - i);
        if (is_valid[len-1][cost-i]) {
            is_valid[len][cost] = true;
            s[len][cost].resize(1, 1);
            for(auto x: s[len-1][cost-i]) s[len][cost].eb(x + 1);
            reverse(s[len][cost].begin(), s[len][cost].begin() + i);
            break;
        }
    }
    return;
}
auto solve() {
    int n, c; cin >> n >> c;
    get_permutation(n, c);
    return make_tuple(is_valid[n][c], s[n][c]);
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest; cin >> ntest;
    forn(i, 1, ntest) {
        vector<int> ans;
        bool is_valid;
        cout << "Case #" << i << ": ";
        tie(is_valid, ans) = solve();
        if (not is_valid) cout << "IMPOSSIBLE\n";
        else {
            for(auto x: ans) cout << x << ' ';
            cout << '\n';
        }

        
    }
    return 0;
}
