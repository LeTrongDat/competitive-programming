/*
        Author: Le Trong Dat.
        Idea: - Dijkstra, but instead of using dijsktra from 1 source like usual, we push in priority queue many sources
                then run dijkstra.
              - Check all edges (x, y) . The answer is Min(dist[x]+dist[y]+w(x, y)).
*/
#include <bits/stdc++.h>
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
const int N=1e5 +100;
const ll inf=1e15;
int n, m, v1, v2;
bool gang[N];
ll dist[N], res=inf;
vector<ii> adj[N];
priority_queue<ii, vector<ii>, greater<ii>> pq;
int from[N];
struct Edge 
{
    ll u, v, w;
    Edge(){};
    Edge(ll u, ll v, ll w) : u(u), v(v), w(w) {};
} edge[N];
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    memset(dist, 0x3f, sizeof dist);
    forn(i, 1, n) 
    {
        cin>>gang[i];
        if (gang[i]) 
        {
            from[i]=i;
            dist[i]=0;
            pq.push({0, i});
        }
    }
    forn(i, 1, m)
    {
        ll u, v, w; cin>>u>>v>>w;
        edge[i]={u, v, w};
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    while (pq.size())
    {
        auto cur=pq.top();
        pq.pop();
        ll u=cur.second, d=cur.first;
        if (dist[u]<d) continue;
        for(auto &nxt: adj[u])
        {
            int v=nxt.first;
            ll w=nxt.second;
            if (dist[v]>d+w) 
            {
                dist[v]=d+w;
                from[v]=from[u];
                pq.push({dist[v], v});
            }
        }
    }
    forn(i, 1, m)
    {
        int u=edge[i].u, v=edge[i].v, w=edge[i].w;
        if (res>dist[u]+dist[v]+w && from[u]!=from[v]) 
        {
            res=dist[u]+dist[v]+w;
            v1=from[u]; v2=from[v];
        }
    }
    if (res>=inf) cout<<"No luck at all"; else cout<<res<<'\n'<<v1<<' '<<v2;
}
