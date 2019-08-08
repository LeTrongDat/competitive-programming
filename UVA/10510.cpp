/*
  Author: Le Trong Dat
  Idea: 
    * Check if the graph is SCC ?
    * Simple cycles only intersect at articular point.
    => Find articular point and check is this partition simple cycle ?
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 +10;
struct Cactus {
  int n, m;
  int counter;
#define forn(i, a, b)   for(int i=a; i<=b; ++i)
#define repn(i, a, b)   for(int i=a; i <b; ++i)
#define ii    pair<int, int>
#define vi    vector<int>
#define pb    push_back
  vi e[N], low, entry, seen, processed;
  Cactus() {
    cin >> n >> m;
    seen.resize(n, 0);
    processed.resize(n, 0);
    low.resize(n, 0);
    entry.resize(n, 0);
    counter = 0;
    repn(i, 0, n) e[i].clear();
    forn(i, 1, m) {
      int u, v;
      cin >> u >> v;
      e[u].pb(v);
    }
  }
  bool is_cactus() {
    bool ok = dfs(0);
    repn(i, 0, n) if (!seen[i]) ok = false;
    return ok;
  }
  bool is_simple(int u, int s) {
    if (u == s) return true;
    int cnt = 0;
    for(auto v: e[u]) if (v == s || low[v] == entry[s]) 
      cnt ++;
    if (cnt > 1) return false;
    for(auto v: e[u]) if (v == s || low[v] == entry[s]) return is_simple(v, s);
  }
  bool dfs(int u) {
    seen[u] = true;
    entry[u] = low[u] = ++counter;
    for(auto v: e[u]) if (!seen[v]) {
      if (!dfs(v)) return false;
      low[u] = min(low[u], low[v]);
      if (low[v] > entry[u]) {
        return false;
      }
      if (low[v] == entry[u]) {
        if (!is_simple(v, u)) return false;
      }
    } else {
      if (processed[v]) return false;
      low[u] = min(low[u], entry[v]);
    }
    processed[u] = true;
    return true;
  }
};
int main() {
  ios::sync_with_stdio(0);
  int ncase; 
  cin >> ncase;
  forn(i, 1, ncase) {
    Cactus graph = Cactus();
    cout << (graph.is_cactus() ? "YES" : "NO") << '\n';
  }
}
