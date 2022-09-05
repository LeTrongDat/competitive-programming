#include <bits/stdc++.h>

using namespace std;
using ll = long long;

typedef pair<int, int> ii;
const ll inf = 1e15;
#define all(a) a.begin(), a.end()

bool mark_a[2], mark_b[2];

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<ii> edge;
    edge.emplace_back(0, 0);
    edge.emplace_back(0, n - 1);
    edge.emplace_back(n - 1, 0);
    edge.emplace_back(n - 1, n - 1);

    int best_a0 = 0, best_an = 0;
    int best_b0 = 0, best_bn = 0;
    for(int i = 1; i < n; ++i) {
        if (abs(b[best_a0] - a[0]) > abs(a[0] - b[i])) 
            best_a0 = i;
        if (abs(b[best_an] - a[n-1]) > abs(a[n-1] - b[i]))
            best_an = i;
        if (abs(a[best_b0] - b[0]) > abs(a[i] - b[0]))
            best_b0 = i;
        if (abs(a[best_bn] - b[n-1]) > abs(a[i] - b[n-1]))
            best_bn = i;
    }
    edge.emplace_back(0, best_a0);
    edge.emplace_back(n - 1, best_an);
    edge.emplace_back(best_b0, 0);
    edge.emplace_back(best_bn, n - 1);

    sort(all(edge));
    edge.resize(unique(all(edge)) - edge.begin());

    int m = edge.size();
    ll ans = inf;
    for(int mask = 1; mask < (1 << m); ++mask) {
        ll sum = 0;
        for(int bit = 0; bit < m; ++bit) {
            if (!(mask >> bit & 1))
                continue;
            int i, j;
            i = edge[bit].first;
            j = edge[bit].second;
            sum += abs(a[i] - b[j]);
            if (!i) mark_a[0] = true;
            if (i == n - 1) mark_a[1] = true;
            if (!j) mark_b[0] = true;
            if (j == n - 1) mark_b[1] = true;
        }
        if (mark_a[0] && mark_a[1] && mark_b[0] && mark_b[1])
            ans = min(ans, sum);
        mark_a[0] = mark_a[1] = mark_b[0] = mark_b[1] = 0;
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}