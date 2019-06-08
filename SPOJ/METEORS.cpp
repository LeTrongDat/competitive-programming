#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL N = 3 * (LL) 1e5 + 10;
LL low[N], high[N], n, m, res[N], tg[N], k, l[N], r[N], a[N], f[N];
vector<LL> DS[N], adj[N];
void up(LL i, LL val) {
    while (i < N) { f[i] += val; i += i & -i; }
}
LL query(LL i) {
    LL sum = 0;
    while (i > 0) { sum += f[i]; i -= i & -i; }
    return sum;
}
void update(LL left, LL right, LL val) {
    if (left <= right) {
        up(left, val);
        up(right + 1, -val);
        return;
    }
    update(left, m, val);
    update(1, right, val);
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #ifdef LTD
        freopen("METEORS.inp","r",stdin);
        freopen("METEORS.out","w",stdout);
    #endif // LTD

    cin >> n >> m;
    for(LL i = 1; i <= m; ++i) {
        LL inx;
        cin >> inx;
        DS[inx].push_back(i);
    }
    for(LL i = 1; i <= n; ++i) cin >> tg[i];
    cin >> k;
    for(LL i = 1; i <= n; ++i) { low[i] = 1; high[i] = k; }
    for(LL i = 1; i <= k; ++i) cin >> l[i] >> r[i] >> a[i];
    while (true) {
        bool check = 0;
        for(LL i = 0; i <= k; ++i) adj[i].clear();
        for(LL i = 1; i <= n; ++i)
            if (low[i] <= high[i]) {
                LL mid = low[i] + high[i] >> 1;
                adj[mid].push_back(i);
            }
        memset(f, 0, sizeof(f));
        for(LL i = 1; i <= k; ++i) {
            update(l[i], r[i], a[i]);
            for(LL j = 0; j < adj[i].size(); ++j) {
                check = 1;
                LL inx = adj[i][j];
                LL ans = 0;
                for(LL it = 0; it < DS[inx].size(); ++it) if (ans + query(DS[inx][it]) < (LL) 1e15) ans += query(DS[inx][it]);
                if (ans >= tg[inx]) {
                    res[inx] = i;
                    high[inx] = i - 1;
                }
                else low[inx] = i + 1;
            }
        }
        if (!check) break;
    }
    for(LL i = 1; i <= n; ++i) {
        if (res[i]) cout << res[i]; else cout << "NIE";
        cout << '\n';
    }

    return 0;
}
