/**
 * @file arc148_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
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

int fa[maxn], son[maxn], a[maxn], buc[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++) cin >> fa[i], son[fa[i]]++;
    while (q--) {
        int m, ans = 0;
        cin >> m;
        for (int i = 1; i <= m; i++) cin >> a[i], buc[a[i]]++, ans += son[a[i]] + 1;
        for (int i = 1; i <= m; i++) ans -= 2 * buc[fa[a[i]]];
        for (int i = 1; i <= m; i++) buc[a[i]]--;
        cout << ans << endl;
    }
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