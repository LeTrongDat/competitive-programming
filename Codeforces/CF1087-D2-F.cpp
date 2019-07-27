/*
    Author: Le Trong Dat.
    Idea:
    In shortly: 
        * Call lose (i) is the type to lose i-th type and win (i) is 
            the type that wins type i-th
            Lose (P) = R, Win (P) = S
            Lose (R) = S, Win (R) = P
            Lose (S) = P, Win (S) = R
        * A[i] wins all the candidates on the left 
            <=> Or has lose(a(i)) on the left or does not exist win(a(i)) on the left (the same is on the right).
            In other words, A(i) loses <=> There is no lose(a(i)) on the left and there exists win(a(i)) on the left a(i).
            <=> a(i) is between leftmost(win(a(i)) and leftmost(lose(a(i)) (Same with the rightmost).
    In details: 
        https://codeforces.com/blog/entry/64078
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)                   for(int i=a; i<=b; ++i)
#define ford(i, a, b)                   for(int i=a; i>=b; --i)
const int N = 2e5 +10;
int n, q;
string s;
int a[N];
int bit[3][N];
int convertToNumber(char c) {
    if (c == 'R') return 0;
    if (c == 'P') return 1;
    return 2;
}
void update(int x, int ki, int v) {
    for(; x < N; x += x & -x) bit[ki][x] += v;
}
int query(int x, int ki, int tot = 0) {
    for(; x > 0; x -= x & -x) tot += bit[ki][x];
    return tot;
}
int pos(int ki, int upbound) {
    long long tot = 0, cur = 0;
    ford(lg, 18, 0) if (cur+(1 << lg) <= n && tot + bit[ki][cur+ (1 << lg)] < upbound) {
        cur += (1 << lg);
        tot += bit[ki][cur];
    }
    return cur + 1;
}
int leftmost(int ki) { return pos(ki, 1); }
int rightmost(int ki) { return pos(ki, query(n, ki)); }
int win(int i) { return (i+1) % 3; }
int lose(int i) { return (i+2) % 3; }
int winers() {
    forn(i, 0, 2) if (query(n, i) == n) return n;
    forn(i, 0, 2) if (query(n, i) == 0) {
        if (i == 0) return query(n, 2);
        if (i == 1) return query(n, 0);
        return query(n, 1);
    }
    int ans = 0;
    forn(i, 0, 2) {
        int x1, x2;
        x1 = leftmost(win(i));
        x2 = leftmost(lose(i));
        //cout << i << ' ' << x1 << ' ' << x2 << '\n';
        if (x1 < x2) ans += query(x2-1, i) - query(x1, i);
        x1 = rightmost(win(i));
        x2 = rightmost(lose(i));
        if (x1 > x2) ans += query(x1-1, i) - query(x2, i);
    }
    return n-ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n >> q >> s;
    forn(i, 1, n) a[i] = convertToNumber(s[i-1]);
    forn(i, 1, n) update(i, a[i], +1);
    cout << winers() << '\n';
    forn(i, 1, q) {
        int idx, kin; char c;
        cin >> idx >> c;
        kin = convertToNumber(c);
        update(idx, a[idx], -1);
        update(idx, kin, +1);
        a[idx] = kin;
        cout << winers() << '\n';
    }
}
