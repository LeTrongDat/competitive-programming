/*
    Author: Le Trong Dat
    Idea: http://www.usaco.org/current/data/sol_sort_gold_open18.html
*/
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int N = 1e5 + 10;;
int n, b[N], bit[N];
pair < int, int > a[N];
void update(int x) { for(; x > 0; x -= x & -x) bit[x] ++; }
int query(int x, int sum = 0) { for(; x < N; x += x & -x) sum += bit[x]; return sum; }
int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin >> n;
    for(int i=1; i<=n; ++i) { cin >> a[i].x; a[i].y = i; }
    sort(a+1, a+n +1);
    for(int i=1; i<=n; ++i) b[a[i].y] = i;
    int ans = 1;
    for(int i=1; i< n; ++i) {
        update(b[i]);
        ans = max(ans, query(i+1));
    }
    cout << ans;

    return 0;
}