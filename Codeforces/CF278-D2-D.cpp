/*
    Author: Le Trong Dat
    Idea:
        Create the set of points like this : https://postimg.cc/rz5Fmp9b.
        In details : https://codeforces.com/blog/entry/6815
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    int n, m; 
    cin >> n >> m;
    if (m == 3) {
        if (n == 3) {
            cout << "0 0\n" << "0 1\n" << "1 0";
        }
        if (n == 4) {
            cout << "0 0\n" << "0 10\n" << "10 0\n" << "1 1";
        }
        if (n >= 5) cout << -1;
    } else {
        int x = 1e7;
        for(int i=1; i<=m; ++i) cout << i << ' ' << i*i + x << '\n';
        for(int i=1; i<=n-m; ++i) cout << i << ' ' << -i*i - x << '\n';
    }
}
