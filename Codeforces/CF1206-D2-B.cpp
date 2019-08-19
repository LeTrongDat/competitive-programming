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
    int n; cin >> n;
    vi a(n);
    bool exist = false;
    repn(i, 0, n) {
        cin >> a[i];
        if (a[i] == 0) exist = true;
    }
    ll ans = 0;
    repn(i, 0, n) if (abs(a[i]-1) > abs(a[i]+1)) {
        
        ans += abs(a[i]+1);
        a[i] = -1;
    } else {
        
        ans += abs(a[i] - 1);
        a[i] = 1;
    }
    int cur = 1;
    repn(i, 0, n) cur*= a[i];
    if (cur == -1 && !exist) ans += 2;
    cout << ans;

    return 0;
}