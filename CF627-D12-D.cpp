/*
        Author: Le Trong Dat
        Idea: Binary search by answer.
        Fixed the minimum value of k nodes. Call it D.
        Then we will consider there is a way to traverse through k nodes satisfied each node has value a >= D.
        => We can use Dp.
        Dp(u) = {The maximum number of nodes >= D in subtree u we can traverse in subtree u, can we go back u or not ? }
        Out(u) = {The maximum number of nodes >= D outside subtree u we can traverse, can we go back u or not ? };
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define ford(i, a, b)           for(int i=a; i>=b; --i)
#define repn(i, a, b)           for(int i=a; i <b; ++i)
#define ii pair<int, int>
const int N = 2e5 +10;
int n, k;
int a[N];
bool flag[N];
ii dp[N], out[N];
int mx1[N], mx2[N];
vector<int> e[N]; 
void dfs1(int u, int par = 0) {
    for(auto v: e[u]) if (v != par) dfs1(v, u); 
    if (!flag[u]) { dp[u] = {0, 1}; return; }
    dp[u] = {1, 0};
    mx1[u] = mx2[u] = -1;
    for(auto v: e[u]) if (v != par) {
        if (dp[v].second) {
            if (mx1[u] < dp[v].first) {
                mx2[u] = mx1[u];
                mx1[u] = dp[v].first;
            } else mx2[u] = max(mx2[u], dp[v].first);
        } else dp[u].first += dp[v].first;
    }
    if (mx1[u] != -1) { dp[u].second = 1; dp[u].first += mx1[u]; }
}
void dfs2(int u, int p = 0) {
    if (p == 0) out[u] = {0, 0};
    else {
        if (!flag[p]) out[u] = {0, 1}; else {
            out[u].second = 0;
            int inP = 0, mx = -1;
            if (dp[u].second == 0) {
                inP = dp[p].first - dp[u].first - (mx1[p]==-1?0:mx1[p]);
                if (out[p].second == 0) inP += out[p].first;
                    else mx = max(mx, out[p].first);
                mx = max(mx, mx1[p]);
                out[u].first = inP;
                if (mx != 0) { out[u].second = 1; out[u].first += mx; }
            } else {
                inP = dp[p].first - (mx1[p]==-1?0:mx1[p]);
                if (out[p].second == 0) inP += out[p].first; 
                    else mx = max(mx, out[p].first);
                if (dp[u].first == mx1[p]) mx = max(mx, mx2[p]); 
                    else mx = max(mx, mx1[p]);
                out[u].first = inP;
                if (mx != -1) { out[u].second = 1; out[u].first += mx; }
            }
        }
    }
    for(auto v: e[u]) if (v != p) dfs2(v, u);
}
bool ok(int m) {
    memset(flag, 0, sizeof flag);
    int result = 0;
    forn(i, 1, n) if (a[i] >= m) flag[i] = true;
    dfs1(1);
    dfs2(1);
    forn(i, 1, n) if (flag[i]) {
        int mx = -1, inP = dp[i].first - (mx1[i] == -1 ? 0 : mx1[i]);
        mx = max(mx, mx1[i]);
        if (out[i].second == 0) inP += out[i].first;
            else mx = max(mx, out[i].first);
        inP += (mx == -1 ? 0 : mx);
        result = max(result, inP);
    }
    return (result >= k);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    forn(i, 1, n) cin >> a[i];
    repn(i, 1, n) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int l = 1, r = 1e9, rz = 1;
    while (l <= r) {
        int m = l+r >> 1;
        if (ok(m)) rz = m, l = m+1;
            else r = m-1;
    }
    cout << rz;
    return 0;
}
