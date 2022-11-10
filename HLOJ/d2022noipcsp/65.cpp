/**
 * @file 65.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005
#define mod 1000000007

int a[maxn], f[maxn], rig[maxn];
int64_t pre[maxn];
map<int64_t, int> pos;

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];
    for (int i = n - 1; i; i--) pos[pre[i]] = i, rig[i] = (pos.count(pre[i - 1]) ? pos[pre[i - 1]] : 0);
    f[0] = 1, f[1] = mod - 1;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        if (rig[i]) f[rig[i]] = Mod(f[rig[i]] + mod - ans), f[rig[i] + 1] = Mod(f[rig[i] + 1] + ans);
        f[i] = (f[i] + f[i - 1] * 2LL) % mod, ans = Mod(ans + f[i - 1]);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("segment.in", "r", stdin), freopen("segment.out", "w", stdout);
#endif
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