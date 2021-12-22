#include <bits/stdc++.h>
using namespace std;

int ntest;
int n;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> ntest;
    while (ntest--) {
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cout << i + 2 << ' ';
        }
        cout << '\n';
    }
}