/**
 * @file 100197B.cpp
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

#define maxn 70

int f[maxn][maxn], g[maxn][maxn], pre[maxn][maxn];

stack<int> S[maxn];
vector<string> ans;

void mov(int x, int y) {
    int v = S[x].top();
    S[x].pop();
    ans.push_back("move " + to_string(v) + " from " + to_string(x) + " to " + to_string(y));
    if (!S[y].empty()) ans.back() += " atop " + to_string(S[y].top());
    S[y].push(v);
    return;
}

void solve(int m, int n, int from, int to, vector<int> pos) {
    vector<int> x(m + 1);
    for (int i = m; i >= 3; i--) x[i] = pre[i][n - 1], n -= x[i];

    for (int i = m; i >= 3; i--) {
        if (!x[i]) continue;
        vector<int> npos = pos;
        npos.resize(i - 3), npos.push_back(to);
        solve(i, x[i], from, pos[i - 3], npos);
    }

    mov(from, to);

    for (int i = 3; i <= m; i++) {
        if (!x[i]) continue;
        vector<int> npos = pos;
        npos.resize(i - 3), npos.push_back(from);
        solve(i, x[i], pos[i - 3], to, npos);
    }

    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) f[i][j] = g[i][j] = 1e9;
    f[2][1] = 1;

    for (int i = 3; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            f[i][j] = min(int(1e9), 1 + 2 * g[i][j - 1]);
            for (int k = j; k <= n; k++)
                if (g[i][k] > g[i - 1][k - j] + f[i][j]) g[i][k] = g[i - 1][k - j] + f[i][j], pre[i][k] = j;
        }

    vector<int> pos;
    for (int i = 2; i < m; i++) pos.push_back(i);
    for (int i = n; i; i--) S[1].push(i);
    solve(m, n, 1, m, pos);

    cout << ans.size() << endl;
    for (auto x : ans) cout << x << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("hanoi.in", "r", stdin), freopen("hanoi.out", "w", stdout);
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