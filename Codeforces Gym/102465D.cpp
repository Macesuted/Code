/**
 * @file 102465D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

vector<int> a[maxn];
int xu[maxn], xd[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n, m, q, su = 0, sd = 0;
    cin >> n >> m >> q;
    int64_t cur = n - 1, ans = INT64_MAX;
    for (int i = 1, x, y; i <= q; i++) cin >> x >> y, a[y].push_back(x);

    for (int y = m - 1; ~y; y--)
        for (auto x : a[y]) {
            if (!xu[x]) cur += y * 2, su++;
            xu[x]++;
        }

    for (int y = 0; y < m; y++) {
        ans = min(ans, cur);
        for (auto x : a[y]) {
            xu[x]--;
            if (!xu[x]) su--;
            if (!xd[x]) sd++;
            xd[x]++;
        }
        cur += 2 * (sd - su);
    }

    cout << ans << endl;

    return 0;
}