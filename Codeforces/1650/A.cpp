#include <bits/stdc++.h>

using namespace std;

void solve() {
    string s; cin >> s;
    char c; cin >> c;
    for(int i = 0; i < s.size(); ++i) if (s[i] == c) {
        if (!(i % 2) && !((s.size() - i - 1) % 2)) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
    return 0;
}