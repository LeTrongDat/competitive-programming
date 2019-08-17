/*
    Author: Le Trong Dat
    Idea: Consider characters from large to small. Use deque to save the height of each row 
    (the height of a row is the position of the last row containing the character> = the character that we are considering).
    * Note : Use array instead of deque to optimize.
*/

#include <bits/stdc++.h>
using namespace std;
#define x  first
#define y  second
#define pb push_back
#define forn(i, a, b)   for(int i=a; i<=b; ++i)
#define ford(i, a, b)   for(int i=a; i>=b; --i)
typedef pair<int, int> ii;
const int N = 1010;
const int INF = 1e8;
int n;
int h[N];
char ch[N][N];
int sz; 
pair < int, char > st[N];
int main() {
    ios::sync_with_stdio(0);
    freopen("ssdj.in", "r", stdin);
    freopen("ssdj.out", "w", stdout);
    cin >> n;
    forn(i, 1, n) forn(j, 1, n) cin >> ch[i][j];
    long long ans = 0;
    ford(c, 'z', 'a') {
        forn(i, 1, n) h[i] = 0;
        forn(i, 1, n) {
            int cnt = 0;
            sz = 0;
            forn(j, 1, n) {
                while (sz && st[sz].first <= h[j]) {
                    cnt -= (st[sz].second == c);
                    sz --;
                }
                if (ch[i][j] == c) {
                    ans += sz - cnt;
                    if (sz && st[1].first == i && st[1].second != c) ans --;
                }
                if (ch[i][j] >= c) h[j] = i;
                while (sz && st[sz].first <= h[j]) {
                    cnt -= (st[sz].second == c);
                    sz --;
                }
                if (h[j]) {
                    cnt += (ch[h[j]][j] == c);
                    st[++sz] = {h[j], ch[h[j]][j]};
                }
            }
        }
        forn(i, 1, n) h[i] = n+1;
        ford(i, n, 1) {
            sz = 0;
            ford(j, n, 1) {
                while (sz && st[sz].first >= h[j]) sz --;
                if (ch[i][j] == c) {
                    ans += sz;
                    if (sz && st[1].first == i) ans --;
                }
                if (ch[i][j] >= c) h[j] = i;
                while (sz && st[sz].first >= h[j]) sz --;
                if (h[j] != n+1) st[++sz] = {h[j], 'a'};
            }
        }
    }
    cout << ans << '\n';
}
