/**
 * @file 238.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 200005
#define maxm 105

string s;
int c[maxm], blk[maxn], cnt1[maxn];
bool f[maxn][maxm], g[maxn][maxm], cnt0[maxn];

void dfs(int n, int m) {
    if (!n) return;
    if (g[n][m]) return;
    g[n][m] = true;
    if (s[n] != 'X' && f[n - 1][m]) cnt0[n] = true, dfs(n - 1, m);
    if (m && blk[n] >= c[m] && s[n - c[m]] != 'X' && f[max(0, n - c[m] - 1)][m - 1])
        cnt0[n - c[m]] = true, cnt1[n - c[m] + 1]++, cnt1[n + 1]--, dfs(max(0, n - c[m] - 1), m - 1);
    return;
}

string solve_puzzle(string _s, vector<int> _c) {
    int n = _s.size(), m = _c.size();
    s = " " + _s;
    for (int i = 1; i <= m; i++) c[i] = _c[i - 1];
    for (int i = 1; i <= n; i++) blk[i] = (s[i] == '_' ? 0 : blk[i - 1] + 1);
    f[0][0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (s[i] != 'X') f[i][j] = f[i - 1][j];
            if (j && blk[i] >= c[j] && s[i - c[j]] != 'X') f[i][j] |= f[max(0, i - c[j] - 1)][j - 1];
        }
    dfs(n, m);
    string ans;
    for (int i = 1; i <= n; i++) ans.push_back((cnt1[i] += cnt1[i - 1]) && cnt0[i] ? '?' : "X_"[cnt0[i]]);
    return ans;
}