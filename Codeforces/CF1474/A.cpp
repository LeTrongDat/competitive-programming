#include <bits/stdc++.h>
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define ford(i, a, b)       for(int i = a; i >= b; --i)
#define repn(i, a, b)       for(int i = a; i < b; ++i) 
#define repd(i, a, b)       for(int i = (int)a - 1; i >= b; --i) 
#define llong               long long
using namespace std;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    for(; ntest; ntest --) { 
        int n; cin >> n;
        string a, b; 
        cin >> b;
        a = b;
        int prv = -1;
        repn(i, 0, b.size()) {
            ford(dig, 2, 0) {
                if (dig != prv && dig - b[i] + '0' <= 1) {
                    a[i] = char(dig - b[i] + '0' + '0'); 
                    break;
                }
            }
            prv = a[i] + b[i] - '0' * 2;
        }
        cout << a << '\n';
    }
    return 0;
}
