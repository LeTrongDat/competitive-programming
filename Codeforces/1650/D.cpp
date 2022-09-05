#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define all(a) a.begin(), a.end()

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) 
        cin >> a[i];
    vector<int> res;
    for(int i = n; i >= 1; --i) {
        int nxt_pos = i - 1;
        for(int j = 0; j < n; ++j) if (a[j] == i) {
            int num = 0;
            while (a[nxt_pos] != nxt_pos + 1) {
                rotate(a.begin(), a.begin() + 1, a.begin() + i);
                num++;
            }
            res.emplace_back(num);
            break;
        }
    }
    for(int i = 0; i < n; ++i)
        if (a[i] != i + 1) {
            cout << -1 << '\n';
            return;
        }
    reverse(all(res));
    for(auto num: res) cout << num << ' ';
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
    return 0;
}