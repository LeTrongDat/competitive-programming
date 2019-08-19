#include <bits/stdc++.h>
using namespace std;

#define pb  push_back
#define vi  vector<ll>
#define ll  long long
#define ft  first
#define nd  second
#define pr  pair<ll, ll>

#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define ford(i, a, b)           for(int i=a; i>=b; --i)
#define repn(i, a, b)           for(int i=a; i <b; ++i)
#define repd(i, a, b)           for(int i=(int)a-1; i>=b; --i)
const int INF = 1e9;
vi bit[70];
int d[210];
bool e[210][210];
int main() {
    ios::sync_with_stdio(0);
    ll n; cin >> n;
    vi a(n, 0);
    repn(i, 0, n) cin >> a[i];
    vi b;
    repn(i, 0, n) if (a[i] != 0) b.pb(a[i]);
    a = move(b);
    n = a.size();
    for(ll i = 0; i < 64; ++i) repn(j, 0, n) 
        if (a[j] >> i & 1LL) bit[i].pb(j);
    repn(i, 0, 64) if (bit[i].size() > 2) { cout << 3; return 0; }
    repn(i, 0, 64) {
        for(auto u: bit[i]) for(auto v: bit[i]) if (u != v) {
            e[u][v] = e[v][u] = true;
        }
    }
    int ans = INF;
    repn(i, 0, n) {
        repn(j, 0, n) if (e[i][j]) {
            repn(u, 0, n) d[u] = INF;
            d[i] = 0;
            d[j] = 1;
            queue < int > q;
            q.push(j);
            while (q.size()) {
                int u = q.front(); q.pop();
                repn(v, 0, n) if (e[u][v] && v != i) {
                    if (d[v] > d[u] + 1) {
                        d[v] = d[u] + 1;
                        q.push(v);
                    }
                }
            }
            repn(u, 0, n) if (u != i && u != j) {
                if (e[u][i]) ans = min(ans, d[u] + 1);
            }
        }
    }
    cout << (ans == INF ? -1 : ans);


    return 0;
}