#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define all(a) a.begin(), a.end()

const int N = 1e6 + 10;
int cnt[N];

void solve() {
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
    for(auto ai: a) ++cnt[ai];

    for(int i = 1; i <= c; ++i) {
        cnt[i] = cnt[i-1] + cnt[i];
    }

    bool is_integral = true;
    for(auto y: a) {
        for(int r = 1; r <= c / y; ++r) {
            if (cnt[r] - cnt[r-1]) continue;
            int low = y * r, high = min(c+1, y * (r + 1));
            if (cnt[high-1] - cnt[low-1]) {
                is_integral = false;
                break;
            }
        }   
        if (!is_integral) break;
    }
    cout << (is_integral ? "Yes" : "No") << '\n';
    fill(cnt, cnt + c + 1, 0);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}