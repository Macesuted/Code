/**
 * @file 2066C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-11
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

#define maxn 200005
#define mod 1'000'000'007

int a[maxn], pre[maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] ^ a[i];

    unordered_map<int, int> f;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        int det = 0;
        if (f.count(pre[i - 1])) det = Mod(det + Mod(2 * f[pre[i - 1]]));
        if (f.count(pre[i])) det = Mod(det + Mod(2 * f[pre[i]]));
        if (det) f[pre[i - 1]] = Mod(f[pre[i - 1]] + det);
    }

    int ans = 0;
    for (auto [i, v] : f) ans = Mod(ans + v);

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