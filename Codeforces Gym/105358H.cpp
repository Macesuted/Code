/**
 * @file 105358H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-22
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

#define maxn 500005

typedef pair<int, int> pii;

vector<pii> rec[maxn];
int f[maxn], g[maxn];

int Mod(int x, int mod) { return x >= mod ? x - mod : x; }
uint64_t getSum(int l, int r) { return uint64_t(l + r) * (r - l + 1) / 2; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y, v; i <= n; i++) cin >> x >> y >> v, rec[x].emplace_back(y, Mod(v, n));

    f[0] = 0;
    for (int i = 1; i < n; i++) f[i] = n + 1;

    uint64_t ans = 0, sum = 0;
    int maxv = n + 1;
    for (int i = 1; i <= n; i++) {
        for (auto [p, v] : rec[i]) {
            if (p >= maxv) continue;

            for (int x = 0; x < n; x++) g[x] = f[x];
            for (int x = 0, y = v; x < n; x++, y = Mod(y + 1, n)) {
                if (f[y] <= max(g[x], p)) continue;
                sum -= getSum(f[y], n) * y;
                f[y] = max(g[x], p);
                sum += getSum(f[y], n) * y;
            }
            maxv = 0;
            for (int x = 0; x < n; x++) maxv = max(maxv, f[x]);
        }
        ans += sum * i;
    }
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}