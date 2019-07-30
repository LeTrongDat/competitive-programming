/*
    Author: Le Trong Dat
    Idea: 
        Hint: C(k, n) is the number of ways to go from coordinates (0, 0) 
        to coordinates (k, n-k).
    In details: http://agc001.contest.atcoder.jp/data/agc/001/editorial.pdf
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
#define repn(i, a, b)       for(int i=a; i <b; ++i)
typedef long long llong;
const int N = 4010;
const int M = 2e5 +10;
const int maxN = 2000;
const int MOD = 1e9+7;
llong gt[2*N], in[2*N];
int n, mxa, mxb, a[M], b[M];
int ans, dp[N][N];
void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}
int pw(int x, int q) {
    if (!q) return 1;
    llong tmp = pw(x, q>>1);
    tmp = tmp * tmp % MOD;
    if (q & 1) tmp = (tmp * x) % MOD;
    return tmp;
}
int C(int k, int n) {
    return gt[n] * in[k] % MOD * in[n-k] % MOD;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    gt[0] = in[0] = 1;
    repn(i, 1, 2*N) {
        gt[i] = gt[i-1] * i % MOD;
        in[i] = in[i-1] * pw(i, MOD-2) % MOD;
    }
    int mxa = 0, mxb = 0;
    forn(i, 1, n) {
        cin >> a[i] >> b[i];
        dp[-a[i]+maxN][-b[i]+maxN] += 1;
        mxa = max(mxa, a[i]+maxN);
        mxb = max(mxb, b[i]+maxN);
    }
    forn(i, 0, mxa) forn(j, 0, mxb) {
        add(dp[i+1][j], dp[i][j]);
        add(dp[i][j+1], dp[i][j]);
    }
    forn(i, 1, n) add(ans, dp[a[i]+maxN][b[i]+maxN]);
    forn(i, 1, n) ans = (ans - C(2*a[i], 2*a[i] + 2*b[i])) % MOD;
    ans = (llong) ans * in[2] % MOD;
    cout << (ans + MOD) % MOD;
}
