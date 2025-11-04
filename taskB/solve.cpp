#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        bool hasZero = false;
        int positiveCount = 0;
        int negativeCount = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == 0) {
                hasZero = true;
            } else if (a[i] > 0) {
                positiveCount++;
            } else {
                negativeCount++;
            }
        }
        if (hasZero) {
            cout << -1 << endl;
            continue;
        }
        if (positiveCount != negativeCount) {
            cout << -1 << endl;
            continue;
        }
        sort(a.begin(), a.end(), [](int x, int y) {
            if (abs(x) == abs(y)) {
                return x > y;
            }
            return abs(x) < abs(y);
        });
        stack<int> st;
        long long ans = 0;
        bool valid = true;
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                st.push(a[i]);
            } else {
                if (st.empty()) {
                    valid = false;
                    break;
                }
                int s = st.top();
                st.pop();
                int e = -a[i];
                if (s > e) {
                    valid = false;
                    break;
                }
                ans += e - s;
            }
        }
        if (!st.empty()) {
            valid = false;
        }
        if (!valid) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
