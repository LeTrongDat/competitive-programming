/* 
                    Author: Le Trong Dat
                    Idea: - We have an observation:
                            + We can delete up to n / 3 elements, meaning that each array must have 
                              at least 2/3 different elements => Divide each sequence into 3 parts :
                                * Part 1: 0->n/3: a[i]=i;
                                * Part 2: n/3->2n/3: b[i]=i;
                                * Part 3: 2n/3->n/3: b[i] = (n/3->0) => a(i)=s(i)-b(i)>=n-n/3>n/3>a(n/3)=>b gradually decreases 
                                and a gradually increases.
                            Since the array S is unique, S(i)> = i, therefore. The unique part of 
                            array a will be an ascending sequence, while the unique part of array b 
                            will be a descending sequence and each part will account for 2/3 of the array.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
#define repn(i, a, b)       for(int i=a; i <b; ++i)
const int N=1e5 + 100;
int n;
int a[N], b[N];
pair<int, int> s[N];
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    forn(i, 1, n) { cin>>s[i].first; s[i].second=i; }
    sort(s+1, s+n +1);
    repn(i, 0, n/3) { a[s[i+1].second]=i; b[s[i+1].second]=s[i+1].first-a[s[i+1].second]; }
    repn(i, n/3, 2*n/3) { b[s[i+1].second]=i; a[s[i+1].second]=s[i+1].first-b[s[i+1].second]; }
    int now=n/3;
    repn(i, 2*n/3, n) { b[s[i+1].second]=max(--now, 0); a[s[i+1].second]=s[i+1].first-b[s[i+1].second]; }
    cout<<"YES\n";
    forn(i, 1, n) cout<<a[i]<<' ';
    cout<<'\n';
    forn(i, 1, n) cout<<b[i]<<' ';
    return 0;
}