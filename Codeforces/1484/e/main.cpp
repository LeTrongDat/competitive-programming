#include <bits/stdc++.h>
using namespace std;
#define eb                  emplace_back
#define llong               long long 
#define forn(i, a, b)       for(int i = a; i <= b; ++i)
#define repn(i, a, b)       for(int i = a; i <  b; ++i)
 
#ifndef LOCAL 
#define cerr                if (0) cerr 
#endif 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 3e5 + 10;
int n;
int h[N], b[N], l[N];
llong dp[N];
class Node {
    private:
        Node *left;
        Node *right;
        llong mx; 
        int l, r;
    public: 
        Node(): left(NULL), right(NULL) {};
        Node(int l, int r, llong mx): Node() {
            this->l = l;
            this->r = r;
            this->mx = mx;
        }
        llong get(int l, int r) {
            if (this->l >= r or this->r - 1 < l) return LLONG_MIN;
            if (l <= this->l and this->r <= r) return mx;
            return max(left->get(l, r), right->get(l, r));
        }
        void update(int pos, llong val) {
            if (this->l + 1 == this->r) {
                this->mx = val;
                return;
            }
            if (pos < left->r) left->update(pos, val);
            else right->update(pos, val);

            this->mx = max(left->mx, right->mx);
        }
        void init() {
            if (this->l + 1 ==  this->r) return;
            int mid = (this->l + this->r) >> 1;
            this->left = new Node(this->l, mid, LLONG_MIN);
            this->right = new Node(mid, this->r, LLONG_MIN);

            this->left->init();
            this->right->init();
        }
        ~Node() {
            if (left) delete left;
            if (right) delete right;
        }
} *root; 
auto solve() {
    cin >> n;
    repn(i, 0, n) cin >> h[i];
    repn(i, 0, n) cin >> b[i];


    root = new Node(0, n, LLONG_MIN);
    root->init();
    l[0] = -1; dp[0] = b[0];
    root->update(0, dp[0]);

    repn(i, 1, n) {
        l[i] = i - 1;
        while (l[i] != -1 and h[l[i]] > h[i]) l[i] = l[l[i]];
        dp[i] = (l[i] == -1 ? b[i] : dp[l[i]]);
        dp[i] = max(root->get(l[i], i) + b[i], dp[i]);
        root->update(i, dp[i]);
    }
    delete root;
    return dp[n-1];
}
int main(void) {
#ifdef LOCAL 
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ntest = 1;
    for(; ntest --;) {
        auto ans = solve();
        cout << ans << '\n';
    }
    return 0;
}
