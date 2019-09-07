/*
    Author: Le Trong Dat
    Idea: p(x) is the product of its digits with itself.
    => p(x) * x <= B <=> p(x) <= sqrt(B) <= 1e9
    p(x) = (1^x1) * (2^x2) * (3^x3) ... * (9^x9) 
        = (2^k1) * (3^k2) * (5^k3) * (7^k4).
    => Only have ~ 5100 numbers like that <= 1e9.
    => We can recursive the answer.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)   for(int i=a; i<=b; ++i)
typedef long long ll;
typedef pair<ll, ll> pr;
ll A, B;
ll powx[20];
ll lo, hi;
map<pr, ll> dp;
ll cal(ll N, ll prf, ll prod) {
    if ( prf < lo / powx[N] ) return 0;
    if ( prf > hi / powx[N] ) return 0;
    if (hi >= powx[N] - 1 &&  prf >= (lo + powx[N] - 1) / powx[N] && prf <= (hi + 1 - powx[N]) / powx[N] ) return dp[{N, prod}];
    ll rz = 0;
    forn(i, min(1LL, prf), 9) if (i == 0 || prod % i == 0) rz += cal(N-1, prf * 10 + i, (i == 0 ? prod : prod / i));
    return rz;
}
ll backtrack(ll N, ll prod) {
    if (dp.find({N, prod}) != dp.end()) return dp[{N, prod}];
    ll &ans = dp[{N, prod}];
    if (N == 0) return ans = (prod == 1);
    ans = 0;
    forn(i, 1, 9) if (prod % i == 0) ans += backtrack(N-1, prod/i);
    return ans;
}
ll pw(ll a, ll q) {
    ll rz = 1;
    forn(i, 1, q) rz *= a;
    return rz;
}
ll process(ll a, ll b, ll px) {
    lo = a, hi = b;
    return cal(18, 0, px);
}
int main() {
    cin >> A >> B;
    forn(n2, 0, 30) forn(n3, 0, 19) if (pw(2, n2) * pw(3, n3) <= sqrt(B)) 
        forn(n5, 0, 13) forn(n7, 0, 11) if (pw(5, n5) * pw(7, n7) <= sqrt(B)) {
            ll px = pw(2, n2) * pw(3, n3) * pw(5, n5) * pw(7, n7);
            if (px > sqrt(B)) continue;
            forn(i, 1, 18) backtrack(i, px);
        }
    powx[0] = 1;
    forn(i, 1, 18) powx[i] = powx[i-1] * 10;
    ll ans = 0;
    forn(n2, 0, 30) forn(n3, 0, 19) if (pw(2, n2) * pw(3, n3) <= sqrt(B)) 
        forn(n5, 0, 13) forn(n7, 0, 11) if (pw(5, n5) * pw(7, n7) <= sqrt(B)) {
            ll px = pw(2, n2) * pw(3, n3) * pw(5, n5) * pw(7, n7);
            if (px > sqrt(B)) continue;
            ans += process( (A+px-1)/px, B/px , px);
        }
    cout << ans ;
    return 0;
}
