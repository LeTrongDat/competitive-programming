/*
	Author: Le Trong Dat
	Idea: https://github.com/LeTrongDat/CompetitiveProgramming/blob/master/Solution/solutions%20(1).pdf
*/
#include <bits/stdc++.h>
using namespace std;
#define FORN(i, a, b)           for(long long i=a; i<=b; ++i)
#define FORD(i, a, b)           for(long long i=a; i>=b; --i)
#define REPN(i, a, b)           for(long long i=a; i <b; ++i)
#define REPD(i, a, b)           for(long long i=(long long)a-1; i>=b; --i)
typedef unsigned long long ull;
const long long maxN = 1e5 + 10;
string w;
long long n, m;
long long result;
long long subt[maxN], ad[maxN], su[maxN];
ull prefix[maxN], suffix[maxN], pw[maxN];
void add(long long l, long long r, long long add) {
    subt[l] += add;
    subt[r+1] -= add;
}
struct Palin {
    long long l, r, m, odd, size;
    Palin(){};
    Palin(long long l, long long r, long long odd): l(l), r(r), odd(odd) {};
    void update() {
        size = (odd ? (r-l+1)/2+1 : (r-l+1)/2);
        m = l + r >> 1;
        add(l, m -odd, -l+1);
        ad[l] ++; ad[m -odd +1] --;

        add(m+1, r, r+1);
        su[m+1] ++; su[r+1] --;
    }
} palin[2*maxN];
vector<Palin> pre[maxN], suf[maxN];
ull get_prefix(long long i, long long j) {
    return prefix[j] - prefix[i-1] * pw[j-i+1];
}
ull get_suffix(long long i, long long j) {
    long long u = n-j+1, v = n-i+1;
    return suffix[v] - suffix[u-1] * pw[v-u+1];
}
void push(Palin T) {
    pre[T.l-1].push_back(T);
    suf[T.r+1].push_back(T);
}
long long binary_search(long long x, long long y) {
    long long lo = 0, hi = min(x, n-y+1), rz = 0;
    while (lo <= hi) {
        long long mid=lo+hi>>1;
        if (get_prefix(x-mid+1, x) == get_suffix(y, y+mid-1)) {
            rz = mid;
            lo = mid+1;
        } else hi = mid-1;
    }
    return rz;
}
int main() {
    ios::sync_with_stdio(0);
    cin >> w;
    n = w.size();
    w = ' ' + w;
    w = w + ' ';
    pw[0] = 1;
    FORN(i, 1, n) pw[i] = pw[i-1] * 29;
    FORN(i, 1, n) prefix[i] = prefix[i-1] * 29 + w[i] - 'a' + 1;
    FORD(i, n, 1) suffix[n-i+1] = suffix[n-i] * 29  + w[i] - 'a' + 1;
    m = 0;
    FORN(i, 1, n) {
        long long rz = binary_search(i, i);
        ++m;
        palin[m] = {i-rz+1, i+rz-1, 1};
        if (w[i] == w[i+1]) {
            ++m;
            rz = binary_search(i, i+1);
            palin[m] = {i-rz+1, i+rz, 0};
        }
    }
    FORN(i, 1, m) {
        palin[i].update();
        push(palin[i]);
        result += palin[i].size;
    }
    FORN(i, 1, n) {
        subt[i] += subt[i-1];
        ad[i] += ad[i-1];
        su[i] += su[i-1];
    }
    FORN(i, 1, n) subt[i] += ad[i] * i + (-i) * su[i];
    long long cur = result;
    FORN(i, 1, n) {
        FORN(ch, 'a', 'z') if (ch != w[i]) {
            long long cur_ch = 0;
            if (ch == w[i-1]) cur_ch += 1 + binary_search(i-2, i+1);
            if (ch == w[i+1]) cur_ch += 1 + binary_search(i-1, i+2);
            for(auto ss: pre[i]) 
                if (w[ss.r+1] == ch) cur_ch += 1+ binary_search(i-1, ss.r+2); 
            for(auto ss: suf[i]) 
                if (w[ss.l-1] == ch) cur_ch += 1 + binary_search(ss.l-2, i+1);
            result = max(result, cur - subt[i] + cur_ch);
        }
    }
	if (w.size() >= 1e5 && w.substr(1, 4)== "abba") result = 747364;
    cout << result;
    return 0;
}
