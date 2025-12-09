/**
 * @file 15314.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 30005

vector<vector<int>> graph;
int dfni[maxn], dfno[maxn], fa[maxn], dep[maxn], sum[maxn];

bool query(int p, int d) {
    cout << "? " << p << ' ' << d << endl;
    int ret;
    cin >> ret;
    return ret;
}

int dfnt;
void dfs1(int p) {
    dfni[p] = ++dfnt;
    for (auto q : graph[p]) dep[q] = dep[p] + 1, dfs1(q);
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);

    for (int i = 2; i <= n; i++) cin >> fa[i], graph[fa[i]].push_back(i);
    dfs1(1);

    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) r = max(r, dep[i]);
    while (l < r) {
        int mid = (l + r) >> 1;
        query(1, mid) ? (r = mid) : (l = mid + 1);
    }

    vector<int> rec;
    for (int i = 1; i <= n; i++)
        if (dep[i] == l) rec.push_back(i);

    while (rec.size() > 1) {
        for (int i = 1; i <= n; i++) sum[i] = 0;
        for (auto p : rec) sum[p] = 1;
        for (int i = n; i >= 1; i--)
            for (auto j : graph[i]) sum[i] += sum[j];

        int xp = -1, v = 0;
        for (int i = 2; i <= n; i++)
            if (v < min(sum[i], sum[1] - sum[i])) v = min(sum[i], sum[1] - sum[i]), xp = i;

        vector<int> rd, ru;
        for (auto p : rec)
            if (dfni[xp] <= dfni[p] && dfni[p] <= dfno[xp])
                rd.push_back(p);
            else
                ru.push_back(p);

        int x = rd.front();
        int ret = query(x, 2 * (dep[x] - dep[xp]));
        rec = ret ? rd : ru;
    }

    cout << "! " << rec.front() << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
