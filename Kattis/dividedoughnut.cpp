/*
                Author: Le Trong Dat.
                Idea: - https://en.wikipedia.org/wiki/Intermediate_value_theorem;
                      - If function f (x) is continuous on interval [a, b] and
                        min (f(a), f(b)) <= u <= max (f(a), f(b)) always exist x such that f(x) = u;
                      - Call f(x) = query (x, x + 5e8-1) => f(x) is a continuous function.
                        If f(0) == n/2, we get the result immediately, otherwise 
                        we have f (0) and f(5e8) will have 1 value >n/2 and 1 value <n/2 because f(0) + f(5e8) == n
                        => on the segment from [0, 5e8] according to the above theorem
                         will have 1 point x such that f(x) = n/2.
                        The second observation: call the section you are 
                        maintaining as [low, mid] (initially low = 0 and high = 5e8) if:
                        * f(mid) == n/2 => we get the results right away.
                        * If f(mid)! = n/2
                      - If f (mid) <n/2 and f(low)>n/2 then the next interval
                        containing the solution will be [low, mid] otherwise, 
                        it will be [mid, high] because low and high are always inversely each other and vice versa.
*/
#include <bits/stdc++.h>
using namespace std;
const int MOD=1e9;
const int half=5e8;
int n;
void answer(int x)
{
    cout<<"YES "<<x<<endl;
    exit(0);
}
int query(int mid)
{
    cout<<"QUERY "<<mid<<' '<<(mid+half-1)%MOD<<endl;
    int sprinkles; cin>>sprinkles;
    if (sprinkles==n/2) answer(mid);
    return sprinkles;
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    int sprinkles=query(0);
    int lo=0, hi=5e8;
    for(int i=1; i<=28; ++i)
    {
        int mid=lo+hi>>1;
        int current=query(mid);
        if (current>n/2 && sprinkles<n/2 || current<n/2 && sprinkles>n/2) hi=mid; else lo=mid;
    }
    answer(lo+hi>>1);
}