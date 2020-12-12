#include <bits/stdc++.h>
using namespace std;
#define llong       long long 
llong x, y, n;
llong solve() {
    llong res = 1 % n;
    while (y > 0) {
        if (y & 1) 
            res = res * x % n;
        x = x * x % n;
        y >>= 1;
    }
    return res;
}
int main(void) {
    int NTEST = 0;
    cin >> NTEST;
    for(; NTEST; NTEST--) {
        cin >> x >> y >> n;
        llong ans = solve();
        cout << ans << '\n';
    }
    int END;
    cin >> END;
}
