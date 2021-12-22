#include <bits/stdc++.h>

using namespace std;
int ntest;
long long a, s;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> ntest;

    while (ntest--) {
        cin >> a >> s;
        if (a >= s) {
            cout << -1 << '\n';
            continue;
        }

        string a_str = to_string(a);
        string s_str = to_string(s);

        while (a_str.length() < s_str.length()) {
            a_str = "0" + a_str;
        }

        int pivot = a_str.length() - 1;
        string ans = "";
        bool invalid = false;
        for(int i = s_str.length() - 1; i >= 0; --i) {
            if (s_str[i] >= a_str[pivot]) {
                ans = to_string(s_str[i] - a_str[pivot]) + ans;
                --pivot;
                continue;
            }
            if (!i) {
                invalid = true;
                break;
            }
            int nxt_num = (s_str[i-1] - '0') * 10 + (s_str[i] - '0');
            if (nxt_num < 10 || nxt_num > 18) {
                invalid = true;
                break;
            }
            ans = to_string(nxt_num - (a_str[pivot] - '0')) + ans;
            --i;
            --pivot;
        }
        if (pivot >= 0) {
            for(int i = 0; i <= pivot; ++i) {
                if (a_str[i] > '0') {
                    invalid = true;
                }
            }
        }

        if (invalid) {
            cout << -1 << '\n';
            continue;
        }

        while (ans.length() && ans[0] == '0') {
            ans = ans.substr(1, ans.length() - 1);
        }
        cout << ans << '\n';
    }

}