#include <bits/stdc++.h>
using namespace std;

int ntest;
int n, a, b;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> ntest;

    while (ntest--) {
        cin >> n >> a >> b;
        vector<int> permutation;
        for(int i = 0; i < n; ++i) {
            permutation.emplace_back(i+1);
        }
        for(int i = 1; i < n; ++i) {
            if (a && i + 1 < n) {
                swap(permutation[i], permutation[i+1]);
                ++i;
                continue;
            }


        }
    }
}