/**
 * @file B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

int a[maxn], pos[maxn], rig[maxn];
bool vis[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i, vis[i] = false;

    set<int> S, Spos;
    for (int i = 1; i <= n && k >= 2; i++) {
        if (a[i] == i) continue;

        if (!vis[i]) vis[i] = true, S.insert(a[i]), Spos.insert(i), k--;
        if (!vis[pos[i]]) vis[pos[i]] = true, S.insert(i), Spos.insert(pos[i]), k--;
    }

    auto it = S.begin();
    for (int i = 1; i <= n; i++)
        if (vis[i]) a[i] = *it++;

    if (k == 1) {
        rig[n + 1] = n + 1;
        for (int i = n; i >= 1; i--) rig[i] = min(a[i], rig[i + 1]);

        for (int i = 1; i <= n; i++) {
            if (a[i] == i) continue;
            if (vis[i]) {
                if (rig[i + 1] > a[i]) continue;
                int p = pos[rig[i + 1]];
                vis[p] = true, S.insert(a[p]), Spos.insert(p);
                break;
            }

            auto it = Spos.lower_bound(i);
            if (it == Spos.end() || a[*it] > a[i]) continue;
            vis[i] = true, S.insert(a[i]), Spos.insert(i);
            break;
        }
    }

    it = S.begin();
    for (int i = 1; i <= n; i++)
        if (vis[i]) a[i] = *it++;

    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
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
