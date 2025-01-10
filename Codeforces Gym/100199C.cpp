/**
 * @file 100199C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
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

#define maxn 500005

int fa[maxn], deg[maxn];
bool vis[maxn];

void solve(void) {
    int n;
    cin >> n;

    for (int i = 2; i <= n; i++) cin >> fa[i], deg[fa[i]]++;

    queue<int> que;
    for (int i = 1; i <= n; i++)
        if (!deg[i]) que.push(i);

    vector<int> ans;
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        if (p == 1) break;

        if (!vis[p] && !vis[fa[p]]) vis[p] = vis[fa[p]] = true, ans.push_back(p);
        if (!--deg[fa[p]]) que.push(fa[p]);
    }

    cout << ans.size() * 1000 << endl;
    sort(ans.begin(), ans.end());
    for (auto i : ans) cout << i << ' ';
    cout << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("grant.in", "r", stdin), freopen("grant.out", "w", stdout);
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