/**
 * @file 115023K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int64_t a[maxn], A[maxn], B[maxn];
int ans[maxn];

void solve(void) {
    int n = 1000;

    for (int i = 0; i < n; i++) cin >> a[i];

    const int64_t mod = 1e9, bmod = 1e18;

    auto fnd = [&](const vector<int64_t>& rec) -> pair<int64_t, int64_t> {
        unordered_map<int64_t, int64_t> mp;
        while (true) {
            int64_t S = rnd() & (((int64_t)1 << rec.size()) - 1), sum = 0;
            for (size_t i = 0; i < rec.size(); i++)
                if (S >> i & 1) sum += rec[i];
            sum %= mod;
            if (mp.count(sum) && S != mp[sum]) return {S ^ (S & mp[sum]), mp[sum] ^ (S & mp[sum])};
            mp[sum] = S;
        }
    };

    vector<int64_t> vec;
    for (int t = 0; 32 * (t + 1) <= n; t++) {
        vector<int64_t> rec;
        for (int i = 0; i < 32; i++) rec.push_back(a[32 * t + i] % mod);
        tie(A[t], B[t]) = fnd(rec);

        int64_t sum = 0;
        for (int i = 0; i < 32; i++) {
            if (A[t] >> i & 1) sum = (sum + a[32 * t + i]) % bmod;
            if (B[t] >> i & 1) sum = (sum + bmod - a[32 * t + i]) % bmod;
        }
        vec.push_back(sum / mod);
    }

    auto [S, T] = fnd(vec);
    for (size_t t = 0; t < vec.size(); t++) {
        if (S >> t & 1)
            for (int i = 0; i < 32; i++) {
                if (A[t] >> i & 1) ans[32 * t + i] = 1;
                if (B[t] >> i & 1) ans[32 * t + i] = 2;
            }
        if (T >> t & 1)
            for (int i = 0; i < 32; i++) {
                if (A[t] >> i & 1) ans[32 * t + i] = 2;
                if (B[t] >> i & 1) ans[32 * t + i] = 1;
            }
    }

    for (int i = 0; i < n; i++) cout << ans[i];
    cout << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}