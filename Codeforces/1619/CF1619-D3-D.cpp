#include <bits/stdc++.h>

using namespace std;
const int NShop = 1e5 + 10;

int ntest;
int n_friends;
int m_shops;
int invalid_shop[NShop];
vector<int> joy_table[NShop];

auto solved(int alpha) {
    for(int i = 0; i < m_shops; ++i) {
        invalid_shop[i] = false;
    }
    for(int i = 0; i < n_friends; ++i) {
        for(int j = 0; j < m_shops; ++j) {
            if (joy_table[j][i] < alpha) {
                invalid_shop[j] = true;
            }
        }
    }
    int n_valid_shops = 0;
    for(int i = 0; i < m_shops; ++i) {
        if (!invalid_shop[i]) {
            ++n_valid_shops;
        }
    }
    return (n_valid_shops >= n_friends-1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> ntest;
    while (ntest--) {
        cin >> n_friends >> m_shops;

        for(int i = 0; i < m_shops; ++i) {
            for(int j = 0; j < n_friends; ++j) {
                int joy_ij;
                cin >> joy_ij;

                joy_table[i].emplace_back(joy_ij);
            }
        }

        int ans = 0, low = 0, high = 1e9, mid = 0;
        while (low <= high) {
            mid = (low + high) >> 1;
            if (solved(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        for(int i = 0; i < m_shops; ++i) {
            joy_table[i].clear();
        }
        cout << ans << '\n';
    }

}