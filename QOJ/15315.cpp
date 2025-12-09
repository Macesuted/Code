/**
 * @file 15315.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

vector<vector<int>> graph;
int a[maxn], dep[maxn], fa[maxn];
bool vis[maxn];

vector<int> ans;
int sum;
void dfs(int p) {
    ans.push_back(p), a[p] ^= 1;
    vis[p] = true;
    for (auto q : graph[p]) {
        if (vis[q]) {
            if (sum && dep[q] <= dep[p] && !((dep[p] - dep[q]) & 1)) {
                sum = 0;
                int x = p;
                while (x != q) ans.push_back(x = fa[x]), a[x] ^= 1;
                ans.push_back(p), a[p] ^= 1;
            }
            continue;
        }
        dep[q] = dep[p] + 1, fa[q] = p, dfs(q);
        ans.push_back(p), a[p] ^= 1;
        if (a[q]) {
            ans.push_back(q), a[q] ^= 1;
            ans.push_back(p), a[p] ^= 1;
        }
    }
    return;
}

void solve(void) {
    int n, m, r;
    cin >> n >> m >> r;

    for (int i = 1; i <= n; i++) cin >> a[i], a[i] &= 1;

    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    ans.clear(), sum = 0;
    for (int i = 1; i <= n; i++) sum ^= a[i], vis[i] = false;
    a[r] ^= 1, dep[r] = 0, dfs(r);

    for (int i = 1; i <= n; i++)
        if (a[i]) return cout << "No" << endl, void();

    ans.pop_back();
    reverse(ans.begin(), ans.end());

    cout << "Yes" << endl << ans.size() << endl;
    for (auto x : ans) cout << x << ' ';
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
