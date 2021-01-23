#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define repn(i, a, b)       for(int i = a; i < b; ++i)
#define repd(i, a, b)       for(int i = (int)a - 1; i >= b; --i)
const int N = 1e6 + 10;
int cnt[N];
void init(vector<int> &a) {
    for(auto x: a) cnt[x] ++;
}
void clear(vector<int> &a) {
    for(auto x: a) cnt[x] = 0;
}
bool check(int x, vector<int> &a, vector<tuple<int, int>> &track) {
    repd(i, a.size(), 0) {
        while (cnt[a[i]]) {
            if (cnt[x-a[i]]) {
                cnt[a[i]] --;
                cnt[x-a[i]] --;
                track.emplace_back(a[i], x-a[i]);
                x = a[i];
                continue;
            } 
            return false;
        }
    }
    return true;
}
void print(int x, vector<tuple<int, int>> &track) {
    cout << "YES\n";
    cout << x << '\n';
    for(auto step: track) {
        cout << get<0>(step) << ' ' << get<1>(step) << '\n';
    }
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; 
    cin >> ntest;
    for(; ntest; ntest --) {
        int n; 
        cin >> n;
        n *= 2;
        vector<int> a(n);
        repn(i, 0, n) cin >> a[i];
        sort(a.begin(), a.end());
        bool res = false;
        repn(i, 0, n-1) {
            vector<tuple<int, int>> track;
            int x = a.back() + a[i];
            init(a);
            if (check(x, a, track)) {
                res = true;
                print(x, track);
                break;
            }
            clear(a);
        }
        if (!res) cout << "NO\n"; 
    }
    return 0;
}
