/**
 * @file arc204_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-17
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

#define maxn 10005

int p[maxn], f[maxn][maxn];
bool vis[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n * k; i++) cin >> p[i];

    int ans = 0;

    for (int i = 1; i <= n * k; i++) {
        if (p[i] == i || vis[i]) continue;

        int x = i;
        vector<int> path;
        while (p[x] != i) path.push_back(x), vis[x = p[x]] = true;
        path.push_back(x);

        int m = path.size();
        for (int i = 0; i < m; i++) path.push_back(path[i]);

        vector<int> nxt(2 * m, -1), lst(n, 2 * m);
        for (int i = 2 * m - 1; ~i; i--) nxt[i] = lst[path[i] % n], lst[path[i] % n] = i;

        for (int l = 2 * m - 2; ~l; l--) {
            vector<int> nxts;
            int p = nxt[l];
            while (p < 2 * m) nxts.push_back(p), p = nxt[p];
            nxts.push_back(2 * m);

            for (int r = l + 1; r <= min(2 * m - 1, l + m - 1); r++) {
                f[l][r] = f[l + 1][r];
                for (int t = 0; t < (int)nxts.size() && nxts[t] <= r; t++)
                    f[l][r] = max(f[l][r], 1 + f[l][nxts[t] - 1] + f[nxts[t]][r]);
            }
        }

        int mxv = 0;
        for (int l = 0, r = m - 1; r < 2 * m; l++, r++) mxv = max(mxv, f[l][r]);

        ans += mxv;
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