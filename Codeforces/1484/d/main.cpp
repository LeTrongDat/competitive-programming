#include <bits/stdc++.h>
using namespace std;
#define eb                  emplace_back
#define llong               long long 
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define repn(i, a, b)       for(int i = a; i <  b; ++i)
 
#ifndef LOCAL 
#define cerr                if (0) cerr 
#endif 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int del(set<int>::iterator bad_one, set<int> &bad_positions, set<int>& remainings, vector<int> &ans, vector<int> &a) {
    int pos = *bad_one; ans.eb(pos + 1);
    bad_positions.erase(bad_one);

    bad_one = remainings.lower_bound(pos);

    set<int>::iterator prev_one = bad_one == remainings.begin() ? prev(remainings.end()) : prev(bad_one);

    set<int>::iterator next_one = bad_one == prev(remainings.end()) ? remainings.begin() : next(bad_one);

    if (gcd(a[*next_one], a[*bad_one]) == 1) bad_positions.erase(*next_one);

    if (gcd(a[*next_one], a[*prev_one]) == 1) bad_positions.emplace(*next_one);
    
    int new_beginning =  *(next_one == prev(remainings.end()) ? remainings.begin() : next(next_one));
    remainings.erase(bad_one);

    return new_beginning;
}
auto solve() {
    int n; cin >> n;
    vector<int> a(n);
    repn(i, 0, n) cin >> a[i];
    set<int> remainings;
    set<int> bad_positions;
    vector<int> ans;

    repn(i, 0, n) {
        remainings.emplace(i);

        if (gcd(a[i], a[(i + 1) % n]) == 1) 
            bad_positions.emplace((i + 1) % n);
    }

    int beginning = 1;

    while (bad_positions.size() and remainings.size()) {
        set<int>::iterator bad_one = bad_positions.lower_bound(beginning);
        if (bad_one == bad_positions.end()) bad_one = bad_positions.begin();
        beginning = del(bad_one, bad_positions, remainings, ans, a);
    }
    return ans;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest; cin >> ntest;
    for(; ntest --;) {
        auto ans = solve();
        cout << ans.size() << ' ';
        for(auto pos: ans) cout << pos << ' ';
        cout << '\n';
    }
    return 0;
}
