/*
    Author: Le Trong Dat
    Idea:
        There are 2 ways to turn 1 string into an easy-to-remember string.
        * Change the character of 1 in the columns of that string at the cost of C (i, j).
        * Changing the whole character is similar to the character of 1 in the columns of 
        that string at the cost of the total cost of changing all the same letters - the biggest cost.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)   for(int i=a; i <=b; ++i)
#define repn(i, a, b)   for(int i=a; i < b; ++i)
template<typename T>
void minimize(T &a, T b) { a = min(a, b); }
template<typename T>
void maximize(T &a, T b) { a = max(a, b); }
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 22;
int n, m;
ll c[N][N], sum[N][30];
ll dp[1 << N-2], pos[1 << N-2];
ll cost[N][30], mask[N][30], mx[N][30];
string str[N];
int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    forn(i, 1, n) {
        cin >> str[i];
        str[i] = ' ' + str[i];
    }
    forn(i, 1, n) forn(j, 1, m) cin >> c[i][j];
    forn(j, 1, m) {
        forn(i, 1, n) {
            cost[j][str[i][j]-'a'] += c[i][j];
            mask[j][str[i][j]-'a'] ^= (1 << i-1);
            maximize(mx[j][str[i][j]-'a'], c[i][j]);
        }
        forn(i, 'a', 'z') cost[j][i-'a'] -= mx[j][i-'a'];
    }
    repn(msk, 0, (1 << n)) repn(j, 0, n) if ( !(msk >> j & 1) ) {
        pos[msk] = j;
        break;
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    repn(msk, 0, (1 << n)) if (dp[msk] != INF) {
        int idx = pos[msk];
        forn(j, 1, m) {
            minimize(dp[msk | (1 << idx)], dp[msk] + c[idx+1][j]);
            minimize(dp[msk | mask[j][str[idx+1][j]-'a']], dp[msk] + cost[j][str[idx+1][j]-'a']);
        }
    }
    cout << dp[(1 << n) - 1];
}
