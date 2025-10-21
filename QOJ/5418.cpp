/**
 * @file 5418.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005
#define maxlgn 20

class STList {
   private:
    int f[maxlgn][maxn], lgLen[maxn];

   public:
    void build(int n, int a[]) {
        for (int i = 2; i <= n; i++) lgLen[i] = lgLen[i >> 1] + 1;
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int t = 1; t <= lgLen[n]; t++)
            for (int i = 0; i + (1 << t) <= n; i++) f[t][i] = min(f[t - 1][i], f[t - 1][i + (1 << (t - 1))]);
        return;
    }
    int64_t getMin(int l, int r) {
        int t = lgLen[r - l + 1];
        return min(f[t][l], f[t][r - (1 << t) + 1]);
    }
} STL;

int a[maxn], dep[maxn], fa[maxn][maxlgn], dfni[maxn];
vector<vector<int>> graph, ngraph, rec;

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int dfnt = 0;
void dfs1(int p, int pre = 0) {
    rec[dep[p] = dep[pre] + 1].push_back(p), dfni[p] = ++dfnt, fa[p][0] = pre;
    for (int t = 1; t < maxlgn; t++) fa[p][t] = fa[fa[p][t - 1]][t - 1];
    for (auto q : graph[p])
        if (q != pre) dfs1(q, p);
    return;
}

int64_t dfs2(int p, int tar) {
    if (ngraph[p].empty()) return STL.getMin(0, tar - 1);
    int64_t sum = 0;
    for (auto q : ngraph[p]) sum += dfs2(q, tar);
    return min(sum, STL.getMin(tar - dep[p], tar - 1));
}

void solve(void) {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) cin >> a[i];
    STL.build(n, a);

    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    rec.clear(), rec.resize(n + 1);
    dfnt = 0, dfs1(1);

    int64_t ans = 0;

    ngraph.clear(), ngraph.resize(n + 1);
    for (int d = 1; d <= n; d++) {
        if (rec[d].empty()) continue;

        sort(rec[d].begin(), rec[d].end(), [&](int x, int y) -> bool { return dfni[x] < dfni[y]; });

        vector<int> tmp;
        stack<int> S;
        int head = 1;
        for (auto x : rec[d]) {
            int t = lca(head, x);
            while (!S.empty() && dep[S.top()] >= dep[t])
                tmp.push_back(S.top()), ngraph[S.top()].push_back(head), head = S.top(), S.pop();
            if (head != t) tmp.push_back(t), ngraph[t].push_back(head), head = t;
            if (x != t) S.push(head), head = x;
        }

        while (!S.empty()) tmp.push_back(S.top()), ngraph[S.top()].push_back(head), head = S.top(), S.pop();

        ans += dfs2(1, d);

        for (auto x : tmp) ngraph[x].clear();
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
