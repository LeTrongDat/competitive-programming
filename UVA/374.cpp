#include <bits/stdc++.h>
using namespace std;
#define llong       long long 
llong b, p, m;
llong solve() {
    llong res =1 % m;
    while (p > 0) {
        if (p & 1) 
            res = res * b % m;
        b = b * b % m;
        p >>= 1;
    }
    return res;
}
int main() {
    while (cin >> b >> p >> m) {
        llong ans = solve();
        cout << ans << '\n';
    }
}
