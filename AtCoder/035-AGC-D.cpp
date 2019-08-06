/*
    Author: Le Trong Dat
    Idea: https://img.atcoder.jp/agc035/editorial.pdf.
*/
#include <bits/stdc++.h>
using namespace std;
long long INF = 1e18;
int n;
long long a[20];
struct State {
    int l, xl, r, xr;
    State(){};
    State(int l, int xl, int r, int xr): l(l), xl(xl), r(r), xr(xr) {};
    bool operator < (const State& oo) const {
        if (this->l != oo.l) return this-> l < oo.l;
        if (this->xl != oo.xl) return this->xl < oo.xl;
        if (this->r != oo.r) return this->r < oo.r;
        return this->xr < oo.xr;
    }
};
map<State, long long> dp;
long long cal(int l, int xl, int r, int xr) {
    if (dp.count({l, xl, r, xr})) return dp[{l, xl, r, xr}];
    long long &ans = dp[{l, xl, r, xr}];
    ans = INF;
    if (l + 1 == r) return ans = 0;
    for(int m = l+1; m < r; ++m) ans = min(ans, a[m] * (xl + xr) + cal(l, xl, m, xl+xr) + cal(m, xl+xr, r, xr));
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for(int i=1; i<=n; ++i) cin >> a[i];
    cout << a[1] + a[n] + cal(1, 1, n, 1);
    return 0;
}
