/**
 * @file 3891.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-12
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

mt19937_64 rnd(114514);
uint64_t val[maxn], sum[2][maxn];

void solve(void) {
    int n, m, q;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) val[i] = rnd();
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, sum[1][y] += val[x];
    uint64_t tot = 0, target = 0;
    for (int i = 1; i <= n; i++) tot += sum[1][i], target += val[i];
    cin >> q;
    while (q--) {
        int t, u, v;
        cin >> t >> u;
        if (t == 1)
            cin >> v, tot -= val[u], sum[1][v] -= val[u], sum[0][v] += val[u];
        else if (t == 2)
            tot -= sum[1][u], sum[0][u] += sum[1][u], sum[1][u] -= sum[1][u];
        else if (t == 3)
            cin >> v, tot += val[u], sum[1][v] += val[u], sum[0][v] -= val[u];
        else
            tot += sum[0][u], sum[1][u] += sum[0][u], sum[0][u] -= sum[0][u];
        cout << (tot == target ? "YES" : "NO") << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("galaxy.in", "r", stdin), freopen("galaxy.out", "w", stdout);
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