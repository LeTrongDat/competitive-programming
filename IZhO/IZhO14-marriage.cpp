/*
    Author: Le Trong Dat.
    Idea: Trivial observation:
        - If [L, R] satisfies, [L, i] is also satisfied with N> = i> = R.
        => Use two pointer.
        For each fixed L, we will find the nearest R such that [L, R] satisfies the requirements of the problem.
        Maintaining 1 set of daughters has not been matched.    
        When increasing L to 1 if young man (L-1)-th is matched with daughter j-th, 
        we will add daughter j-th to the set of daughters that have not been matched.
        If the current set still has no daughters yet matched, we increase R and pop_back 
        each daughters out of the set if we find augmenting path which contains only the young man in the segment L-> R.
        => Use Kuhn Munkres.
*/
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)           for(int i=a; i<=b; ++i)
const int maxN = 3e4 +10;
const int maxM = 2e3 +10;
int matched[maxN];
vector<int> E[maxM];
int le, ri, t = 1;
int N, M, K;
long long result;
int visited[maxM];
vector<int> not_match;
bool visit(int u) {
    if (visited[u] == t) return false;
    visited[u] = t;
    while (E[u].size() && E[u].back() < le) E[u].pop_back();
    for(auto v: E[u]) if (v <= ri) {
        if (!matched[v] || visit(matched[v])) {
            matched[v] = u;
            return true;
        } 
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin >> N >> M >> K;
    forn(i, 1, K) {
        int Ai, Bi; 
        cin >> Ai >> Bi;
        E[Bi].push_back(Ai);
    }
    forn(i, 1, M) {
        sort(E[i].begin(), E[i].end());
        reverse(E[i].begin(), E[i].end());
    }
    forn(i, 1, M) not_match.push_back(i);
    for(le = 1; le <= N; ++le) {
        ri = max(ri, le);
        while (not_match.size()) {
            t ++;
            if (visit(not_match.back())) not_match.pop_back(); else {
                if (ri > N) break; 
                ri ++;
            }
        }
        if (not_match.empty()) result += N - ri + 1;
        if (matched[le]) not_match.push_back(matched[le]);
    }
    cout << result;
}
