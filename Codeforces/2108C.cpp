/**
 * @file 2108C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-07
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

int a[maxn], fa[maxn], id[maxn];
bool mark[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void merge(int x, int y) {
    x = getfa(x), y = getfa(y);
    if (x != y) fa[x] = y, mark[y] |= mark[x];
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], id[i] = fa[i] = i, mark[i] = false;
    sort(id + 1, id + n + 1, [&](int x, int y) { return a[x] > a[y]; });

    int ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r + 1 <= n && a[id[r + 1]] == a[id[l]]) r++;

        for (int i = l; i <= r; i++) {
            int p = id[i];
            if (1 < p && a[p - 1] >= a[p]) merge(p - 1, p);
            if (p < n && a[p] <= a[p + 1]) merge(p, p + 1);
        }

        for (int i = l; i <= r; i++) {
            int p = getfa(id[i]);
            if (!mark[p]) mark[p] = true, ans++;
        }
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}