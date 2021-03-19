#include <bits/stdc++.h>
using namespace std;
bool prime(int x) {
    for(int i = 2; i <= min((int)sqrt(x) + 1, x - 1); i ++) {
        if (x % i == 0) return false;
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    for(; ntest; ntest --) {
        int d; cin >> d;
        int cnt = 0;
        long long ans = 1;
        for(long long i = d + 1;; i++) {
            if (prime(i)) {
                cnt ++;
                ans *= i;
                i += d - 1;
            }
            if (cnt == 2) break;
        }
        cout << ans << '\n';
    }
    return 0;
}
