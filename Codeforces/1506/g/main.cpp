#include <bits/stdc++.h>
using namespace std;
#define eb                  emplace_back
#define llong               long long 
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define repn(i, a, b)       for(int i = a; i <  b; ++i)
#define repd(i, a, b)       for(int i = (int) a-1; i >= b; --i)
 
#ifndef LOCAL 
#define cerr                if (0) cerr 
#endif 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto solve() {
    string s; cin >> s;
    int n = s.length();
    int sz_alphabet = 26;
    set<int> pivots;
    vector< vector<int> > positions(26);

    repn(i, 0, n) positions[s[i]-'a'].eb(i);
    repn(i, 0, sz_alphabet) if (positions[i].size()) 
        pivots.insert(positions[i].back());

    pivots.insert(n);

    string ans = "";
    repn(i, 0, n) {

        if (positions[s[i]-'a'].empty()) continue;
        if (*pivots.begin() == i) { ans += s[i]; pivots.erase(pivots.begin()); continue; }
        int nxt_pvt = *pivots.begin();
        int m = nxt_pvt - i;
        vector<int> mx(m + 1);
        mx[m] = s[i+m] - 'a';
        repd(j, nxt_pvt, i) {
            mx[j-i] = mx[j-i+1];
            if (positions[s[j]-'a'].size()) mx[j-i] = max(mx[j-i+1], s[j]-'a');
        }
        int max_c = -1;
        forn(j, i, nxt_pvt) if (positions[s[j]-'a'].size()) {
            max_c = max(max_c, s[j] - 'a');
            if (max_c == s[j] - 'a' and mx[j-i] == s[j]-'a') {
                ans += s[j];
                for(auto pos: positions[s[j]-'a']) pivots.erase(pos);
                positions[s[j]-'a'].clear();
                i = j;
                break;
            }
        }
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
        cout << ans << '\n';
    }
    return 0;
}
