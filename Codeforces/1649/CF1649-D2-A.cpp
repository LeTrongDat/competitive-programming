#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define all(a) a.begin(), a.end()

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);

    int max_val = 0;
    ll total = 0;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        total += a[i];
        max_val = max(max_val, a[i]);
    }

    if (!max_val) {
        cout << 0 << '\n';
        return;
    }
    cout << (2 * max_val <= total ? 1 : 2 * max_val - total) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}