/*
        Author: Le Trong Dat.
        Problem: CF187_D1_C.
        Idea: 
            - Binary Search + Dijkstra. 
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
const int N=2e5 +100;
int n, m, k;
int location, destination;
bool volunteer[N];
int reach[N];
vector<int> adj[N];
void read()
{
    // read input
    cin>>n>>m>>k;
    forn(i, 1, k) 
    {
        int position; cin>>position;
        volunteer[position]=true;
    }
    forn(i, 1, m) 
    {
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin>>location>>destination;
}
bool go(int limit)
{
    forn(i, 1, n) reach[i]=m+1; // initialize value of reach 
    // Dijkstra 
    #define ii pair<int, int>
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push({0, location});
    reach[location]=0;
    while (pq.size())
    {
        auto current=pq.top();
        pq.pop();
        if (reach[current.second]<current.first || current.first==limit) continue;
        for(auto &v: adj[current.second]) if (reach[v]>current.first+1)
        {
            reach[v]=(volunteer[v]?0:current.first+1);
            pq.push({reach[v], v});
        }
    }
    return (reach[destination]<=limit); // if can reach the destination with reach[value] != initial value, 
                                        // then there is a way from begin to destination
}
void process()
{
    int lo=0, hi=m, rez=-1;

    // Binary Search
    while (lo<=hi) 
    {
        int mid=lo+hi>>1;
        if (go(mid)) { rez=mid; hi=mid-1; } else lo=mid+1;
    }
    cout<<rez;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    read();
    process();
    return 0;
}
