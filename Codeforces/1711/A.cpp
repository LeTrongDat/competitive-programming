#include <bits/stdc++.h>

using namespace std;

int ntest, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> ntest;
    for(int i = 0; i < ntest; ++i) {
        cin >> n;
        vector<int> ans;
        for(int i = 1; i <= n; ++i) {
            ans.emplace_back(i);
        }
        for(int i = 0; i < n - (n % 2); i += 2) {
            swap(ans[i], ans[i+1]);
        }
        if (n & 1) swap(ans[n-1], ans[0]);
        for(auto p: ans) cout << p << ' ';
        cout << '\n';
    }
    return 0;
}