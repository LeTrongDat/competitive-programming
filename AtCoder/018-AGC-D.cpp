/*
    Author: Le Trong Dat
    Idea: https://img.atcoder.jp/agc018/editorial.pdf.
*/
#include <bits/stdc++.h>
using namespace std;
#define pb                          push_back
#define repn(i, a, b)               for(int i=a; i< b; ++i)
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
typedef long long ll;
const int N = 1e5 +10;
ll ans = 0;
int n;
ll child[N];
vector<pair<ll, ll>> e[N];
struct Edge {
    ll u, v, c;
    Edge(){};
    Edge(ll u, ll v, ll c): u(u), v(v), c(c) {};
} edge[N];
void dfs1(int u, int p = 0) {
    child[u] = 1;
    for(auto x: e[u]) if (x.first != p) {
        dfs1(x.first, u);
        child[u] += child[x.first];
    }
}
void dfs2(int u, int p = 0, int w = 0) {
    for(auto v: e[u]) if (v.first != p && child[v.first] > n/2)
        dfs2(v.first, u, v.second);
    for(auto v: e[u]) if (v.first != p && child[v.first] == n/2 && n%2 == 0) {
        cout << ans - v.second;
        exit(0);
    }
    bool ok = child[u] >= n/2;
    for(auto v: e[u]) if (v.first != p) ok &= !(child[v.first] > n/2);
    ll  mn = w;
    if (ok) {
        for(auto v: e[u]) mn = min(mn, v.second);
        cout << ans - mn;
        exit(0);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    repn(i, 1, n) {
        int u, v, c;
        cin >> u >> v >> c;
        edge[i] = {u, v, c};
        e[u].pb({v, c});
        e[v].pb({u, c});
    }
    dfs1(1);
    repn(i, 1, n) if (child[edge[i].u] > child[edge[i].v]) swap(edge[i].u, edge[i].v);
    repn(i, 1, n) ans += 2*edge[i].c*min(child[edge[i].u], n-child[edge[i].u]);
    dfs2(1);
    cout << ans;
}
