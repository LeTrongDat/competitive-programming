/*
    Author: Le Trong Dat
    Idea: - With each vertex, finding the three longest paths that do not intersect starting from that vertex, 
    call their lengths x1, x2, x3. The longest route length going through vertex u is x1 * (x2 + x3) with x1> x2> x3.
        => Dp find the 3 longest lengths from each vertex and the number of paths with the same length.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define ford(i, a, b)               for(int i=a; i>=b; --i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
#define repd(i, a, b)               for(int i=(int)a -1; i>=b; --i)
#define llong                       long long 
#define ii                          pair<llong, llong> 
const llong INF = 2;
const int maxN = 5e5 + 10;
int N;
vector<ii> D[maxN];
vector<int> E[maxN];
ii F[maxN], out[maxN];
llong d2[maxN], sum2[maxN];
void maximize(ii &a, ii b) {
    if (a.first < b.first + 1) {
        a.first = b.first + 1;
        a.second = b.second;
    } else if (a.first == b.first + 1) a.second += b.second;
}
void dfs1(int u, int prv = 0) {
    F[u] = {-INF, 0};
    bool leaf = true;
    for(auto v: E[u]) if (v != prv) {
        leaf = false;
        dfs1(v, u);
        maximize(F[u], F[v]);
        D[u].push_back(F[v]);
    }
    sort(D[u].begin(), D[u].end());
    reverse(D[u].begin(), D[u].end());
    repn(i, 0, D[u].size()) if (D[u][i].first + 1 != F[u].first) {
        d2[u] = D[u][i].first + 1;
        repn(j, i, D[u].size()) if (D[u][j].first == D[u][i].first) sum2[u] += D[u][j].second; 
           else break;
        break;
    }
    if (leaf) F[u] = {0, 1};
}
void dfs2(int u, int prv = 0) {
    out[u] = {-INF, 0};
    if (!prv) out[u] = {0, 1}; 
        else {
            maximize(out[u], out[prv]);
            if (F[u].first + 1 == F[prv].first) {
                if (F[u].second != F[prv].second) maximize(out[u], {F[prv].first, F[prv].second -F[u].second}); 
                    else maximize(out[u], {d2[prv], sum2[prv]});
            } else maximize(out[u], F[prv]);
        }
    for(auto v: E[u]) if (v != prv) dfs2(v, u);
}
int main() {
    ios::sync_with_stdio(0);
    cin >> N;
    repn(i, 1, N) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs1(1);
    dfs2(1);
    llong result = 0, ways = 0;
    forn(u, 1, N) {
        for(auto &x: D[u]) x.first ++;
        D[u].push_back(out[u]);
        sort(D[u].begin(), D[u].end());
        reverse(D[u].begin(), D[u].end());
        if (D[u].size() < 3 || D[u][2].first <= 0) continue;
        while (D[u].size() && D[u].back().first != D[u][2].first) D[u].pop_back();
        long long paths, a, ab;
        paths = a = ab = 0;
        if (D[u][0].first == D[u][2].first) {
            for(auto v: D[u]) {
                ab  += v.second * a;
                a   += v.second; 
            }
            paths = ab;
        } else {
            if (D[u][1].first == D[u][2].first) {
                for(auto v: D[u]) if (v.first != D[u][0].first) {
                    ab += v.second  * a;
                    a  += v.second;
                }
                paths = ab;
            } else {
                for(auto v: D[u]) if (v.first == D[u][2].first) a += v.second;
                if (D[u][0].first == D[u][1].first) paths = (D[u][0].second + D[u][1].second) * a;
                    else paths = D[u][1].second * a;
            }
        }
        llong Dist = D[u][0].first * (D[u][1].first + D[u][2].first);
        if (result < Dist) {
            result = Dist;
            ways = paths;
        } else if (result == Dist) ways += paths;
    }
    if (result == 0) ways = 1;
    cout << result << ' ' << ways << '\n';
    return 0;
}
