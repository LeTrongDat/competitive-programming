#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pr pair < ll, ll >
#define vi vector < ll >
#define ft first
#define nd second
#define pb push_back

#define forn(i, a, b)   for(int i=a; i<=b; ++i)
#define ford(i, a, b)   for(int i=a; i>=b; --i)
#define repn(i, a, b)   for(int i=a; i <b; ++i)
#define repd(i, a, b)   for(int i=(int)a-1; i>=b; --i)

int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif //ONLINE_JUDGE
    ios::sync_with_stdio(0);
    string s; cin >> s;
    int n = s.size(); 
    if (n % 2 == 0) { cout << n/2; return 0; }
    repn(i, 1, n) if (s[i] != '0') {
        cout << (n+1) /2;
        return 0;
    }
    cout << n/ 2;
    
    return 0;
}