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
    ll n; cin >> n;
    vi a(2 * n, 0);
    ll sum = n * n * (2 * n + 1);
    int modul = sum % (2 * n);
    if (abs(modul - (2 * n - modul)) != 0) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    int lo = 0, hi = 2 * n + 1;
    int turn = 0;
    repn(i, 0, 2 * n) {
        if (a[i]) continue; 
        if (!turn) {
            a[i] = ++lo;
            int pos = (i + n) % (2 * n);
            while (pos != i) {
                a[pos] = ++lo;
                pos = (pos + n) % (2 * n);
            }
        } else {
            a[i] = --hi;
            int pos = (i + n) % (2 * n);
            while (pos != i) {
                a[pos] = --hi;
                pos = (pos + n) % (2 * n);
            }
        }
        turn ^= 1;
    }
    repn(i, 0, 2*n) cout << a[i] << ' ';
    return 0;
}