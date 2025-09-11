/**
 * @file 7579.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 50005

int a[maxn], k[maxn], tim[maxn], f[maxn], g[maxn], ans[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> k[i], tim[k[i]] = i;
    for (int i = 1; i <= n; i++) f[i] = tim[i];

    for (int i = 1; i <= n; i++) ans[i] = 0;
    ans[1] = 1;

    for (int t = 2;; t++) {
        map<int, int> rec;
        for (int i = 1; i <= n; i++) {
            auto p = rec.lower_bound(a[i]);
            int ins = f[i];
            if (p == rec.begin()) {
                f[i] = INT_MAX;
                if (ins != INT_MAX) {
                    rec[a[i]] = ins;
                    p = rec.upper_bound(a[i]);
                    while (p != rec.end() && p->second >= ins) p = rec.erase(p);
                }
            } else {
                f[i] = max(tim[i], (--p)->second);
                if (ins < p->second) {
                    rec[a[i]] = ins;
                    p = rec.upper_bound(a[i]);
                    while (p != rec.end() && p->second >= ins) p = rec.erase(p);
                }
            }
        }
        int minv = INT_MAX;
        for (int i = 1; i <= n; i++) minv = min(minv, f[i]);
        if (minv == INT_MAX) break;
        ans[minv] = t;
    }

    for (int i = 1; i <= n; i++)
        if (!ans[i]) ans[i] = ans[i - 1];

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
