/*
    Author: Le Trong Dat
    Idea: * Go from the lowest coordinate.
        * Go right when it's possible, then go straight, then go left and eventually, go backward.
        * If we find a loop, then all outer walls in that loop will be collapsed.
*/
#include <bits/stdc++.h>
using namespace std;
#define x  first
#define y  second
#define pb push_back
#define pr pair < int, int > 

#define forn(i, a, b)   for(int i=a; i<=b; ++i)
#define repn(i, a, b)   for(int i=a; i <b; ++i)
const int N = 1e5 + 10;
vector < pair < pr, int > > v;
multiset < pair < pr, int > > ms;
int n, w;
vector < pr > e[N][5];
bool visit[N];
vector < int > ans;
pr p[N];
istream & operator >> (istream &is, pr &p) {
    is >> p.x >> p.y;
    return is;
}
int direction(pr &pa, pr &pb) {
    if (pb.x == pa.x) {
        if (pb.y > pa.y) return 0;
        return 2;
    }
    if (pb.x > pa.x) return 1;
    return 3;
}
int go(int u, int dir = 0) {
    if (visit[u]) return u;
    visit[u] = true;
    repn(i, 0, 4) {
        int nxt = ( (dir + 1) - i + 4 ) % 4;
        if (e[u][nxt].empty()) continue;
        auto ed = e[u][nxt].front();
        e[u][nxt].clear();
        int v = ed.y;
        e[v][(nxt + 2) % 4].clear();
        int loop = go(v, nxt);
        if (!loop) {
            ans.pb(ed.x);
            continue;
        }
        if (loop != u) {
            visit[u] = false;
            return loop;
        }
    }
    visit[u] = false;
    return 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    forn(i, 1, n) {
        cin >> p[i];
        v.pb({p[i], i});
    }
    cin >> w;
    forn(i, 1, w) {
        int u, v;
        cin >> u >> v;
        e[u][direction(p[u], p[v])].pb({i, v});
        e[v][direction(p[v], p[u])].pb({i, u});
    }
    sort(v.begin(), v.end());
    for(auto st: v) go(st.y);
    cout << ans.size() << '\n';
    for(auto id: ans) cout << id << '\n';
    return 0;
}