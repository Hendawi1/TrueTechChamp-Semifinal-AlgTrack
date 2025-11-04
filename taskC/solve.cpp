#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        int64 p, q;
        cin >> p >> q;
        int64 g = std::gcd(p, (int64)180);
        cout << (180LL * q / g - 1) << '\n';
    }
}
