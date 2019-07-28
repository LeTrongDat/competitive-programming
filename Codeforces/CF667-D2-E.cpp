/*
    Author: Le Trong Dat
    Idea: https://codeforces.com/blog/entry/44605?#comment-291339
*/  
#include <bits/stdc++.h>
using namespace std;
#define pb                  push_back
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
#define ford(i, a, b)       for(int i=a; i>=b; --i)
#define repn(i, a, b)       for(int i=a; i <b; ++i)
#define repd(i, a, b)       for(int i=(int)a-1; i>=b; --i)
const int INF = 5e8;
typedef pair<int, int> ii;
typedef long long llong;
int x[5], y[5];
int ans;
vector<ii> tr;
void minimize(int &a, int b) { a = min(a, b); }
void maximize(int &a, int b) { a = max(a, b); }
int dist(int x1, int y1, int x2, int y2) {
    if (x1 == x2) return abs(y1-y2);
    if (y1 == y2) return abs(x1-x2);
    return INF;
}
int query(int x1, int x2, int y1, int y2, int id) {
    vector<ii> vi;
    vi.pb({x1, y1});
    vi.pb({x1, y2});
    vi.pb({x2, y1});
    vi.pb({x2, y2});
    vector<int> p;
    int rz = INF;
    repn(i, 0, 4) p.pb(i);
    do {
        int sumD = 0;
        repn(i, 0, 4) maximize(sumD, dist(x[i], y[i], vi[p[i]].first, vi[p[i]].second));
        minimize(rz, sumD);
        if (ans > sumD) {
            ans = sumD;
            tr.clear();
            repn(i, 0, 4) if (!id) tr.pb(vi[p[i]]);
                else {
                    auto ss = vi[p[i]];
                    swap(ss.first, ss.second);
                    ss.second = -ss.second;
                    tr.pb(ss);
                }
        }
    } while (next_permutation(p.begin(), p.end()));
    return rz;
}
int get_ans(int id) {
    int rz = INF;
    vector<int> xx, yy;
    repn(i, 0, 4) xx.pb(x[i]), yy.pb(y[i]);
    for(auto x1: xx) for(auto x2: xx) if (x1 < x2) {
        for(auto y1: yy) {
            minimize(rz, query(x1, x2, y1, y1 + abs(x1-x2), id));
            minimize(rz, query(x1, x2, y1, y1 - abs(x1-x2), id));
        }
    }
    for(auto x1: xx) for(auto x2: xx) if (x1 < x2) {
        int lo = -INF, hi = INF;
        while (hi - lo > 4) {
            int m1 = lo+hi >> 1;
            int m2 = m1 + 1;
            if (query(x1, x2, m1, m1 + abs(x1-x2), id) > query(x1, x2, m2, m2 + abs(x1-x2), id))
                lo = m1; 
            else hi = m2;
        }
        forn(i, lo, hi) minimize(rz, query(x1, x2, i, i+abs(x1-x2), id));
    }
    return rz;
}
int main() {
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    for(; T; T--) {
        repn(i, 0, 4) cin >> x[i] >> y[i];
        ans = INF;
        tr.clear();
        minimize(ans, get_ans(0));
        repn(i, 0, 4) swap(x[i], y[i]), x[i] = -x[i];
        minimize(ans, get_ans(1));
        if (ans == INF) cout << "-1 \n"; 
            else {
                cout << ans << '\n';
                for(auto ss: tr) cout << ss.first << ' ' << ss.second << '\n';
            }
    }
}
