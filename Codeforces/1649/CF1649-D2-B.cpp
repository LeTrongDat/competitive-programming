#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define all(a) a.begin(), a.end()

void solve() {
    int n; 
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int l = 0, r = 0;
    for(int i = 0; i < n; ++i) 
        if (!a[i]) {
            l = i - 1;
            break;
        }
    
    for(int i = n - 1; i >= 0; --i)
        if (!a[i]) {
            r = i + 1;
            break;
        }
    
    cout << max(0, r - l) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}