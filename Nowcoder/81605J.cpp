/**
 * @file 81605J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005

vector<vector<int>> X, Y;
int dfni[maxn], dfno[maxn], fa[maxn], f[maxn], pre[maxn];

int dfnt;
void dfs(int p, int pre = 0) {
    dfni[p] = ++dfnt, fa[p] = pre;
    for (auto i : Y[p])
        if (i != fa[p]) dfs(i, p);
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n;
    cin >> n;
    X.clear(), Y.clear(), X.resize(n + 1), Y.resize(n + 1);
    for (int i = 1; i <= n; i++) pre[i] = 0;
    for (int i = 2, x; i <= n; i++) cin >> x, X[i].push_back(x), X[x].push_back(i);
    for (int i = 2, x; i <= n; i++) cin >> x, Y[i].push_back(x), Y[x].push_back(i);
    dfnt = 0, dfs(1);
    for (int i = 1; i <= n; i++) {
        f[i] = 0;
        set<int> S;
        S.insert(n + 1);
        for (auto j : X[i]) S.insert(dfni[j]);
        for (auto j : Y[i]) {
            bool fnd = false;
            if (fa[i] == j)
                fnd = (*S.lower_bound(1) < dfni[i] || *S.lower_bound(dfno[i] + 1) <= n);
            else
                fnd = (*S.lower_bound(dfni[j]) <= dfno[j]);
            if (!fnd) {
                if (f[i]) return cout << -1 << endl, void();
                f[i] = j;
            }
        }
        if (f[i]) {
            if (f[i] == fa[i])
                pre[dfni[i]]++, pre[dfno[i] + 1]--;
            else
                pre[1]++, pre[dfni[f[i]]]--, pre[dfno[f[i]] + 1]++, pre[n + 1]--;
        }
    }
    pre[0] = 0;
    for (int i = 1; i <= n; i++) pre[i] += pre[i - 1];
    for (int i = 1; i <= n; i++)
        if (!pre[dfni[i]]) return cout << i << endl, void();
    cout << -1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}