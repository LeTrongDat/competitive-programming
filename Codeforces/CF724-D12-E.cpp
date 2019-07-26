/*
    Author: Le Trong Dat.
    Idea:
    In shortly: 
        * Notice: if you build n^2 edges, the problem will become a max-flow problem.
        * Min-cut = max-flow => We will solve min-cut problem by using dp.
    In details:
        http://codeforces.com/blog/entry/47644. 
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define ford(i, a, b)           for(int i=a; i>=b; --i)
const int N = 10010;
long long n, k;
long long p[N], s[N];
long long ans, dp[N], f[N];
int main() {
    ios::sync_with_stdio(0);
    cin >> n >> k;
    forn(i, 1, n) cin >> p[i];
    forn(i, 1, n) cin >> s[i];
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    forn(i, 1, n) {
        forn(j, 0, n) f[j] = dp[j];
        memset(dp, 0x3f, sizeof dp);
        ford(j, i-1, 0) {
            dp[j+1] = min(dp[j+1], f[j] + s[i]);
            dp[j] = min(dp[j], f[j] + p[i] + k * j);
        }
    }
    ans = 0x3f3f3f3f3f3f3f3f;
    forn(i, 0, n) ans = min(ans, dp[i]);
    cout << ans;
}
