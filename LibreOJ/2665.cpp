/**
 * @file 2665.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-15
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

#define maxn 200005

int a[maxn], b[maxn], c[maxn], f[maxn];
bool g[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, t; i <= n; i++) cin >> t, b[t] = i;
    for (int i = 1; i <= n; i++) c[a[i] = b[a[i]]] = i;
    g[1] = true;
    for (int i = 2; i < n; i++)
        if (c[i] > c[i + 1]) g[i] = true;
    for (int i = 1; i < n; i++)
        if (a[i] + 1 < a[i + 1]) f[a[i]]++, f[a[i + 1]]--;
    double ans = 1;
    for (int i = 1, pre = 0; i < n; i++) {
        pre += f[i];
        if (g[i])
            ans += 1;
        else if (pre == 0)
            ans += 0.5;
    }
    cout << setprecision(3) << setiosflags(ios::fixed) << ans << endl;
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