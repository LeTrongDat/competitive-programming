#include <bits/stdc++.h>
using namespace std;
#define eb                  emplace_back
#define llong               long long 
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define repn(i, a, b)       for(int i = a; i <  b; ++i)
 
#ifndef LOCAL 
#define cerr                if (0) cerr 
#endif 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

auto solve() {
    int n, m; cin >> n >> m;
    vector< vector<llong> > d;
    vector< vector<llong> > mx;
    repn(i, 0, n + 1) {
        d.eb(vector<llong>(n + 1, LLONG_MAX / 2));
        mx.eb(vector<llong>(n + 1, LLONG_MIN));
    }

    vector<tuple<int, int, int>> edges;
    repn(i, 0, m) {
        int u, v, w; cin >> u >> v >> w;
        edges.eb(u, v, w);
        d[u][v] = d[v][u] = w;
    }
    int q; cin >> q;
    vector<tuple<int, int, int>> trips(q);
    repn(i, 0, q) {
        int u, v, l; cin >> u >> v >> l;
        trips[i] = {u, v, l};
    }
    forn(i, 1, n) d[i][i] = 0;

    forn(k, 1, n) forn(i, 1, n) forn(j, 1, n) 
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    forn(v, 1, n) for(auto trip: trips) {
        int s, t, l;
        tie(s, t, l) = trip;
        mx[s][v] = max(mx[s][v], (llong)l - d[v][t]);
    }
    int ans = 0;
    for(auto edge: edges) {
        int u, v, w; tie(u, v, w) = edge;
        forn(s, 1, n) {
            if (d[s][u] + w <= mx[s][v] or d[s][v] + w <= mx[s][u]) {
                ans ++;
                break;
            }
        }
    } 
    return ans;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest = 1;
    for(; ntest --;) {
        auto ans = solve();
        cout << ans << '\n';
    }
    return 0;
}
