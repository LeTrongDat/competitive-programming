#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
struct Dynamic_Segment_Tree {
    long long total, mini;
    long long le, ri;
    Dynamic_Segment_Tree *left, *right;
    Dynamic_Segment_Tree(){};
    Dynamic_Segment_Tree(long long _le, long long _ri) {
        le = _le; 
        ri = _ri;
        total = mini = 0;
        left = right = NULL;
    }
    void update(long long i, long long volume) {
        //cout << le << ' ' << ri << '\n';
        if (le == ri) {
            mini = volume;
            total = volume;
            return;
        }
        long long mid = le + ri >> 1LL;
        if (left == NULL) left = new Dynamic_Segment_Tree(le, mid);
        if (right == NULL) right = new Dynamic_Segment_Tree(mid+1, ri);
        if (i <= mid) left->update(i, volume); else right->update(i, volume);
        mini = min(left->mini, left->total + right->mini);
        total = left->total + right->total;
    }
    long long query_sum(long long i, long long j) {
        if (i > j) return 0;
        if (i <= le && ri <= j) return total;
        if (ri < i || j < le) return 0;
        long long mid = le + ri >> 1LL;
        if (left == NULL) left = new Dynamic_Segment_Tree(le, mid);
        if (right == NULL) right = new Dynamic_Segment_Tree(mid+1, ri);
        return left->query_sum(i, j) + right->query_sum(i, j);
    }
    long long query_min(long long i, long long j) {
        //cout << le << ' ' << ri << ' ' << i << ' ' << j << '\n';
        if (ri < i || j < le) return INF;
        if (i <= le && ri <= j) return mini;
        long long mid = le + ri >> 1LL;
        if (left == NULL) left = new Dynamic_Segment_Tree(le, mid);
        if (right == NULL) right = new Dynamic_Segment_Tree(mid+1, ri);
        return min(left->query_min(i, j), left->query_sum(i, j) + right->query_min(i, j));
    }
};
Dynamic_Segment_Tree *st = new Dynamic_Segment_Tree(0, 1e9);
typedef pair < long long, long long > pr;
multiset< pr > ms;
void get_time(long double l, long long r, long long s, long long v) {
    if (s >= 0) { cout << -1 << '\n'; return; }
    l += (long double) (-v) / (long double) (s);
    cout << fixed << setprecision(6) << (l <= r ? l : -1) << '\n';
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("a.inp", "r", stdin);
    freopen("a.out", "w", stdout);
#endif // ONLINE_JUDGE
    ios::sync_with_stdio(0);
    int nquery; cin >> nquery;
    int cnt = 0;
    for(; nquery; nquery --) {
        cnt ++;
        int type; cin >> type;
        if (type == 1) {
            long long t, s;
            cin >> t >> s;
            ms.insert({t, s});
            
            //if (cnt > 41) cout <<  1 << ' ' << t << ' ' << s << '\n';
            auto it = ms.find({t, s});
            if (it != ms.begin()) {
                pr prv = *prev(it);
                //cout << prv.first << ' ' << t << ' ' << prv.second << '\n';
                st->update(t, (t - prv.first) * prv.second);
            }
            if (it != prev(ms.end())) {
                pr nxt = *next(it);
                st->update(nxt.first, (nxt.first - t) * s);
            }
        }
        if (type == 2) {
            long long t, s;
            cin >> t;
            
            //if (cnt > 41) cout <<  2 << ' ' << t << '\n';
            st->update(t, 0);
            auto it = ms.lower_bound({t, -INF});
            s = (*it).second;
            if (it != prev(ms.end())) {
                pr nxt = *next(it);
                st->update(nxt.first, 0);
                if (it != ms.begin()) {
                    pr prv = *prev(it);
                    st->update(nxt.first, (nxt.first - prv.first) * prv.second);
                }
            }
            ms.erase(it);
        }
        if (type == 3) {
            long long l, r, v;
            cin >> l >> r >> v;
            //if (cnt > 41) cout << 3 << ' ' << l << ' ' << r << ' ' << v << '\n';
            if (!v) { cout << l << '\n'; continue; }
            if (ms.empty()) { cout << -1 << '\n'; continue; }
            auto it = ms.lower_bound({l, -INF});
            if (it == ms.end()) { cout << -1 << '\n'; continue; }
            pr cur = *it;
            if (cur.first >= r) { cout << -1 << '\n'; continue; }
            // cout << v << '\n';
            // cout << cur.first+1 << '\n';
            // cout << st->query_min(745314149, 745314149) << '\n';
            long long lo = cur.first + 1, hi = r, answer = -1;
            while (lo <= hi) {
                long long mid = lo+hi >> 1LL;
                //cout << lo << ' ' << hi << ' ' << st->query_min(cur.first+1, mid) << '\n';
                if (st->query_min(cur.first+1, mid) + v > 0) {
                    answer = mid;
                    lo = mid + 1;
                } else hi = mid - 1;
            }
            if (answer == -1) {
                get_time(cur.first, r, cur.second, v);
                continue;
            }
            //cerr << 1 << '\n';
            //cout << answer << '\n';
            auto nxt = ms.upper_bound({answer, -INF});
            nxt = prev(nxt);
            //cout << (*nxt).first << '\n';
            v += st->query_sum(cur.first + 1, (*nxt).first);
            //cout << v << ' ' << (*nxt).first << '\n';
            // cout << st->query_sum(cur.first + 1, (*nxt).first) << '\n';
            // cout << cur.first << ' ' << v << ' ' << (*nxt).first << ' ' << 
            //         (*nxt).second << '\n';
            get_time((*nxt).first, r, (*nxt).second, v);
        }
    }
}
