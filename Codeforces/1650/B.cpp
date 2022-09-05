#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    ll l, r, a;
    cin >> l >> r >> a;
    if (r % a == a-1) {
        cout << r / a + r % a << '\n';
        return;
    }
    ll x = r / a * a - 1;
    if (x < l) x = r;
    cout << x / a + x % a << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
    return 0;
}