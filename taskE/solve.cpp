#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 1000000007;

int64 modpow(int64 a, long long e) {
    int64 r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        string ks;
        cin >> n >> ks;
        if ((int)ks.size() < n) ks = string(n - ks.size(), '0') + ks;
        vector<int> bit(n, 0);
        for (int i = 0; i < n; ++i) if (ks[i] == '1') bit[n - 1 - i] = 1;
        if (bit[n-1] == 1) {
            cout << 0 << '\n';
            continue;
        }
        vector<int> isU(n, 0);
        for (int i = 0; i < n; ++i) isU[i] = (bit[i] == 0) ? 1 : 0;
        vector<int> suff(n+1, 0);
        for (int i = n-1; i >= 0; --i) suff[i] = suff[i+1] + isU[i];
        long long m = suff[0];
        long long total_edges = (long long)n * (n - 1) / 2;
        long long internal_U = m * (m - 1) / 2;
        int64 prod = 1;
        long long sum_a = 0;
        for (int i = 0; i < n; ++i) {
            if (!isU[i]) {
                long long a_i = suff[i+1];
                if (a_i == 0) { prod = 0; break; }
                sum_a += a_i;
                int64 term = (modpow(2, a_i) - 1) % MOD;
                if (term < 0) term += MOD;
                prod = (prod * term) % MOD;
            }
        }
        if (prod == 0) {
            cout << 0 << '\n';
            continue;
        }
        long long free_edges = total_edges - internal_U - sum_a;
        if (free_edges < 0) {
            cout << 0 << '\n';
            continue;
        }
        int64 ways_free = modpow(2, free_edges);
        int64 ans = (prod * ways_free) % MOD;
        cout << ans << '\n';
    }
    return 0;
}
