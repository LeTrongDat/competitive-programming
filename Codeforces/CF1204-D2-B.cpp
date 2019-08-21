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
ll a[1010];
int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif //ONLINE_JUDGE
    ios::sync_with_stdio(0);
    int n, l, r;
    cin >> n >> l >> r;
    int diff = 1;
    a[1] = 1;
    ll mx = 1;
    for(int i=2; i<=min(r, n); ++i) {
        a[i] = a[i-1] * 2;
        mx += a[i];
    }
    mx += a[min(r,n)] * (n - min(r, n));
    ll mn = 1;
    for(int i=2; i<=min(l, n); ++i) {
        a[i] = a[i-1] * 2;
        mn += a[i];
    }
    mn += 1 * (n - min(l, n));
    cout << mn << ' ' << mx;
    return 0;
}