/*
        Author: Le Trong Dat
        Idea: Make 2 arrays a and b, one size n and another size m satisfied: 
            a1^2 + a2^2 + .. + an^2 = k1^2.
            b1^2 + b2^2 + .. + bm^2 = k2^2.
            Then each element of table equal to x(i, j) = a[i] * b(j)
            => The sum of the squares of the numbers for each row and column is 
            a[i]^2 * (b1^2 + b2^2 + ... + bm^2) = a[i]^2 * k2^2 is a square.
            or 
            b[j]^2 * (a1^2 + a2^2 + ... + an^2) = b[j]^2 * k1^2 is a square.

            if n == 1, the array will be : 1
            if n == 2, the array will be : 3, 4
            if n is even the array will be : 1, 1, ... , 1, (n-2) / 2;
            if n is odd the array will be : 2, 1, 1, ..., 1, (n+1) / 2;
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i) 
void add(vector<int> &a, int n) {
    if (n == 1) { a.push_back(1); return; }
    if (n == 2) { forn(i, 3, 4) a.push_back(i); return; }
    if (n&1) {
        a.push_back(2);
        forn(i, 2, n-1) a.push_back(1);
        a.push_back((n+1)/2);
        return;
    }
    forn(i, 1, n-1) a.push_back(1);
    a.push_back((n-2)/2);
}
int main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> a, b;
    add(a, n);
    add(b, m);
    forn(i, 0, n-1) {
        forn(j, 0, m-1) cout << a[i]*b[j] << ' ';
        cout << '\n';
    }
}
