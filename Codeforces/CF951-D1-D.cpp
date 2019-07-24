/*
    Author: Le Trong Dat
    Idea: 
    In shortly: 
        * Create MST with my edge list and competitor's edge list. (Firstly we add all edges in out list).
        * With edges which weren't added in MST, call u and v the two vertices of that edge and w be the cost. 
        Realizing that on the path from u-> v in MST, the cost of the edges must not exceed w
        => To optimize the result, we will assign the value of all edges on the path from u-> v = w.
    In details: https://codeforces.com/blog/entry/61356

*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)                   for(int i=a; i<=b; ++i)
#define ford(i, a, b)                   for(int i=a; i>=b; --i)
#define repn(i, a, b)                   for(int i=a; i <b; ++i)
#define repd(i, a, b)                   for(int i=(int)a-1; i>=b; --i)
#define a                               first
#define b                               second 
const int N = 5e5 +10;
const int Log = 21;
const long long INF = 1e15;
typedef pair<int, int> ii;
ii g[N], f[N];
int w[N], lab[N], d[N], nxt[N];
int n, m, k, tp, E;
bool choose[N];
int par[N][Log];
vector<int> e[N];
long long rz[N];
int root(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = root(lab[u]);
}
bool Union(int u, int v) {
    int l1 = root(u), l2 = root(v);
    if (l1 == l2) return false;
    if (lab[l1] > lab[l2]) swap(l1, l2);
    lab[l1] += lab[l2];
    lab[l2] = l1;
    return true;
}
void dfs(int u, int p = 0) {
    for(auto v: e[u]) if (v != p) {
        par[v][0] = u;
        d[v] = d[u] + 1;
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    ford(lg, 20, 0) if (d[par[u][lg]] >= d[v]) 
        u = par[u][lg];
    if (u == v) return u;
    ford(lg, 20, 0) if (par[u][lg] != par[v][lg]) {
        u = par[u][lg];
        v = par[v][lg];
    }
    return par[u][0];
}
int go(int u, int p, int w) {
    if (u != nxt[u]) return u = go(nxt[u], p, w);
    if (d[u] <= d[p]) return u;
    rz[u] = w;
    return nxt[u] = go(par[u][0], p, w);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k >> m;
    forn(i, 1, k) cin >> g[i].a >> g[i].b;
    forn(i, 1, m) {
        cin >> f[i].a >> f[i].b;
        cin >> w[i];
    }
    memset(lab, -1, sizeof lab);
    forn(i, 1, k) {
        Union(g[i].a, g[i].b);
        e[g[i].a].push_back(g[i].b);
        e[g[i].b].push_back(g[i].a);
    }
    forn(i, 1, m) if (choose[i] = Union(f[i].a, f[i].b)) {
        e[f[i].a].push_back(f[i].b);
        e[f[i].b].push_back(f[i].a);
    }   
    dfs(1);
    repn(lg, 1, Log) forn(i, 1, n) par[i][lg] = par[par[i][lg-1]][lg-1];
    d[0] = -1;
    forn(i, 1, n) rz[i] = INF, nxt[i] = i;
    forn(i, 1, m) {
        int u = f[i].a, v = f[i].b, p = lca(u, v);
        go(u, p, w[i]);
        go(v, p, w[i]);
    }
    long long result = 0;
    forn(i, 2, n) {
        result += rz[i];
        if (nxt[i] == i) { cout << -1; return 0; }
    }
    forn(i, 1, m) result -= choose[i] * w[i];
    cout << result;
}
