/**
 * @file 4839.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005
#define maxlgn 20

using pii = pair<int, int>;

class FenwickTree {
   private:
    int a[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) a[i] += v;
        return;
    }
    int qry(int p) {
        int ans = 0;
        for (int i = p; i; i -= i & -i) ans += a[i];
        return ans;
    }
} SGT;

vector<int> graph[maxn];
vector<pii> ques[maxn], modi[maxn];
int64_t ans[maxn];
int64_t n;
int dfni[maxn], dfno[maxn], fa[maxn][maxlgn], dep[maxn];

int dfnt = 0;
void dfs1(int p, int pre = 0) {
    dfni[p] = ++dfnt;
    fa[p][0] = pre, dep[p] = dep[pre] + 1;
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];

    if (pre != 0) ques[p - 1].emplace_back(p, -1), ques[pre - 1].emplace_back(p, +1);

    for (auto q : graph[p]) {
        if (q == pre) continue;
        dfs1(q, p);
    }

    dfno[p] = dfnt;
    return;
}
void dfs2(int p) {
    for (auto q : graph[p])
        if (q != fa[p][0]) ans[q] += ans[p], dfs2(q);
    return;
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int t = maxlgn - 1; ~t; t--)
        if (dep[fa[x][t]] >= dep[y]) x = fa[x][t];
    if (x == y) return x;
    for (int t = maxlgn - 1; ~t; t--)
        if (fa[x][t] != fa[y][t]) x = fa[x][t], y = fa[y][t];
    return fa[x][0];
}

void solve(void) {
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    ans[1] = n * (n - 1) / 2 + n;

    dfs1(1);

    for (int i = 1; i * i <= n; i++)
        for (int j = i + 1; i * j < n; j++) {
            modi[i * j].emplace_back(i, j);
            int t = lca(i, j);
            ans[1] -= i * j < t;
        }

    for (int v = 0; v < n; v++) {
        for (auto [x, y] : modi[v]) SGT.add(dfni[x], +1), SGT.add(dfni[y], +1), SGT.add(dfni[lca(x, y)], -2);
        for (auto [p, coef] : ques[v]) {
            ans[p] += coef * (SGT.qry(dfno[p]) - SGT.qry(dfni[p] - 1));
        }
    }

    dfs2(1);

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}