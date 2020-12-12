#include <bits/stdc++.h>
using namespace std;
#define llong               long long
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
llong n, k;
string solve() {
    string res = "";
    forn(i, 1, n) res += char('a' + i%3);
    return res;
}
int main(void) {
    ios::sync_with_stdio(0);
    int NTEST; cin >> NTEST;
    for(; NTEST; NTEST --) {
        cin >> n >> k;
        auto ans = solve();
        cout << ans << '\n';
    }
}
