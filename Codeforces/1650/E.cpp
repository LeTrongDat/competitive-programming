#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int d;

bool can_change(int pos, vector<int> &a, int rest_d) {
    vector<int> b;
    b.emplace(0);

    for(int i = 0; i < a.size(); ++i) 
        if (i != pos) {
            b.emplace(a[i]);
        }
    
    for(int i = 1; i < b.size(); ++i)
        if (b[i] - b[i-1] - 1 < rest_d) {
            return false;
        }
    
    for(int i = 1; i < b.size(); ++i)
        if (b[i] - b[i-1] - 1 >= rest_d * 2 + 1) {
            return true;
        }
    
    return (d - b.back() - 1 >= rest_d);
}
bool ok(int rest_d, vector<int> &a) {
    if (a[0] - 1 < rest_d) return can_change(0, a, rest_d);

    for(int i = 1; i < a.size(); ++i) 
        if (a[i] - a[i-1] - 1 < rest_d) {
            if (!can_change(i, a, rest_d) && !can_change(i-1, a, rest_d)) {
                return false;
            }
            break;
        }
    return true;
}   
void solve() {
    int n; cin >> n;
    cin >> d;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) 
        cin >> a[i];

    int low = 0, high = d, ans = -1;
    while (low <= high) {
        int mid = low + high >> 1;
        if (ok(mid, a)) {
            ans = mid;
            low = mid + 1;
        } else high = mid - 1;
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