/*
            Author: Le Trong Dat.
            Idea: - We have some observation:
                    + If a*b is perfect square && b*c is perfect square, then a*c is perfect square too.
                    After first observation, we divide array into some component, in which contains some 
                    numbers following the condition: Any two numbers in the array are perfect square.
                    + The second observation is after we divided, the problem change to : We must count the 
                    number of possible permutations satisfy there is no 2 numbers in the same component are
                    neighbor.
                => We come up to the solution dp[i][j] is the number of permutations of i first component and 
                have j "bad" neighbor ( "bad" neighbor is 2 number standing side by side).
                Then how can we do the trasition from dp[i][j] to i+1 ?
                - when we add S numbers from component i+1 we have some choices
                + Divide S into K subsegments, each subsegment have size >=1. => K<=min(S, total[i] +1).
                (total[i] is the sum of the first i component).
                + In K components, we can push each K components between total[i]+1 space.
                + Between each total[i]+1 space we have another choice that is in K space which we chosen, 
                we can take X which is between "bad" neighbor.
            => So we can fix the number K and the number X
            => the number of new "bad" neighbors is j-X + size_component[i+1] - K;
            => we can update state dp[i+1][j-X+size_component[i+1]-K] from dp[i][j].
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)                   for(int i=a; i<=b; ++i)
#define repn(i, a, b)                   for(int i=a; i <b; ++i)
const int MOD=1e9 +7;
const int N=310;
typedef long long llong;
int n, cntSet;
llong s[N], a[N], total[N];
llong gt[N], inv[N];
llong dp[N][N];
bool flag[N];
bool perfect(llong x)
{
    return ((llong)sqrt(x)*(llong)sqrt(x) == x);
}
void add(llong &a, llong b)
{
    a+=b;
    if (a>=MOD) a-=MOD;
}
llong C(llong k, llong n)
{
    return gt[n]*inv[k] %MOD*inv[n-k] %MOD;
}
llong pw(llong x, llong q)
{
    if (q==0) return 1;
    llong tmp=pw(x, q>>1);
    tmp=tmp*tmp%MOD;
    if (q&1) tmp=tmp*x%MOD;
    return tmp;
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    gt[0]=inv[0]=1;
    forn(i, 1, n) 
    {
        gt[i]=gt[i-1]*i%MOD;
        inv[i]=inv[i-1]*pw(i, MOD-2)%MOD;
    }
    forn(i, 1, n) cin>>a[i];
    cntSet=0;
    forn(i, 1, n) if (!flag[i]) 
    {
        s[++cntSet]=1;
        flag[i]=true;
        forn(j, i+1, n) if (perfect(a[i]*a[j])) 
        {
            s[cntSet] ++;
            flag[j]=true;
        }
    }
    forn(i, 1, cntSet) total[i]=total[i-1]+s[i];
    dp[1][s[1]-1]=gt[s[1]];
    repn(i, 1, cntSet) forn(j, 0, n) if (dp[i][j])
    {
        forn(sub, 1, min(total[i] +1, s[i+1])) forn(bad, 0, min(j, sub))
            add(dp[i+1][j-bad + s[i+1] - sub], dp[i][j]*C(bad, j) % MOD * C(sub-bad, total[i]+1-j) % MOD * 
                                        C(sub-1, s[i+1]-1) % MOD * gt[s[i+1]] %MOD);
    }
    cout<<dp[cntSet][0];
    return 0;
}
