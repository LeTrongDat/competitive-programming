/*
                Author: Le Trong Dat.
                Idea: - We come up to solution with dp.
                      - Let's dp[i][k] means the numbers of distinct arrays which has length k and ending is a[i];
                      => dp[i][k]= sum(dp[j][k-1]) (j<i && a[j]<a[i]) => we can use segment tree for updating and query sum value.
                      - Observation: if (i>j && a[i]==a[j]) => dp[i][k]==d[j][k] => when we meet value which appeared before, we 
                        re-update in segment tree value of dp[][];
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)                   for(int i=a; i<=b; ++i)
#define ford(i, a, b)                   for(int i=a; i>=b; --i)
#define repn(i, a, b)                   for(int i=a; i <b; ++i)
typedef long long llong;
const int N=1e4 +10;
const llong MOD=5e6;
int n, k;
vector<int> s;
int a[N];
struct SegmentTree
{
    llong sum[4*N];
    void update(int x, int l, int r, int i, int v)
    {
        if (i>r || i<l) return;
        if (l==r)
        {
            sum[x]=v;
            return;
        }
        int mid=l+r>>1;
        update(2*x, l, mid, i, v);
        update(2*x+1, mid+1, r, i, v);
        sum[x]=(sum[2*x]+sum[2*x+1])%MOD;
    }
    llong query(int x, int l, int r, int i)
    {
        if (l>i) return 0;
        if (r<=i) return sum[x];
        int mid=l+r>>1;
        return (query(2*x, l, mid, i) + query(2*x+1, mid+1, r, i)) % MOD;
    }
} st[55];
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>k;
    s.resize(n);
    repn(i, 0, n) { cin>>s[i]; a[i]=s[i]; }
    sort(s.begin(), s.end());
    s.resize(unique(s.begin(), s.end()) -s.begin());
    repn(i, 0, n) a[i]=lower_bound(s.begin(), s.end(), a[i]) - s.begin() +1;
    st[0].update(1, 0, n, 0, 1);
    repn(i, 0, n) ford(seg, k, 1) 
    {
        llong x=st[seg-1].query(1, 0, n, a[i]-1); 
        st[seg].update(1, 0, n, a[i], x);
    }
    cout<<st[k].query(1, 0, n, n);
}