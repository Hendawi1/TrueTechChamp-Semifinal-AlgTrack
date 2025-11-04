#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
using u128 = __uint128_t;

u64 mul_mod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 pow_mod(u64 a, u64 d, u64 mod) {
    u64 res = 1;
    while (d) {
        if (d & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return res;
}

bool miller_rabin(u64 n) {
    if (n < 2) return false;
    
    // Check small primes
    static const u64 smallPrimes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (u64 p : smallPrimes) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    
    // Find s,d with n-1 = d * 2^s
    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }
    
    // Bases deterministic for 64-bit
    u64 bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (u64 a : bases) {
        if (a % n == 0) continue;
        u64 x = pow_mod(a % n, d, n);
        if (x == 1 || x == n-1) continue;
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n-1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

u64 isqrt_floor(u64 x) {
    u64 r = sqrtl(x);
    while ((u128)(r+1)*(r+1) <= x) ++r;
    while ((u128)r*r > x) --r;
    return r;
}

u64 isqrt_ceil(u64 x) {
    u64 f = isqrt_floor(x);
    return (u128)f*f == x ? f : f+1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    const u64 TEN10 = 10000000000ULL;
    const u64 TEN7 = 10000000ULL;
    
    for (int ti = 0; ti < t; ++ti) {
        string pref;
        cin >> pref;
        
        u64 P = stoull(pref); // Use stoull to avoid sign issues
        set<u64> answers;
        
        // Check both cases: 7 is prime & 8 is square, and 7 is square & 8 is prime
        for (int d = 7; d <= 8; ++d) {
            u64 base = (u64)d * TEN10 + P * TEN7;
            u64 low = base;
            u64 high = base + TEN7 - 1;
            
            u64 k_lo = isqrt_ceil(low);
            u64 k_hi = isqrt_floor(high);
            
            for (u64 k = k_lo; k <= k_hi; ++k) {
                u64 square = k * k;
                u64 S = square - (u64)d * TEN10;
                
                // Verify S is in correct range
                if (S < P * TEN7 || S > P * TEN7 + TEN7 - 1) continue;
                
                int other_d = (d == 7 ? 8 : 7);
                u64 otherN = (u64)other_d * TEN10 + S;
                
                if (miller_rabin(otherN)) {
                    answers.insert(S);
                }
            }
        }
        
        // Convert to sorted vector and output
        vector<u64> out(answers.begin(), answers.end());
        sort(out.begin(), out.end());
        
        cout << out.size();
        for (u64 s : out) {
            string ss = to_string(s);
            if (ss.size() < 10) {
                ss = string(10 - ss.size(), '0') + ss;
            }
            cout << ' ' << ss;
        }
        cout << '\n';
    }
    
    return 0;
}
