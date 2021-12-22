#include <bits/stdc++.h>

using namespace std;

int ntest;
string str;
int main() {
    ios::sync_with_stdio(0);

    cin.tie(nullptr);

    cin >> ntest;
    while (ntest--) {
        cin >> str;
        int len = size(str);
        if (len % 2) {
            cout << "NO\n";
            continue;
        }
        string head = str.substr(0, len / 2);
        string tail = str.substr(len / 2, len / 2);
        cout << (head == tail ? "YES" : "NO") << '\n';
    }

}