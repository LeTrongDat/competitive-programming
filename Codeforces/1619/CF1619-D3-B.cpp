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
        int squares = sqrt(n);
        int cubes = cbrt(n);
        int common = 0;

        for(int i = 1; i <= cubes; ++i) {
            int cube = i * i * i;
            int sq = sqrt(cube);
            if (sq * sq == cube) {
                common ++;
            }
        }

        cout << squares + cubes - common << '\n';
    }

}