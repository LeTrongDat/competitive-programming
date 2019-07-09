/*
    Author: Le Trong Dat.
    Idea: For the first case, we will spend all the remaining votes for each party.
        In the second case, we will fix the number of seats that the i-th party can win, then check if 
        the remaining parties can win M - x (x is the number of seats that party i-th can win) with Number of votes remaining.
        => Dp (i, S) is the minimum number of votes needed to win the S seats when considering the i-th party 
        (not containing the party we are considering).
        When we arrive at the i-party if we want to reach the K seats, the necessary and sufficient conditions are V/K > the 
        number of votes for the current party we are considering / (the number of seats that the party won is + 1). 
        (The reason why <seat K is still available is that the current party will get a seat instead of the number of seats we fixed).
        This is also a sufficient condition, because when larger, the seats of these parties' additional 
        seats are no longer important because even more before or after, the number of additional seats will 
        be sufficient and will not make the party we are considering increasing seats.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
typedef long long llong;
const int maxN = 110;
const int maxM = 210;
int V, N, M;
int Sum, Remain;
int Current[maxN], maxAns[maxN], minAns[maxN];
pair<int, int> A[maxN];
int dp[maxN][maxM];
void minimize(int &a, int b) { a = min(a, b); }
struct Fraction {
    llong Numera, Denomi;
    int id; 
    Fraction(){};
    Fraction(llong Numera, llong Denomi, int id): Numera(Numera), Denomi(Denomi), id(id){};
    bool operator < (const Fraction& oo) const {
        llong num1 = this->Numera * oo.Denomi, num2 = oo.Numera * this->Denomi;
        if (num1 != num2) return num1 < num2;
        return this->id > oo.id;
    }
    bool operator > (const Fraction& oo) const {
        llong num1 = this->Numera * oo.Denomi, num2 = oo.Numera * this->Denomi;
        if (num1 != num2) return num1 > num2;
        return this->id < oo.id;
    }
};
typedef pair<Fraction, int> ii;
void maxVote() {
    forn(i, 1, N) {
        Current[i] += Remain;
        if (Current[i] * 100 < V * 5) { maxAns[i] = 0; Current[i] -= Remain; continue; }
        priority_queue<Fraction, vector<Fraction>, less<Fraction>> pq;
        forn(j, 1, N) if (Current[j] * 100 >= V * 5 ) pq.push({Current[j], 1, j});;
        int rM = M;
        for(; rM; rM --) {
            auto ss = pq.top(); pq.pop();
            if (ss.id == i) maxAns[i] ++;
            pq.push({ss.Numera, ss.Denomi+1, ss.id});
        }
        Current[i] -= Remain;
    }
    forn(i, 1, N) cout << maxAns[i] << ' ';
    cout << '\n';
}
int gAdd(int Aj, int j, int Ai, int i, int vote, int mid) {
    int x = (Ai * vote + mid) / (mid + 1);
    if (x * (mid+1) == Ai * vote && j > i) x ++;
    x = max(x, Aj);
    return x;
}
void minVote() {
    forn(i, 1, N) if (Current[i] * 100 < V * 5) minAns[i] = 0; 
        else {
            int low = 0, high = maxAns[i];
            while (low <= high) {
                int mid = low + high >> 1;
                int m = 0;
                forn(j, 1, N) if (j != i) A[++m] = { Current[j], j };
                memset(dp, 0x3f, sizeof dp);
                dp[0][0] = 0;
                forn(j, 0, m-1) forn(tot, 0, M-mid) {
                    minimize(dp[j+1][tot], dp[j][tot]);
                    forn(vote, 1, M-mid-tot) {
                        int x = gAdd(A[j+1].first, A[j+1].second, Current[i], i, vote, mid);
                        if (x * 100 < V * 5) x = (V * 5 + 99) / 100;
                        //cout << A[j+1].first << ' ' << A[j+1].second << ' ' << vote << ' ' << x << '\n';
                        minimize(dp[j+1][tot+vote], dp[j][tot] + x - A[j+1].first);
                    }
                }
               // cout << mid <<' ' << M - mid << ' ' << dp[m][M-mid] << '\n';
                if (dp[m][M-mid] <= Remain) {
                    minAns[i] = mid;
                    high = mid-1;
                } else low = mid+1;
            }
        }
    forn(i, 1, N) cout << minAns[i] << ' ';
        
}
int main() {
    ios::sync_with_stdio(0);
    cin >> V >> N >> M;
    forn(i, 1, N) {
        cin >> Current[i];
        Sum += Current[i];
    }
    Remain = V - Sum;
    maxVote();
    minVote();
}
