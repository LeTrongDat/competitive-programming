#include <bits/stdc++.h>
using namespace std;

#define pb  push_back
#define vi  vector<ll>
#define ll  long long
#define ft  first
#define nd  second
#define pr  pair<ll, ll>

#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define ford(i, a, b)           for(int i=a; i>=b; --i)
#define repn(i, a, b)           for(int i=a; i <b; ++i)
#define repd(i, a, b)           for(int i=(int)a-1; i>=b; --i)
int main() {
    ios::sync_with_stdio(0);
    int n, m; cin >> n;
    vi a(n);
    repn(i, 0, n) cin >> a[i];
    cin >> m;
    vi b(m);
    repn(i, 0, m) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    cout << a[n-1] << ' ' << b[m-1];
    return 0;
}