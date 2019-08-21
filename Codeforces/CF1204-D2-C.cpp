#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pr pair < ll, ll >
#define vi vector < ll >
#define ft first
#define nd second
#define pb push_back

#define forn(i, a, b)   for(int i=a; i<=b; ++i)
#define ford(i, a, b)   for(int i=a; i>=b; --i)
#define repn(i, a, b)   for(int i=a; i <b; ++i)
#define repd(i, a, b)   for(int i=(int)a-1; i>=b; --i)
const int N = 110;
const int M = 1e6 +10;
int n, m;
int f[M];
int d[N][N], prv[M];
char a[N][N];
int v[M];
int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif //ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin >> n;
    memset(d, 0x3f, sizeof d);
    forn(i, 1, n) forn(j, 1, n) {
        cin >> a[i][j];
        if (a[i][j] == '1') d[i][j] = 1;
    }
    forn(i, 1, n) d[i][i] = 0;
    forn(i, 1, n) forn(j, 1, n) forn(k, 1, n) 
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    memset(f, 0x3f, sizeof f);
    cin >> m;
    forn(i, 1, m) cin >> v[i];
    f[1] = 1;
    forn(i, 2, m) forn(j, max(1, i-n), i-1) if (d[v[j]][v[i]] == i-j && f[i] > f[j] + 1) {
        f[i] = min(f[i], f[j] + 1);
        prv[i] = j;
    }
    cout << f[m] << '\n';
    int cur = m;
    vi ans;
    while (cur != 1) {
        ans.pb(v[cur]);
        cur = prv[cur];
    }
    ans.pb(v[1]);
    reverse(ans.begin(), ans.end());
    for(auto x: ans) cout << x << ' ';
    return 0;
}