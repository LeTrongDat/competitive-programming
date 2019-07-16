/*
    Author: Le Trong Dat.
    Idea: - https://github.com/LeTrongDat/CompetitiveProgramming/blob/master/Solution/subway-sol.pdf.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define ford(i, a, b)               for(int i=a; i>=b; --i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
#define repd(i, a, b)               for(int i=(int)a-1; i>=b; --i)
const long double INF = 1e15+ 10;
const int maxN = 1e5 +10;
long double L;
int N;
long double result = INF;
pair<long double, char> train[maxN];
long double A[maxN], B[maxN];
void process(long double A[]) {
    long double mx = 0, mn = 0;
    forn(i, 2, N) {
        long double tmp = A[i];
        A[i] = A[i-1] + L;
        mx = max(mx, tmp - A[i]);
        mn = min(mn, tmp - A[i]);
    }
    long double x = -(mn + mx) / 2;
    result = min(result, mx+x);
}
int main() {
    cin >> L >> N;
    forn(i, 1, N) cin >> train[i].first >> train[i].second;
    sort(train +1, train +N+1);
    forn(i, 1, N) {
        A[i] = B[i] = train[i].first;
        if (i&1) A[i] = 2*L - A[i]; else B[i] = 2*L - B[i];
    }
    L = 2*L / N;
    sort(A+1, A+N +1);
    sort(B+1, B+N +1);
    process(A);
    process(B);
    cout << fixed << setprecision(6) << result << '\n';
}
