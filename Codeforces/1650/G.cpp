#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ii = tuple<int, int>

const int N = 2e5 + 10;
const int inf = 1000111000;

int n, m, s, t;
vector<int> adj[N];

int add(int &a, int b) {
    a = (a + b) % MOD;
    return a;
}
void min_dis_fr(int source, int min_dis[], int size) {
    fill(min_dis, min_dis + size, inf);
    min_dis[source] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;

    pq.emplace((0, source));
    while (!pq.empty()) {
        int u, du;
        tie(du, u) = pq.top();
        pq.pop();
        if (min_dis[u] != du) continue;

        for(auto v: adj[u]) {
            if (min_dis[v] > du + 1) {
                min_dis[v] = du + 1;
                pq.emplace(min_dis[v], v);
            }
        }
    }
}
void solve() {
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].emplace(v);
        adj[v].emplace(u);
    }
    min_dis_fr(s, fr_s, n);
    min_dis_fr(t, fr_t, n);

    cnt[s][0] = 1;
    queue<int> q;
    q.emplace(s);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for(auto v: adj[u]) {
            if (fr_s[u] + 1 + fr_t[v] == fr_s[t]) {
                add(cnt[v][0], cnt[s][0]);
                add(cnt[v][1], cnt[s][1]);
                continue;
            }
            if (fr_s[u] + 1 + fr_t[v] == fr_s[t] + 1) {
                add(cnt[v][1], cnt[s][0]);
            }
        }
    }
    cout << add(cnt[t][0], cnt[t][1]) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();
    return 0;
}