/*
    Author: Le Trong Dat
    Idea: https://codeforces.com/blog/entry/50456.
        https://codeforces.com/blog/entry/50456?#comment-344219.
*/
#include <bits/stdc++.h>
using namespace std;
#define pb                      push_back
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
typedef vector<int> vi;
const int INF = 0x3f3f3f3f;
const int N = 3e5 +10;
int n, q;
int rz[N], a[N];
int l[N], r[N], compress[N];
int mn[4*N], mx[4*N], t[4*N];
vi vq[N], v;
void update(int x, int l, int r, int i, int v) {
    if (l == r) {
        mx[x] = v;
        return;
    }
    int m = l+r >> 1;
    if (i > m) update(2*x+1, m+1, r, i, v);
        else update(2*x, l, m, i, v);
    mx[x] = max(mx[2*x], mx[2*x+1]);
}
int query(int x, int l, int r, int i, int j) {
    if (i > j) return 0;
    if (r < i || j < l) return 0;
    if (i <= l && r <= j) return mx[x];
    int m = l+r >> 1;
    return max(query(2*x, l, m, i, j), query(2*x+1, m+1, r, i, j));
}
void lazy(int x, int l, int r) {
    mn[x] = min(mn[x], t[x]);
    if (l != r) {
        t[2*x] = min(t[2*x], t[x]);
        t[2*x+1] = min(t[2*x+1], t[x]);
    }
    t[x] = INF;
}
void update_ans(int x, int l, int r, int i, int j, int v) {
    lazy(x, l, r);
    if (r < i || j < l) return;
    if (i <= l && r <= j) {
        t[x] = v;
        lazy(x, l, r);
        return;
    }
    int m = l+r >> 1;
    update_ans(2*x, l, m, i, j, v);
    update_ans(2*x+1, m+1, r, i, j, v);
    mn[x] = min(mn[2*x], mn[2*x+1]);
}
int query_ans(int x, int l, int r, int i) {
    lazy(x, l, r);
    if (l == r) return mn[x];
    int m = l+r >> 1;
    if (i > m) return query_ans(2*x+1, m+1, r, i);
    return query_ans(2*x, l, m, i);
}
void process() {
    forn(i, 1, n) compress[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    memset(mx, 0, sizeof mx);
    memset(mn, 0x3f, sizeof mn);
    memset(t, 0x3f, sizeof t);
    forn(i, 1, n) vq[i].clear();
    forn(i, 1, q) vq[r[i]].pb(i);
    update(1, 1, n, compress[1], 1);
    forn(i, 2, n) {
        int idx = query(1, 1, n, compress[i], n);
        if (idx) update_ans(1, 1, n, 1, idx, a[idx] - a[i]);
        while (idx) {
            int val = (a[idx] + a[i] + 1) / 2;
            int pos = lower_bound(v.begin(), v.end(), val) - v.begin() +1;
            pos --;
            idx = query(1, 1, n, compress[i], pos);
            if (idx == 0) break;
            update_ans(1, 1, n, 1, idx, a[idx] - a[i]);
        }
        for(auto qu: vq[i]) rz[qu] = min(rz[qu], query_ans(1, 1, n, l[qu]));
        update(1, 1, n, compress[i], i);
    }
}
int main() {
    ios::sync_with_stdio(0);
    memset(rz, 0x3f, sizeof rz);
    cin >> n;
    forn(i, 1, n) {
        cin >> a[i];
        v.pb(a[i]);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end())-v.begin());
    cin >> q;
    forn(i, 1, q) cin >> l[i] >> r[i];
    process();
    reverse(a+1, a+n +1);
    forn(i, 1, q) {
        l[i] = n-l[i]+1;
        r[i] = n-r[i]+1;
        swap(l[i], r[i]);
    }
    process();
    forn(i, 1, q) cout << rz[i] << '\n';
    return 0;
}
