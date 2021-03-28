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
int N, T, Q;
int response() {
    int res; cin >> res;
    if (res == -1) exit(0);
    return res;
}
namespace tester {
    vector<int> permutation;
    int num_ques;
    void generate() {
        permutation.clear();
        forn(i, 1, N) permutation.eb(i);
        shuffle(permutation.begin(), permutation.end(), rng);
    }
    int ask(int i, int j, int k) {
        num_ques ++;
        if (num_ques > Q) {
            cerr << "Number of queries exceed\n";
            exit(0);
        }
        int pi, pj, pk;
        repn(u, 0, N) {
            if (permutation[u] == i) pi = u;
            if (permutation[u] == j) pj = u;
            if (permutation[u] == k) pk = u;
        }
        if ((pj < pi and pi < pk) or (pj > pi and pi > pk)) return i;
        if ((pi < pj and pj < pk) or (pi > pj and pj > pk)) return j;
        return k;
    }
}


namespace sub2 {
    auto solve() {
        vector<int> permutation; forn(i, 1, N) permutation.eb(i);
        rng.seed(chrono::steady_clock::now().time_since_epoch().count());
        shuffle(permutation.begin(), permutation.end(), rng);
        vector<int> vt = {permutation[0], permutation[1], permutation[2]};
        cout << permutation[0] << ' ' << permutation[1] << ' ' << permutation[2] << endl;
        int res = response();
        if (res == permutation[0]) swap(vt[0], vt[1]); 
        if (res == permutation[2]) swap(vt[1], vt[2]);
        repn(i, 3, permutation.size()) {
            int new_one = permutation[i];
            int lo = 0, hi = vt.size() - 1;
            while (lo <= hi) {
                if (lo + 2 == hi) {
                    cout << vt[lo] << ' ' << vt[lo+1] << ' ' << new_one << endl;
                    int res = response();
                    if (res == vt[lo]) { vt.insert(vt.begin() + lo, new_one); break; }
                    if (res == new_one) { vt.insert(vt.begin() + lo + 1, new_one); break; }
                    lo = lo + 1;
                    continue;
                }
                if (lo + 1 == hi) {
                    cout << vt[lo] << ' ' << vt[hi] << ' ' << new_one << endl;
                    int res = response();
                    if (res == vt[lo]) { vt.insert(vt.begin() + lo, new_one); break; }
                    if (res == vt[hi]) { vt.insert(vt.begin() + hi + 1, new_one); break; } 
                    vt.insert(vt.begin() + hi, new_one);
                    break;
                }

                int m1 = (2 * lo + hi) / 3;
                int m2 = (lo + 2 * hi) / 3;
                cout << vt[m1] << ' ' << vt[m2] << ' ' << new_one << endl;
                int res = response();
                if (res == vt[m1]) {
                    hi = m1; 
                }
                if (res == vt[m2]) { 
                    lo = m2;
                }
                if (res == new_one) { 
                    if (m1 + 1 == m2) { vt.insert(vt.begin() + m2, new_one); break; }
                    lo = m1; hi = m2; 
                };
            }
        }
        return vt;
    }
}
int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T >> N >> Q;
    forn(i, 1, T) {
        auto ans = sub2::solve();
        for(auto x: ans) cout << x << ' ';
        cout << endl;
        int res = response();
    }
    return 0;
}
