/**
 * @file arc233_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int64_t qpow(int64_t a, int64_t x, int64_t mod) {
    int64_t ans = 1;
    a %= mod;
    while (x) {
        if (x & 1) ans = (ans * a) % mod;
        a = (a * a) % mod, x >>= 1;
    }
    return ans;
}

int a[maxn];

void solve(void) {
    int n;
    cin >> n;

    unordered_set<int> S;
    for (int i = 1; i <= n; i++) cin >> a[i], S.insert(a[i] % n);

    if ((int)S.size() != n) return cout << 0 << endl, void();

    int64_t ans = 1;
    for (int i = 1; i < n; i++) ans = ans * qpow(i, n - i, n) % n;

    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) a[i] %= n;

    int cnt = 0;
    vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        cnt++;
        int p = i;
        while (!vis[p]) vis[p] = true, p = a[p] + 1;
    }

    if ((n - cnt) & 1) ans = (n - ans) % n;

    cout << ans << endl;

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
