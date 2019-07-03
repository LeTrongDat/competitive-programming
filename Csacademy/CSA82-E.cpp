/*
        Author: Le Trong Dat.
        Idea: In a connected component, the best option is to build a fountain at the vertex with the smallest cost.
            The most optimal connected component must be a tree.
        => The most optimal construction method will include multiple connected components 
            where the value of each connected component = the cost of edge construction + the cost of building a fountain.
            Suppose we have a set of connected components (a1, a2, .., an)
        When adding an edge from ai -> aj, cost will be added = the cost of the edge - the cost of building 
            a fountain in one of the two components (because each connected component, we only needs one fountain is enough)
        => Dsu => Add each edge with the smallest cost (initially N vertices will be n connected components).
        After adding an edge, we will update the edge set according to the 
        representative vertex of that connected component (the vertex has the smallest cost of building fountain).
*/
#include <bits/stdc++.h>
using namespace std;
#define llong                   long long 
#define ii                      pair<llong, llong>
#define i3                      pair<llong, ii>
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
const int N = 2010;
int n, k, e;
llong f[N], lab[N];
llong edge[N][N], costEdge[N][N];
llong sum;
bool isExist[N][N];
vector<int> adj[N];
priority_queue<i3, vector<i3>, greater<i3>> pq;
int root(int u)
{
    if (lab[u] == u) return u;
    return lab[u] = root(lab[u]);
}
int main()
{
    ios::sync_with_stdio(false);
    int Test; 
    cin >> Test;
    int itest = 0;
    for(; Test; Test--)
    {
        itest ++;
        cin >> n >> k;
        e = sum = 0;
        while (pq.size()) pq.pop();
        forn(i, 1, n) lab[i] = i;
        forn(i, 1, n) 
        {
            cin >> f[i];
            sum += f[i];
        }
        forn(i, 1, n) forn(j, 1, n) 
        {
            cin >> edge[i][j];
            isExist[i][j] = true;
            if (i<j)
            {
                costEdge[j][i] = costEdge[i][j] = edge[i][j] - max(f[i], f[j]);
                int u = i, v = j;
                if (f[u] > f[v]) swap(u, v);
                pq.push({costEdge[i][j], {u, v}});
            }
        } 
        forn(i, 1, n) isExist[i][i] = false;
        for(int i=1; pq.size();)
        {
            auto ss = pq.top();
            pq.pop();
            int cost = ss.first, u = ss.second.first, v = ss.second.second;
            if (root(u) != u || root(v) != v) continue;
            if (i>n-k && cost>=0) break;
            i ++;
            sum += cost;
            isExist[u][v] = isExist[v][u] = false;
            lab[v] = u;
            forn(j, 1, n) if (isExist[v][j])
            {
                isExist[v][j] = isExist[j][v] = false;
                if (costEdge[u][j] > edge[v][j] - max(f[u], f[j]))
                {
                    edge[u][j] = edge[j][u] = edge[v][j];
                    costEdge[j][u] = costEdge[u][j] = edge[u][j] - max(f[u], f[j]);
                    pq.push({costEdge[u][j], {f[u]<=f[j]?u:j, f[u]>f[j]?u:j}});
                }
            }
        }
        cout << sum << '\n';
    }
}
