/*
    Author : Le Trong Dat.
    Idea: in shortly : subtask2: binary search + segment tree + sweep line.
            subtask 3: sweep line + two pointer + segment tree.
        in details : https://ioinformatics.org/files/ioi2008solutions.pdf.
*/
#include <bits/stdc++.h>
using namespace std;
#define FORN(i, a, b)               for(int i=a; i<=b; ++i)
#define FORD(i, a, b)               for(int i=a; i>=b; --i)
#define REPN(i, a, b)               for(int i=a; i <b; ++i)
#define REPD(i, a, b)               for(int i=(int)a-1; i>=b; --i)
const int maxR = 4*1e5 +10;
const int maxN = 1e6 +10;
const int INF = 1e9 +7;
int M, N, B, P;
typedef tuple<int, int, int> i3;
vector< i3 > open[maxN], close[maxN];
struct Rectangle {
    int x1, y1, x2, y2, cost;
    Rectangle(){};
    Rectangle(int x1, int y1, int x2, int y2): x1(x1), y1(y1), x2(x2), y2(y2) {};
    void expand(int d, int id = 0) {
        open[max(1, x1-d)].push_back({max(1, y1-d), y2, cost});
        close[x2].push_back({max(1, y1-d), y2, cost});
        open[x2+1].push_back({1, P+1, 0});
    }
    friend istream & operator >> (istream &is, Rectangle &T) {
        is >> T.x1 >> T.y1 >> T.x2 >> T.y2 >> T.cost;
        return is;
    }
} rec[maxR];
namespace subtask2 {
#define ii      pair<int, int>
    int a[maxN];
    int it[4*maxN], t[4*maxN];
    void lazy(int x, int l, int r) {
        it[x] += t[x];
        if (l != r) {
            t[2*x] += t[x];
            t[2*x+1] += t[x];
        }
        t[x] = 0;
    }
    void update(int x, int l, int r, int i, int j, int cost) {
        lazy(x, l, r);
        if (a[r] < i || j < a[l]) return;
        if (i <= a[l] && a[r] <= j) {
            t[x] = cost;
            lazy(x, l, r);
            return;
        }
        int m = l+r >> 1;
        update(2*x, l, m, i, j, cost);
        update(2*x+1, m+1, r, i, j, cost);
        it[x] = min(it[2*x], it[2*x+1]);
    }
    int query(int x, int l, int r, int i, int j) {
        lazy(x, l, r);
        if (a[r] < i || j < a[l]) return INF;
        if (i <= a[l] && a[r] <= j) return it[x];
        int m = l+r >> 1;
        return min(query(2*x, l, m, i, j), query(2*x+1, m+1, r, i, j));
    }
    bool ok(int d) {
        FORN(i, 1, P) rec[i].expand(d -1, 1);
        int result = INF;
        open[1].push_back({1, N-d+1, 0});
        FORN(i, 0, M) {
            if (open[i].size()) {
                for(auto ss: open[i]) {
                    int y1, y2, cost;
                    tie(y1, y2, cost) = ss;
                    update(1, 1, P+1, y1, y2, cost);
                }
                if (i <= M-d+1) result = min(result, query(1, 1, P+1, 1, N-d+1));
            }   
            if (close[i].size()) {       
                for(auto ss: close[i]) {
                    int y1, y2, cost;
                    tie(y1, y2, cost) = ss;
                    update(1, 1, P+1, y1, y2, -cost);
                }
            }   
        }
        FORN(i, 1, M) open[i].clear(), close[i].clear();
        return (result <= B);
    }
    void run() {
        FORN(i, 1, P) a[i] = rec[i].y2 + 1;
        a[P+1] = 1;
        sort(a+1, a+P+2);
        int low = 0, high = min(M, N), result = 0;
        while (low <= high) {
            int mid = low + high >> 1;
            if (ok(mid)) {
                result = mid;
                low = mid+1;
            } else high = mid-1;
        }
        cout << result << '\n';
    }
}
namespace subtask3 {
    int result = 0;
    int mx[4*maxN], le[4*maxN], ri[4*maxN], cnt[4*maxN];

    void lazy(int x, int l, int r) {
        int m = l+r >> 1;
        if (l<r) {
            mx[x] = max(max(mx[2*x], mx[2*x+1]), ri[2*x] + le[2*x+1]);
            le[x] = (le[2*x] >= m-l+1 ? le[2*x] + le[2*x+1] : le[2*x]);
            ri[x] = (ri[2*x+1] >= r-m ? ri[2*x+1] + ri[2*x] : ri[2*x+1]);
        } else mx[x] = le[x] = ri[x] = 1;
    }
    void update(int x, int l, int r, int i, int j, int cost) {
        if (j < l || r < i) return;
        if (i <= l && r <= j) {
            cnt[x] += cost;
            if (cnt[x]) mx[x] = le[x] = ri[x] = 0;
                else lazy(x, l, r);
            return;
        }
        int m = l+r >> 1;
        update(2*x, l, m, i, j, cost);
        update(2*x+1, m+1, r, i, j, cost);
        if (cnt[x] == 0) lazy(x, l, r);
    }
    void update(int r) {
        for(auto ss: open[r]) {
            int y1, y2, cost;
            tie(y1, y2, cost) = ss;
            update(1, 1, N, y1, y2, 1);
            close[rec[cost].x2].push_back({y1, y2, cost});
        }
    }
    void build(int x, int l, int r) {
        mx[x] = le[x] = ri[x] = r-l+1;
        if (l == r) return;
        int m = l+r >> 1;
        build(2*x, l, m);
        build(2*x+1, m+1, r);
    }
    void run() {
        build(1, 1, N);
        FORN(i, 1, P) open[rec[i].x1].push_back({rec[i].y1, rec[i].y2, i});
        int ri = 0;
        FORN(i, 1, M) {
            ri = max(ri, i-1);
            while (ri <= M && mx[1] >= ri-i+1) {
                ri ++;
                update(ri);
            }
            result = max(result, ri-i);
            for(auto ss: close[i]) {
                int y1, y2, cost;
                tie(y1, y2, cost) = ss;
                update(1, 1, N, y1, y2, -1);
            }
        }
        cout << result << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> M >> N >> B >> P;
    FORN(i, 1, P) cin >> rec[i];
    if (P <= 3e4) subtask2::run();
        else subtask3::run();
    return 0;
}
