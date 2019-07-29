/*
    Author: Le Trong Dat
    Idea: 
        * We will count the number of convex polygons that do not contain point P.
        * For each point i, find the farthest point called F where CCW(point [i], p, F)> = 0.
        => If we choose k-1 points left from i -> F, we will get 1 set of convex polygons 
        that do not contain point P (or have P on the edge).
        Amount = C (k-1, X-1) with X being the number of points from i-> F.
*/
#include <bits/stdc++.h>
using namespace std;
#define x               first
#define y               second
#define repn(i, a, b)   for(int i=a; i<b; ++i)
typedef long long llong;
typedef pair<llong, llong> Point;
const int N = 1e5 + 10;
const int MOD = 1e9 +7;
Point p[N], a;
int n, k;
llong gt[N], in[N];
llong pw(llong x, llong q) {
    if (q == 0) return 1;
    llong tmp = pw(x, q>>1);
    tmp = (tmp * tmp) % MOD;
    if (q & 1) tmp = (tmp * x) % MOD;
    return tmp;
}
llong C(llong k, llong n) {
    if (k > n) return 0;
    return gt[n] * in[k] % MOD * in[n-k] % MOD;
}
bool CCW(Point a, Point b, Point c) {
    llong u1 = b.x - a.x, v1 = b.y - a.y;
    llong u2 = c.x - b.x, v2 = c.y - b.y;

    return (u1 * v2 - u2 * v1 > 0);
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n >> k;
    gt[0] = in[0] = 1;
    repn(i, 1, n+1) {
        gt[i] = (gt[i-1] * i) % MOD;
        in[i] = (in[i-1] * pw(i, MOD-2)) % MOD;
    }
    repn(i, 0, n) cin >> p[i].x >> p[i].y;
    cin >> a.x >> a.y;
    int now = 2, le = 0;
    llong ans = 0;
    repn(i, 0, n) {
        now --;
        while ( (le + 1) % n != i && !CCW(p[i], a, p[(le+1)%n])) {
            le = (le + 1) % n;
            now ++;
        }
        ans = (ans + C(k-1, now-1)) % MOD;
    }
    ans = (C(k, n) - ans + MOD) % MOD;
    cout << ans;
}
