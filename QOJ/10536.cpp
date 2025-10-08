/**
 * @file 10536.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-07
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

#define maxn 1000005

int fa[maxn], siz[maxn], cnt[maxn], rx[maxn], ry[maxn];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1; i < maxn; i++) fa[i] = i, siz[i] = 1, cnt[i] = 0;

    for (int i = 1; i <= n; i++) cin >> rx[i], rx[i]++;
    for (int i = 1; i <= n; i++) cin >> ry[i], ry[i]++;

    for (int i = 1; i <= n; i++) {
        int x = getfa(rx[i]), y = getfa(ry[i]);
        if (x != y) fa[y] = x, siz[x] += siz[y], cnt[x] += cnt[y];
        cnt[x]++;
    }

    int ans = 0;
    for (int i = 1; i < maxn; i++)
        if (fa[i] == i) ans += siz[i] - 1 + (cnt[i] >= siz[i]);

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
    return 0