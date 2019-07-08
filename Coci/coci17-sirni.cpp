/*
    Author: Le Trong Dat.
    Idea: http://hsin.hr/coci/archive/2016_2017/.
    Contest 6. Problem 5.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define ford(i, a ,b)               for(int i=a; i>=b; --i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
typedef pair<int, int> ii;
const int maxM = 1e7+ 10;
const int maxN = 1e5 +10;
int N;
int Near[maxM];
int lab[maxN];
bool flag[maxM];
vector<int> P;
vector<ii> Edge[maxM];
int root(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = root(lab[u]);
}
bool join(int u, int v) {
    int l1 = root(u), l2 = root(v);
    if (l1 == l2) return false;
    if (lab[l1] > lab[l2]) swap(l1, l2);
    lab[l1] += lab[l2];
    lab[l2] = l1;
    return true;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(lab, -1, sizeof lab);
    cin >> N;
    P.resize(N);
    repn(i, 0, N) cin >> P[i];
    sort(P.begin(), P.end());
    P.resize(unique(P.begin(), P.end()) - P.begin());
    memset(Near, 0x3f, sizeof Near);
    repn(i, 0, P.size()) Near[P[i]] = i;
    ford(i, P.back(), 0) Near[i] = min(Near[i], Near[i+1]);
    repn(i, 0, P.size() -1) {
        int weight = P[Near[P[i]+1]] - P[i];
        Edge[weight].push_back({i, Near[P[i]+1]});
        if (!flag[P[i]]) for(int j = 2*P[i]; j <= P.back(); j += P[i]) {
            flag[j] = true;
            Edge[P[Near[j]] - j].push_back({i, Near[j]});
        }
    }
    long long result = 0;
    repn(i, 0, maxM) {
        for(auto &e: Edge[i]) result += join(e.first, e.second) * i;
    }
    cout << result;
}
