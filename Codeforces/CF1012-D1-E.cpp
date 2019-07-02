/*
    Author: Le Trong Dat.
    Idea: - Firstly we can see that if the array is permutation, so when we sort the array then each element
        will have an edge from its current position to its right position.
        => It creates the graph, in which has some cycles what are non-intersect.
        Call all the cycles are : (i11, i12, ..., i1n1), (i21, i22, ..., i2n2), ..., (im1, im2, ..., imnm);
        If we don't have limit S then the answer will be 1 if there is only 1 cycle, and 2 if there are more and 
        it will be like this
        (i11, i12, ..., i1n1, i21, i22, ..., i2n2, ..., ... , ..., im1, im2, ... , imnm) 
        and (im1, im-11, ..., ..., i11).
        And if the array is not permutation ?
        => Firstly we must sort the array following the condition: There are as many fixed positions as possible.
        Fixed position is the position what we dont need to shift the current element in that position.
        And others elements we make the cycles, when we merge two cycle, the answer will decrese 1 and the length of all cycles
        will increse 1.
        => We will merge as many cycles as possible.
        If we have 2 numbers which are the same but are not in the same cycles like this
        (a11, a2, ..., an) and (a12, b2, ..., bm) (a11==a12)
        => We can change this to (a11, b2, ... , bm, a12, a2, ..., an) => The number of cycles decrease 1 and the length is not 
        change.
 */
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)               for(int i=a; i<=b; ++i)
#define repn(i, a, b)               for(int i=a; i <b; ++i)
const int N = 2e5 +100;
typedef pair<int, int> ii;
int n, limit;
int nxt[N], lab[N], flag[N];
ii a[N];
vector<int> ans1, ans2;
vector< vector<int> > ans3;
vector<ii> v;
int root(int u)
{
    if (lab[u] < 0) return u;
    return lab[u] = root(lab[u]);
}
void join(int u, int v)
{
    int l1 = root(u), l2 = root(v);
    if (l1 == l2) return;
    if (lab[l1] > lab[l2]) swap(l1, l2);
    lab[l1] += lab[l2];
    lab[l2] = l1;
}
void show(vector<int> &s)
{
    cout << s.size() << '\n';
    for(auto &x: s) cout << x << ' ';
    cout << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> limit;
    memset(lab, -1, sizeof lab);
    forn(i, 1, n) 
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a+1, a+n+1);
    forn(i, 1, n)
    {
        int j1 = i, j2 = i;
        while (j2 <n && a[j2+1].first == a[j2].first) j2 ++;
        for(; i<=j2; ++i)
        {
            while (j1 <= a[i].second && a[i].second <= j2 && a[i].second != i) swap(a[i], a[a[i].second]);
        }
        i = j2;
    }
    forn(i, 1, n) if (a[i].second != i)
    {
        nxt[a[i].second] = i;
        join(a[i].second, i);
        v.push_back(a[i]);
    }
    repn(i, 0, v.size())
    {
        while (i+1 < v.size() && v[i+1].first == v[i].first)
        {
            i ++;
            int idx1 = v[i].second, idx2 = v[i-1].second;
            if (root(idx1) == root(idx2)) continue;
            join(idx1, idx2);
            swap(nxt[idx1], nxt[idx2]);
        }
    }
    int sum = 0;
    forn(i, 1, n) if (a[i].second != i && !flag[root(a[i].second)])
    {
        flag[root(a[i].second)] = true;
        sum += abs(lab[root(a[i].second)]);
    }
    if (limit < sum) 
    {
        cout << -1;
        return 0;
    }
    int addmx = limit - sum;
    int cnt = 0;
    memset(flag, 0, sizeof flag);
    forn(i, 1, n) if (a[i].second != i && !flag[root(a[i].second)])
    {
        flag[root(a[i].second)] = true;
        cnt ++;
        if (cnt <= addmx) 
        {
            ans2.push_back(a[i].second);
            int cur = a[i].second;
            do {
                ans1.push_back(cur);
                cur = nxt[cur];
            } while (cur != a[i].second);
        } else 
        {
            vector<int> cycle; 
            int cur = a[i].second;
            do {
                cycle.push_back(cur);
                cur = nxt[cur];
            } while (cur != a[i].second);
            ans3.push_back(cycle);
        }
    }
    if (ans1.size()) ans3.push_back(ans1);
    reverse(ans2.begin(), ans2.end());
    if (ans2.size() > 1) ans3.push_back(ans2);
    cout << ans3.size() << '\n';
    for(auto &s: ans3) show(s);
    return 0;
}
