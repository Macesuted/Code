/**
 * @file 1704E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-31
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

#define maxn 1005
#define mod 998244353

int64_t a[maxn];
int indeg[maxn], id[maxn];
vector<int> graph[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], graph[i].clear(), indeg[i] = 0;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), indeg[y]++;
    bool chk = true;
    for (int j = 1; j <= n; j++) chk &= (a[j] == 0);
    if (chk) return cout << 0 << endl, void();
    static queue<int> que;
    while (!que.empty()) que.pop();
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) que.push(i);
    int cnt = 0;
    while (!que.empty()) {
        int p = id[++cnt] = que.front();
        que.pop();
        for (auto i : graph[p])
            if (!--indeg[i]) que.push(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = n; j; j--) {
            int u = id[j];
            if (!a[u]) continue;
            a[u]--;
            for (auto k : graph[u]) a[k]++;
        }
        bool chk = true;
        for (int j = 1; j <= n; j++) chk &= (a[j] == 0);
        if (chk) return cout << i << endl, void();
    }
    for (int i = 1; i <= n; i++) {
        int u = id[i];
        for (auto j : graph[u]) a[j] = (a[j] + a[u]) % mod;
    }
    cout << (a[id[n]] + n) % mod << endl;
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