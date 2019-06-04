#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)   for(int i=a; i<=b; ++i)
const int N=3e6 +100;
int m;
long long n;
long long ans[N], a[N], s[N];
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long limit=3e6+1;
    cin>>n;
    forn(i, 1, n) 
    {
        int x; cin>>x; a[x] ++;
    }
    forn(i, 1, limit) s[i]=s[i-1]+a[i];
    ans[limit]=n*(n-1);
    forn(i, 1, limit-1) 
    {
        int x=ceil((double)limit / i) -1;
        ans[limit]-=a[i]*(i<=x?s[x]-1:s[x]);
    }
    forn(i, 1, limit-1)
    {
        for(int j=i; j<limit; j+=i) 
        {
            int y=j/i;
            long long add=(y==i ? a[i]*(a[i]-1) : a[i]*a[y]);
            ans[j]+=add;
        }
    }
    for(int i=limit-1; i>=0; --i) ans[i]+=ans[i+1];
    cin>>m;
    forn(i, 1, m) 
    {
        int x; cin>>x; cout<<ans[x]<<'\n';
    }
}