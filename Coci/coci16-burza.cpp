/*  
    Author: Le Trong Dat
    Idea: 
        Hint: k * k >= n, Daniel always wins.
        Solution: http://hsin.hr/coci/archive/2016_2017/
                contest 2.
*/
#include <bits/stdc++.h>
using namespace std;
#define pb                  push_back
#define repn(i, a, b)       for(int i=a; i<b; ++i)
const int N = 410;
const int inf = 1e8+1;
int n, k;
int cnt;
int depth[N];
int st[N], fi[N], f[N][N];
int dp[1 << 20];
vector<int> e[N];
void maximize(int &a, int b) { a = max(a, b); }
void go(int u, int prv = 0) {
    if (depth[u] == k) st[u] = fi[u] = ++cnt;
        else { st[u] = inf; fi[u] = -inf; }
    for(auto v: e[u]) if (depth[u] < k) {
        if (v == prv) continue;
        depth[v] = depth[u] + 1;
        go(v, u);
        st[u] = min(st[u], st[v]);
        fi[u] = max(fi[u], fi[v]);
    }
    if (st[u] != inf) maximize(f[st[u]][depth[u]], fi[u]);
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n >> k;
    if (n <= k * k) { cout << "DA"; return 0; }
    repn(i, 1, n) {
        int u, v; 
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    go(1);
    if (st[1] == inf) { cout << "DA"; return 0; }
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    repn(mask, 0, (1 << k)) if (dp[mask] != -1 && dp[mask] < fi[1]) 
        repn(bit, 0, k) if (!(mask >> bit & 1)) {
            int new_mask = mask | (1 << bit);
            maximize(dp[new_mask], f[dp[mask]+1][bit+1]);
        }
    repn(mask, 0, (1 << k)) if (dp[mask] == fi[1]) {
        cout << "DA";
        return 0;
    }
    cout << "NE";
}