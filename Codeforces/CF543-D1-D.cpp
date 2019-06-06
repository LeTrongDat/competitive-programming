/*
            Author: Le Trong Dat.
            Idea: DP in tree.
                 - Dp(i) is the number of ways to assign the value of each road (bad/good) satisfies the requirement.
                 - DP(u) = Dp(u) * (Dp(v) +1) (v is direct child of u);
                 - Answer for node 1 is dp(1);
                 - How can we find the answers for all node :
                    + Go on the tree, if I am currently at the node u and par is parent of u,
                     update the result of par when there is no node u and update the result of node u when par is a child.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)                       for(int i=a; i<=b; ++i)
#define ford(i, a, b)                       for(int i=a; i>=b; --i)
#define repn(i, a, b)                       for(int i=a; i <b; ++i)
#define repd(i, a, b)                       for(int i=(int)a-1; i>=b; --i)
typedef long long ll;
const ll MOD=1e9+ 7;
const int N=2e5 +10;
int n;
ll dp[N], ans[N];
vector<int> adj[N];
vector<ll> suffix[N], prefix[N];
ll pw(ll a, ll q)
{
    if (q==0) return 1;
    ll tmp=pw(a, q>>1);
    tmp=(tmp*tmp)%MOD;
    if (q&1) tmp=(tmp*a)%MOD;
    return tmp;
}
void dfs(int u)
{
    int m=adj[u].size();
    dp[u] = 1;
    forn(i, 1, m) dfs(adj[u][i-1]);
    suffix[u].resize(m+1);
    prefix[u].resize(m+2);
    forn(i, 1, m)
    {
        int v=adj[u][i-1];
        dp[u]=dp[u] * (dp[v] + 1) %MOD;
    }
    suffix[u][0]=prefix[u][m+1]=1;
    forn(i, 1, m) suffix[u][i]=suffix[u][i-1] * (dp[adj[u][i-1]] +1) % MOD;
    ford(i, m, 1) prefix[u][i]=prefix[u][i+1] * (dp[adj[u][i-1]] +1) % MOD;
}
void go(int u, ll par)
{
    ans[u]=dp[u];
    forn(i, 1, adj[u].size())
    {   
        int v=adj[u][i-1];
        ll tmp=par * suffix[u][i-1] % MOD* prefix[u][i+1] % MOD;
        dp[v]=dp[v] * (tmp + 1) % MOD;
        go(v, (tmp+1)%MOD);
    }
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    forn(i, 2, n)
    {
        int p; cin>>p; 
        adj[p].push_back(i);
    }
    dfs(1);
    go(1, 1);
    forn(i, 1, n) cout<<ans[i]<<' ';
}
