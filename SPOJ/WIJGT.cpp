/*
    Author: Le Trong Dat
    Idea: 
        Build a graph n vertices with each wall is a vertex.
        Distance between 2 vertices is the minimum distance between 2 segments.
        Answer is the minimum distance from vertex 1 to vertex 2.
*/
#include <bits/stdc++.h>
using namespace std;
#define ft                      first
#define nd                      second
#define pb                      push_back
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define ford(i, a, b)           for(int i=a; i>=b; --i)
#define repn(i, a, b)           for(int i=a; i <b; ++i)
#define repd(i, a, b)           for(int i=(int)a-1; i>=b; --i)
const int N = 1010;
const int INF = INT_MAX;
typedef pair<int, int> ii;
typedef long double ldb;
int n;
int d[N];
vector< ii > e[N];
struct Segment {
    int x[2], y[2], l;
    Segment(){};
    friend istream & operator >> (istream &is, Segment &T) {
        is >> T.x[0] >> T.y[0] >> T.l;
        T.x[1] = T.x[0] + abs(T.l) * (T.l >= 0);
        T.y[1] = T.y[0] + abs(T.l) * (T.l <  0);
        return is;
    }
} seg[N];
void minimize(int &a, int b) { a = min(a, b); }
int dp(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
int fi(int x, int y, Segment &s) {
    int rz = INF;
    int lo = (s.l >= 0 ? s.x[0] : s.y[0]), hi = (s.l >= 0 ? s.x[1] : s.y[1]);
    while (hi - lo > 4) {
        int m1 = lo + hi >> 1;
        int m2 = m1 + 1;
        if (s.l >= 0) {
            if (dp(x, y, m1, s.y[0]) > dp(x, y, m2, s.y[0])) lo = m1; else hi = m2;
        } else {
            if (dp(x, y, s.x[0], m1) > dp(x, y, s.x[0], m2)) lo = m1; else hi = m2;
        }
    }
    forn(i, lo, hi) if (s.l >= 0) minimize(rz, dp(x, y, i, s.y[0]));
        else minimize(rz, dp(x, y, s.x[0], i));
    return rz;
}
bool pointInSeg(int x, int y, Segment &a) {
    if (sqrt((ldb)dp(a.x[0], a.y[0], x, y)) + sqrt((ldb)dp(x, y, a.x[1], a.y[1])) == 
        sqrt((ldb)dp(a.x[0], a.y[0], a.x[1], a.y[1]))) return true;
    return false;
}
int distance(Segment &a, Segment &b) {
    int rz = INF;
    if (a.l * b.l >= 0) {
        if (a.l >= 0 && a.y[0] == b.y[0] && 
        (b.x[0] <= a.x[1] && a.x[1] <= b.x[1] || 
        a.x[0] <= b.x[1] && b.x[1] <= a.x[1])) return 0;
        if (a.l <= 0 && a.x[0] == b.x[0] && 
        (b.y[0] <= a.y[1] && a.y[1] <= b.y[1] || 
        a.y[0] <= b.y[1] && b.y[1] <= a.y[1])) return 0;
    } else {
        int x = (a.l >= 0 ? b.x[0] : a.x[0]);
        int y = (a.l < 0 ? b.y[0] : a.y[0]);
        if (pointInSeg(x, y, a) && pointInSeg(x, y, b)) return 0;
    }
    repn(i, 0, 2) minimize(rz, fi(a.x[i], a.y[i], b));
    repn(i, 0, 2) minimize(rz, fi(b.x[i], b.y[i], a));
    return rz;
}
int main() {
    ios::sync_with_stdio(0);
    for(; cin >> n;) {
        if (!n) break;
        forn(i, 1, n) cin >> seg[i];
        forn(i, 1, n) e[i].clear();
        forn(i, 1, n) forn(j, i+1, n) {
            int w = distance(seg[i], seg[j]);
            e[i].pb({j, w});
            e[j].pb({i, w});
        }
        memset(d, 0x3f, sizeof d);
        d[1] = 0;
        priority_queue< ii, vector<ii>, greater<ii> > pq;
        pq.push({0, 1});
        for(; pq.size();) {
            auto ss = pq.top();
            pq.pop();
            if (d[ss.nd] != ss.ft) continue;
            for(auto nxt: e[ss.nd]) {
                int v = nxt.ft, w = nxt.nd;
                if (d[v] > max(d[ss.nd], w)) {
                    d[v] = max(d[ss.nd], w);
                    pq.push({d[v], v});
                }
            }
        }
        cout << fixed << setprecision(2) << sqrt((long double)d[2]) << '\n';
    }
}
