/*
    Author: Le Trong Dat
    Idea:
        We will build one half of a number, the second half is like the first half, 
        then count the number of ways to change the most 1 digit in the second half to get 
        a new number <= a.
        * If the first half <a, then we can change any digits in the second half and still satisfy 
        the condition <= a.
        => Number of numbers = number of first half * (9 * number of digits of the second half + 1).
        * If the first half = the first half of a, we will check each number of the second half, try 
        replacing it with another number, check whether <= a or not and add 1 in the result.
        To count the number of buildable halves, we can use dp with dp (i, less) as the number of ways 
        to build the first half to the i-th digit and already smaller than a or not.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define ford(i, a, b)               for(int i=a; i>=b; --i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
#define repd(i, a, b)               for(int i=(int)a-1; i>=b; --i)
typedef long long llong;
const int N = 30;
llong dp[N][N], f[N], pw[N];
bool operator <= (const vector<int>& a, const vector<int>& b) {
    repn(i, 0, a.size()) if (a[i] != b[i])
        if (a[i] > b[i]) return false; else return true;
    return true;
}
llong get_ans(llong a) {
    if (a < 10) return a;
    llong ans = 0;
    int n;
    vector<int> digit;
    for(; a > 0; a /= 10) digit.push_back(a % 10);
    ans += f[digit.size() -1];
    n = digit.size();
    digit.push_back(0);
    reverse(digit.begin(), digit.end());
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    n = (n + 1) / 2;
    repn(i, 0, n) forn(les, 0, 1) if (dp[i][les]) {
        forn(j, (i == 0 ? 1 : 0), (les ? 9 : digit[i+1])) 
            dp[i+1][les || j < digit[i+1]] += dp[i][les];
    }
    ans += dp[n][1] * ( (digit.size() -1-n) * 9 + 1);
    vector<int> tmp(1, 0);
    forn(i, 1, n) tmp.push_back(digit[i]);
    ford(i, n - (digit.size() - 1) % 2, 1) tmp.push_back(digit[i]);
    if (tmp <= digit) ans ++;
    repn(i, n+1, digit.size()) {
        int x = tmp[i];
        forn(j, 0, 9) if (j != x) {
            tmp[i] = j;
            if (tmp <= digit) ans ++;
        }
        tmp[i] = x;
    }
    return ans;
}
int main() {
    freopen("almost.in", "r", stdin);
    freopen("almost.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    pw[0] = 1;
    forn(i, 1, 18) pw[i] = pw[i-1] * 10;
    f[1] = 9;
    forn(i, 2, 18) {
        int half = (i + 1) / 2;
        f[i] = ( pw[half] - pw[half-1] ) * ((i-half) * 9 + 1);
        f[i] += f[i-1];
    }
    llong a;
    while (cin >> a) {
        if (!a) break;
        cout << get_ans(a) << '\n';
    }
    
    return 0;
}
