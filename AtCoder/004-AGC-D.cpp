/*
    Author: Le Trong Dat
    Idea: 
        * a(1) is always 1 => if a(1) != 1 then change a(1) = 1;
        * When we reverse edge from i->a[i], the graph will be a tree.
        * Height[u] = maximum distance from its children to it. If 
        height[u] == k-1 and par[u] != 1 then we must split subtree u.
        => The number of tree after split -1 = answer
*/

#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
const int N = 1e5 + 10;
int n, k;
int cnt;
int height[N], a[N];
vector<int> e[N];
void dfs(int u, int p = 0) {
    height[u] = 0;
    for(auto v: e[u]) {
        dfs(v, u);
        height[u] = max(height[u], height[v] + 1);
    }
    if (u != 1 && height[u] == k-1 && p != 1) {
        cnt ++;
        height[u] = -1;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    cnt = 0;
    forn(i, 1, n) cin >> a[i];
    if (a[1] != 1) { cnt ++; a[1] = 1; }
    forn(i, 2, n) e[a[i]].push_back(i);
    dfs(1);
    cout << cnt;
    return 0;
}
