#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define all(a) a.begin(), a.end()

void solve() {
    int n, m; cin >> n >> m;
    vector< tuple<int, int, int> > points;
    for(int i = 0; i < m; ++i) {
        int x, w; cin >> x >> w;
        points.emplace_back(w, x, i + 1);
    }
    sort(all(points));
    vector<pair<int, int>> coors;
    int ans = 0;
    for(int i = 0; i < 2 * n; ++i) {
        coors.emplace_back(get<1>(points[i]), get<2>(points[i]));
        // cerr << coors[i].first << ' ' << coors[i].second << '\n';
        ans += get<0>(points[i]);
    }
    
    sort(all(coors));

    cout << ans << '\n';
    for(int i = 0; i < n; ++i) 
        cout << coors[i].second << ' ' << coors[2 * n - i - 1].second << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
    return 0;
}