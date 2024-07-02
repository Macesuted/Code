/**
 * @file 1863F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 10005

const uint64_t full = UINT64_MAX;

uint64_t a[maxn], f[maxn], g[maxn];
bool ans[maxn];

uint64_t sum(int l, int r) { return a[r] ^ a[l - 1]; }
uint64_t highBit(uint64_t v) { return v ? ((uint64_t)1 << (63 - __builtin_clzll(v))) : full; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] ^= a[i - 1], f[i] = g[i] = 0, ans[i] = false;
    if (n == 1) return cout << 1 << endl, void();
    f[1] = g[n] = highBit(sum(1, n));
    for (int len = n - 1; len >= 1; len--)
        for (int l = 1, r = len; r <= n; l++, r++) {
            uint64_t s = sum(l, r);
            if (((f[l] == full && !s) || (s & f[l])) || ((g[r] == full && !s) || (s & g[r]))) {
                uint64_t hb = highBit(s);
                f[l] |= hb, g[r] |= hb;
                if (len == 1) ans[l] = true;
            }
        }
    for (int i = 1; i <= n; i++) cout << ans[i];
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}