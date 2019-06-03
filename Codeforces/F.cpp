#include <bits/stdc++.h>
using namespace std;
#define val                         first
#define mask                        second
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
const int N = 3e5 +100;
typedef long long ll;
typedef pair<ll, ll> Object;
int n;
ll sum, rz;
vector<Object> s[N];
Object obj[N];
int sign(ll x) 
{
    if (x<0) return -1;
    if (x>0) return 1;
    return 0;
}
bool odd(ll s, ll mask)
{
    mask &= s;
    int odd=0;
    forn(bit, 0, 61) odd += (mask>>bit&1LL);
    return (odd&1);
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    forn(i, 1, n) 
    {
        cin>>obj[i].val>>obj[i].mask;
        sum += obj[i].val;
        forn(bit, 0, 61) if (obj[i].mask >= (1LL<<bit) && obj[i].mask < (1LL<<bit+1)) s[bit].push_back(obj[i]);
    }
    forn(bit, 0, 61) 
    {
        ll current = 0;
        for(auto &o: s[bit]) current += o.val * (odd(rz, o.mask)?-1:1);
        if (sign(current) != sign(sum)) continue; else rz+= (1LL<<bit);
    } 
    ll newsum = 0;
    forn(i, 1, n) newsum += obj[i].val * (odd(rz, obj[i].mask)?-1:1);
    cerr<<sum<<' '<<newsum<<'\n';
    cout<<rz;
}