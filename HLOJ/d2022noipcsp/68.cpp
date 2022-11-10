/**
 * @file 68.cpp
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

#define maxn 3005

int a[maxn], f[maxn][maxn];
map<int, int> pos;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
    for (int i = n; i; i--) {
        for (int j = i - 1; j; j--) {
            int v = a[i] + a[j], p = (pos.count(v) ? pos[v] : -1);
            ans = max(ans, f[i][j] = 1 + (~p ? f[p][i] : 1));
        }
        pos[a[i]] = i;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("fibonacci.in", "r", stdin), freopen("fibonacci.out", "w", stdout);
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