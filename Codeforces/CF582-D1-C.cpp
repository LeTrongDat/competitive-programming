/*
    Author: Le Trong Dat
    Idea: https://codeforces.com/blog/entry/20692
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define repn(i, a, b)           for(int i=a; i <b; ++i)
typedef long long ll;
const int N = 2e5 +10;
ll n, ans;
ll a[2*N];
ll mx[N], sum[N], gcd[N];
void maximize(ll &a, ll b) { a = max(a, b); }
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    repn(i, 0, n) cin >> a[i];
    repn(i, n, 2*n) a[i] = a[i-n];
    repn(i, 1, n) gcd[i] = __gcd((ll)i, n);
    repn(g, 1, n) if (n % g == 0) {
        memset(mx, 0, sizeof mx);
        memset(sum, 0, sizeof sum);
        repn(i, 0, n) maximize(mx[i%g], a[i]);
        repn(i, 0, n) if (a[i] == mx[i%g]) {
            ll ri = i;
            while (ri+1 < 2*n && a[ri+1] == mx[(ri+1) % g]) ri ++;
            forn(j, 1, min(ri-i+1, n)) sum[j] += min(ri-j+1, n-1) - i+1;
            i = ri;
        }
        repn(i, 1, n) if (gcd[i] == g) ans += sum[i];
    }
    cout << ans;
}
