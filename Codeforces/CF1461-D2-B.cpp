#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
#define llong               long long
const int MAXN = 510;
int m, n;
int sum[MAXN][MAXN];

void read() {
    cin >> n >> m;
    forn(i, 1, n) forn(j, 1, m) {
        char c; cin >> c;
        sum[i][j] = (c == '*' ? 1 : 0);
    }
}
void prepare() {
    forn(i, 1, n) forn(j, 1, m) {
        sum[i][j] = sum[i][j-1] + sum[i][j];
    }
}
int solve() {
    prepare();
    llong ans = 0;
    forn(i, 1, n) forn(j, 1, m) {
        forn(height, 1, min(n-i+1, min(m-j+1, j))) {
            if (sum[i+height-1][j+height-1] - sum[i+height-1][j-height] != 2 * height - 1) break;
            ans ++;
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    int NTEST; cin >> NTEST;
    for(; NTEST; NTEST--) {
        read();
        auto ans = solve();
        cout << ans << '\n';
    }
}
