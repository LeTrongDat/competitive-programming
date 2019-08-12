/*
    Author: Le Trong Dat.
    Idea: 
        * If Takahashi doesn't move then so does Aoki => The game ends.
        => Takahashi always moves when it's possible.
        * Choose the column where game will end at => caculate the number of steps needed to reach 
        that column by simulate the way from cell(1, 1) to that column.
*/
#include <bits/stdc++.h>
using namespace std;
#define FORN(i, a, b)                   for(int i=a; i<=b; ++i)
#define pb                              push_back
const int N = 2e5 + 10;
int h, w, n;
typedef pair< int, int > pr;
map < pr, bool > block;
vector < int > col[N];
int main() {
    ios::sync_with_stdio(0);
    cin >> h >> w >> n;
    FORN(i, 1, n) {
        int x, y;
        cin >> x >> y;
        block[{x, y}] = true;
        col[y].pb(x);
    }
    FORN(i, 1, w) { col[i].pb(h+1); block[{h+1, i}] = true; }
    FORN(i, 1, h) sort(col[i].begin(), col[i].end());
    int ans = 1e6;
    for(int x = 1, y = 1, steps = 0; x <= h && y <= w;) {
        if (block[{x+1, y}]) { steps ++; ans = min(ans, steps); break; }
        auto nxt = *lower_bound(col[y].begin(), col[y].end(), x);
        ans = min(ans, steps + nxt - x);
        x ++; steps ++;
        while (x < nxt && y < w && block[{x, y+1}]) { steps ++; x++; }
        if (x < nxt) y++;
    }
    cout << ans;
}
