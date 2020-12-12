#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
#define ford(i, a, b)       for(int i=a; i>=b; --i)
#define llong               long long 

map<int, bool> query;
int n, q;
vector<llong> a;
vector<llong> queries;
struct IntervalTree {
    int n, q;
    vector<llong> a;
    vector<llong> queries;
    vector<llong> sum;
    map<llong, int> is_queried;
    map<llong, bool> ans;

    IntervalTree(){};
    IntervalTree(vector<llong> &a, vector<llong> &queries) {
        this->a = a;
        this->queries = queries;
        q = queries.size() - 1;
        n = a.size() - 1;
        sum.resize(n + 1, 0);
    }
    
    void init() {
        is_queried.clear();
        ans.clear();
        forn(i, 1, q) is_queried[queries[i]] = i;
        sort(a.begin() +1, a.end());
        forn(i, 1, n) sum[i] = sum[i-1] + a[i];
    }

    int find(int mid_val, int l_idx, int r_idx) {
        int res = l_idx;
        while (l_idx <= r_idx) {
            int m = (l_idx + r_idx) >> 1;
            if (a[m] <= mid_val) {
                res = m;
                l_idx = m + 1;
            } else r_idx = m - 1;
        }
        return res;
    }
    
    void build(int l_idx, int r_idx) {
        llong value = sum[r_idx] - sum[l_idx-1];
        if (is_queried.count(value)) {
            ans[value] = true;
        }
        if (l_idx == r_idx) return;
        llong mid = (a[r_idx] + a[l_idx]) >> 1;
        int mid_pos = find(mid, l_idx, r_idx);
        if (mid_pos == r_idx) return;
        build(l_idx, mid_pos);
        build(mid_pos+1, r_idx);
    }
} tree;
void read() {
    cin >> n >> q;
    a.resize(n+1);
    queries.resize(q+1);
    forn(i, 1, n) cin >> a[i];
    forn(i, 1, q) cin >> queries[i];
}
map<llong, bool> solve() {
    tree = IntervalTree(a, queries);
    tree.init();
    tree.build(1, n);
    return tree.ans;
}
void write(map<llong, bool> ans) {
    forn(i, 1, q) 
        cout << (ans.count(queries[i]) ? "Yes" : "No") << '\n';
}
int main(void) {
    ios::sync_with_stdio(0);
    int NTEST; cin >> NTEST;
    for(; NTEST; NTEST --) {
        read();
        auto ans = solve();
        write(ans);
    }
}
