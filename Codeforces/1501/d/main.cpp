#include <bits/stdc++.h>
using namespace std;
#define eb                  emplace_back
#define llong               long long 
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define repn(i, a, b)       for(int i = a; i <  b; ++i)
 
#ifndef LOCAL 
#define cerr                if (0) cerr 
#endif 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
tuple<T, T> operator * (const tuple<T, T> &o, const T &k) {
    return make_tuple(get<0>(o) * k, get<1>(o) * k);
}

template<class T>
tuple<T, T> ext_euclid(const T &a, const T &b) {
    if (not b) return {1 / a, 0};

    auto tmp = ext_euclid(b, a % b);

    llong x, y;
    x = get<1>(tmp);
    y = get<0>(tmp) - a / b * get<1>(tmp);
    return {x, y};
}

bool valid(llong mi, vector<llong> &pos, llong k, const llong &LCM) {
    llong good_days = 0;
    for(auto p: pos) if (p != -1) {
        if (p > mi) continue;
        good_days += max(0LL, (mi - p) / LCM + 1);
    }
    return (mi + 1 - good_days >= k);
}

auto solve() {
    llong n, m, k; cin >> n >> m >> k;
    const llong GCD = gcd(n, m);
    const llong LCM = n * m / GCD;
    vector<llong> pos(2 * max(m, n) + 1, -1);
    vector<int> a(2 * max(m, n) + 1, -1), b(2 * max(m, n) + 1, -1);
    repn(i, 0, n) {
        int x; cin >> x;
        a[x] = i;
    }
    repn(i, 0, m) {
        int x; cin >> x;
        b[x] = i;
    }
    forn(i, 0, 2 * max(m, n)) if (a[i] != -1 and b[i] != -1) {
        llong x, y; x = a[i]; y = b[i];
        if ((x - y) % GCD) continue;
        llong a = n / GCD, b = m / GCD, g = (x - y) / GCD;
        tuple<llong, llong> sol = ext_euclid(b, -a);
        sol = sol * g;
        pos[i] = m * get<0>(sol) + y;
        pos[i] = (pos[i] % LCM + LCM) % LCM;
    }
    llong lo = 0, hi = 1e18, ans = -1;
    while (lo <= hi) {
        llong mi = (lo + hi) >> 1;
        if (valid(mi, pos, k, LCM)) {
            ans = mi;
            hi = mi - 1;
        } else lo = mi + 1;
    }
    return ans + 1;
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest = 1;
    for(; ntest --;) {
        auto ans = solve();
        cout << ans << '\n';
    }
    return 0;
}
