/*
    Author: Le Trong Dat.
    Idea: - For each depth from u to each child of u, maintaining the left most and the right most 
        from sign '+' of u.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
#define ford(i, a, b)           for(int i=a; i>=b; --i)
typedef pair<int, int> i2;
#define le first
#define ri second
const int N = 3e5 + 10;
long long ans = 0;
int n;
string s[N];
int a[N], add_le[N], add_ri[N];
vector<int> e[N];
deque< i2 > dq[N];
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    cin >> s[1];
    forn(i, 2, n) {
        int u; 
        cin >> s[i] >> u;
        e[u].push_back(i);
    }
    forn(i, 1, n) {
        a[i] = s[i].size() + 2;
        ans += a[i] * 3;
    }
    ford(u, n, 1) {
        int m = (a[u] + 1) / 2;
        if (e[u].size() == 2) {
            int v1 = e[u][0], v2 = e[u][1];
            int dist = 3;
            for(int i=0; i<min(dq[v1].size(), dq[v2].size()); ++i) 
                dist = max(dist, dq[v1][i].ri + add_ri[v1] + add_le[v2] + dq[v2][i].le);
            dist /= 2;
            ans += dist * 2 + 6;
            if (dq[v1].size() > dq[v2].size()) {
                dq[u] = move(dq[v1]);
                add_ri[u] = add_ri[v1] - (1 + dist);
                add_le[u] = add_le[v1] + (1 + dist);
                for(int i=0; i<dq[v2].size(); ++i) 
                    dq[u][i].ri = dq[v2][i].ri + add_ri[v2] + 1 + dist - add_ri[u];
            } else {
                dq[u] = move(dq[v2]);
                add_ri[u] = add_ri[v2] + (1 + dist);
                add_le[u] = add_le[v2] - (1 + dist);
                for(int i=0; i<dq[v1].size(); ++i) 
                    dq[u][i].le = dq[v1][i].le + add_le[v1] + 1 + dist - add_le[u];
            }
        }
        if (e[u].size() == 1) {
            int v1 = e[u][0];
            ans += 3;
            dq[u] = move(dq[v1]);
            add_le[u] = add_le[v1];
            add_ri[u] = add_ri[v1];
        }
        dq[u].push_front({m-1-add_le[u], a[u]-m-add_ri[u]});
    }
    cout << ans;
    return 0;
}
