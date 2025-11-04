#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    string s;
    while (t--) {
        cin >> s;
        array<int,3> cnt = {0,0,0};
        for (char ch : s) {
            if (ch == 'M') ++cnt[0];
            else if (ch == 'T') ++cnt[1];
            else if (ch == 'C') ++cnt[2];
        }
        bool stable = true;
        for (int i = 0; i < 3; ++i) {
            if (cnt[i] > 0 && (cnt[i] % 9 != 0)) {
                stable = false;
                break;
            }
        }
        cout << (stable ? 1 : 0) << '\n';
    }
    return 0;
}
