/*
        Author: Le Trong Dat
        Idea: 
            - For each query, we call method Dfs(i, j, D) = the maximum distance 
            if we reach (i, j) with direction D. 
            we can jump to the next cross in O(logN) by using sparse table.
            row[i][j] = maximum number from row i-th to row i+2^j-1 -th.
            Store all states which we passed by map.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)                   for(int i=a; i<=b; ++i)
#define ford(i, a, b)                   for(int i=a; i>=b; --i)
#define repn(i, a, b)                   for(int i=a; i <b; ++i)
#define repd(i, a, b)                   for(int i=(int)a-1; i>=b; --i)
const int maxLog = 19;
const int maxN = 5e4 +10;
int H, W, Q;
int A[maxN], B[maxN];
int pw[maxLog];
int col[maxN][maxLog], row[maxN][maxLog];
map< tuple<int, int, int>, long long > dp; 
int max(int a, int b, int c, int d) {
    return max( max(a, b), max(c, d) );
}
long long DFS(int cur_x, int cur_y, int dir) {
    tuple<int, int, int> cur_state = {cur_x, cur_y, dir};
    if (dp.count(cur_state)) return dp[cur_state];
    long long &ans = dp[cur_state];
    int sign, nxt, tmp;
    if (dir == 0 || dir == 1) {
        sign = (dir == 0 ? -1 : 1);
        nxt = -1;
        tmp = cur_x;
        ford(i, 16, 0) { 
            nxt = cur_x + pw[i] * sign - sign;
            if (nxt < 1 || nxt > H) continue;
            if ( (sign == 1 ? row[cur_x][i] : row[nxt][i]) > B[cur_y] ) continue;
            cur_x = nxt + sign;
        }
        if (cur_x < 1 || cur_x > H) {
            cur_x -= sign;
            return ans = abs(cur_x - tmp);
        }
        return ans = abs(cur_x - tmp) + max( DFS(cur_x, cur_y, 2), DFS(cur_x, cur_y, 3) );
    }
    sign = (dir == 2 ? -1 : 1);
    nxt = -1;
    tmp = cur_y;
    ford(i, 16, 0) {
        nxt = cur_y + pw[i] * sign - sign;
        if (nxt < 1 || nxt > W) continue;
        if ( (sign == 1 ? col[cur_y][i] : col[nxt][i]) > A[cur_x] ) continue;
        cur_y = nxt + sign;
    }
    if (cur_y < 1 || cur_y > W) {
        cur_y -= sign;
        return ans = abs(cur_y  - tmp);
    }
    return ans = abs(cur_y - tmp) + max( DFS(cur_x, cur_y, 0), DFS(cur_x, cur_y, 1) );
}
int main() {
    ios::sync_with_stdio(0);
    pw[0] = 1;
    forn(i, 1, 17) pw[i] = pw[i-1] * 2;
    cin >> H >> W >> Q;
    forn(i, 1, H) cin >> A[i];
    forn(i, 1, W) cin >> B[i];
    forn(i, 1, H) row[i][0] = A[i];
    forn(i, 1, W) col[i][0] = B[i];
    forn(lg, 1, 16) forn(i, 1, H-pw[lg]+1)
        row[i][lg] = max(row[i][lg-1], row[i+pw[lg-1]][lg-1]);
    forn(lg, 1, 16) forn(i, 1, W-pw[lg]+1) 
        col[i][lg] = max(col[i][lg-1], col[i+pw[lg-1]][lg-1]);
     for(int S, T; Q; Q--) {
         cin >> S >> T;
         long long ans = 0;
         if (S < H) ans = max(ans, DFS(S+1, T, 1) + 1);
         if (S > 1) ans = max(ans, DFS(S-1, T, 0) + 1);
         if (T < W) ans = max(ans, DFS(S, T+1, 3) + 1);
         if (T > 1) ans = max(ans, DFS(S, T-1, 2) + 1);
         cout << ans << '\n';
    }
    return 0;
}
