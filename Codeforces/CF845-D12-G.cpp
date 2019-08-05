/*
    Author: Le Trong Dat.
    Idea: https://csacademy.com/contest/archive/task/xor_cycle/solution/
        
*/  
#include <bits/stdc++.h>
using namespace std;
#define pb                          push_back
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
const int N = 1e5 +10;
struct Edge {
    int u, v, w;
    Edge(){};
    Edge(int u, int v, int w): u(u), v(v), w(w){};
} edge[N];
int n, m, P;
int lab[N], depth[N];
vector<pair<int, int>> e[N];
bool mark[N];
vector<int> a;
int root(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = root(lab[u]);
}
bool join(int u, int v) {
    int r1 = root(u), r2 = root(v);
    if (r1 == r2) return false;
    if (lab[r1] > lab[r2]) swap(r1, r2);
    lab[r1] += lab[r2];
    lab[r2] = r1;
    return true;
}
void dfs(int u, int prv = 0) {
    for(auto ss: e[u]) {
        int v = ss.first, w = ss.second;
        if (v == prv) continue;
        depth[v] = depth[u] ^ w;
        dfs(v, u);
    }
}
int get(int x, int i) { return (x >> i & 1); }
int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    memset(lab, -1, sizeof lab);
    forn(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[i] = {u, v, w};
        if (join(u, v)) {
            e[u].pb({v, w});
            e[v].pb({u, w});
            mark[i] = true;
        }
    }
    dfs(1);
    P = depth[n];
    forn(i, 1, m) if (!mark[i]) a.pb(edge[i].w ^ depth[edge[i].u] ^ depth[edge[i].v]);
    int col = 28;
    repn(i, 0, a.size()) {
        repn(j, i, a.size()) if (get(a[j], col)) { swap(a[i], a[j]); break; }
        if (!get(a[i], col)) {
            col --;
            if (col < 0) break;
            i --;
            continue;
        }
        repn(j, i+1, a.size()) if (get(a[j], col)) a[j] ^= a[i];
        col --;
        if (col < 0) break;
    }
    repn(i, 0, a.size()) P = min(P, P^a[i]);
    cout << P;
}
