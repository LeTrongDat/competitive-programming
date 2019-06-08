/*
                Author: Le Trong Dat
                Idea: - Firstly, we can find the maximum distance for each node in the tree by dp. This is classic problem.
                      - Secondly, sort all the maximum distance of each node, then use 2 pointers to find the segment that has 
                      the difference between max and minimum does not exceed L.
                      - Now, we have an important observation: 
                            + if we can somehow dsu all node in this segment in O(1) or O(logN), then we will
                                be able to answer all queries in time limit. 
                            + if we sort all the maximum distance decreasingly, then we will add node in order from leaf to root.
                            => sort decreasingly, then use dsu, when we add a node, using dsu, and when we 
                                remove a node which is a leaf, then nothing happen from its set which 
                                is containing that node, only the size decrese 1.
*/
#include <bits/stdc++.h>
using namespace std;
#define ft                          first
#define nd                          second
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define ford(i, a, b)               for(int i=a; i>=b; --i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
#define repd(i, a, b)               for(int i=(int)a-1; i>=b; --i)
typedef long long llong;
typedef pair<int, int> ii;
const int N=1e5 +100;
const llong inf=1e17;
int n;
int res;
llong ou[N], in[N][3];
vector<ii> adj[N];
ii lab[N];
pair<llong, llong> dist[N];
bool flag[N];
void inSubTree(int u, int par=0)
{
    in[u][1]=0;
    in[u][2]=-inf;
    for(auto &cur: adj[u]) 
    {
        llong v=cur.ft, d=cur.nd;
        if (v==par) continue;
        inSubTree(v, u);
        if (in[u][1]<in[v][1]+d) 
        {
            in[u][2]=in[u][1];
            in[u][1]=in[v][1]+d;
        } else in[u][2]=max(in[u][2], in[v][1]+d);
    }
}
void ouSubTree(int u, int par, int dist)
{
    if (par)
    {
        ou[u]=max(ou[u], ou[par]+dist);
        if (in[u][1]+dist==in[par][1]) ou[u]=max(ou[u], in[par][2]+dist);
            else ou[u]=max(ou[u], in[par][1]+dist);
    }
    for(auto &cur: adj[u]) if (cur.ft!=par) ouSubTree(cur.ft, u, cur.nd);
}
int root(int u)
{
    if (lab[u].ft==u) return u;
    return lab[u].ft=root(lab[u].ft);
}
void remove(int u)
{
    flag[u]=false;
    int lab1=root(u);
    lab[lab1].nd --;
}
void add(int u)
{
    flag[u]=true;
    for(auto &cur: adj[u])
    {
        int v=cur.ft;
        if (flag[v])
        {
            int lab1=root(u), lab2=root(v);
            if (lab[lab1].nd<lab[lab2].nd) swap(lab1, lab2);
            lab[lab1].nd+=lab[lab2].nd;
            res=max(res, lab[lab1].nd);
            lab[lab2]={lab[lab1].ft, lab[lab2].nd};
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    repn(i, 1, n)
    {
        int u, v, d;
        cin>>u>>v>>d;
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }
    inSubTree(1);
    ouSubTree(1, 0, 0);
    forn(i, 1, n) dist[i]={max(ou[i], in[i][1]), i};
    sort(dist+1, dist+n +1);
    reverse(dist +1, dist +n+ 1);
    int query; cin>>query;
    for(llong l; query; --query)
    {
        forn(i, 1, n) { lab[i]={i, 1}; flag[i]=false; }
        cin>>l;
        int itr=1;
        res=1;
        forn(i, 1, n) 
        {
            if (i>1) remove(dist[i-1].nd);
            while (itr<=n && dist[i].ft-dist[itr].ft <=l) add(dist[itr++].nd);
        }
        cout<<res<<'\n';
    }
}