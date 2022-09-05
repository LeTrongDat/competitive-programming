#include <bits/stdc++.h>

using namespace std;

int ntest; // number of test cases
const int N = 1e5 + 10;
const int M = 1e5 + 10;
int n, m;
int a[N];
int deg[N];


void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        deg[i] = 0;
    }
    for(int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        ++deg[x];
        ++deg[y];
    }
    bool is_odd = m & 1;
    if (!is_odd) {
        cout << 0 << '\n';
        return;
    }
    int ans = 1e4 + 1;
    for(int i = 1; i <= n; ++i) {
        if (deg[i] & 1) {
            ans = min(ans, a[i]);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin >> ntest;
    while (ntest--) {
        solve();
    }
    return 0;
}