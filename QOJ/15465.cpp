/**
 * @file 15465.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 5005

vector<int> graph[maxn];
int siz[maxn];
int64_t f[maxn];

void dfs(int p, int pre = -1) {
    vector<int> rec;
    siz[p] = 1, f[p] = 0;
    for (auto q : graph[p]) {
        if (q == pre) continue;
        dfs(q, p);
        rec.push_back(siz[q]), siz[p] += siz[q], f[p] += f[q] + 1;
    }

    sort(rec.begin(), rec.end(), greater<int>());
    vector<int> vl, vr;
    for (size_t i = 0; i < rec.size(); i++) ((i & 1) ? vr : vl).push_back(rec[i]);

    for (size_t i = 0; i < vl.size(); i++) f[p] += vl[i] * i;
    for (size_t i = 0; i < vr.size(); i++) f[p] += (int64_t)vr[i] * (i + (pre != -1));

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    dfs(1);
    cout << f[1] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
