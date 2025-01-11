/**
 * @file 100197E.cpp
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

#define maxn 1005
#define maxm 130

typedef pair<int, int> pii;

int a[maxn], mat[maxm][maxm], f[maxn][maxm];
pii pre[maxn][maxm];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int m, s;
    cin >> m >> s;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < s; j++) cin >> mat[i][j];

    for (int i = 1; i <= n + 1; i++)
        for (int j = 0; j < m; j++) f[i][j] = 1e9;
    f[1][0] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
            for (int p = 0; p < s; p++)
                if (f[i + 1][p & (m - 1)] > f[i][j] + abs(a[i] - mat[j][p]))
                    f[i + 1][p & (m - 1)] = f[i][j] + abs(a[i] - mat[j][p]), pre[i + 1][p & (m - 1)] = {j, p};

    int ansp = 0;
    for (int i = 0; i < m; i++)
        if (f[n + 1][ansp] > f[n + 1][i]) ansp = i;

    cout << f[n + 1][ansp] << endl;
    vector<int> ans;
    for (int i = n + 1; i > 1; i--) ans.push_back(pre[i][ansp].second), ansp = pre[i][ansp].first;
    reverse(ans.begin(), ans.end());
    for (auto x : ans) cout << x << ' ';
    cout << endl;

    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("quant.in", "r", stdin), freopen("quant.out", "w", stdout);
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