#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    if (n > 19) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << 1 << ' ';
    int prev = 1;
    for(int i = 1; i < n; ++i) {
        prev *= 3;
        cout << prev << ' ';
    }
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}