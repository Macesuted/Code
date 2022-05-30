/**
 * @file 3355.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define maxlgn 20

typedef pair<int, int> pii;

vector<pii> graph[maxn];
int fa[maxn][maxlgn], dep[maxn], dfni[maxn], dfno[maxn], pnt[maxn], f[maxn];
vector<int> ans;

int dfnt = 0;
void dfs(int p, int pre = 0) {
    fa[p][0] = pre, dep[p] = dep[pre] + 1, dfni[p] = ++dfnt;
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : graph[p])
        if (i.first != pre) dfs(i.first, p);
    dfno[p] = dfnt;
    return;
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int calc(int p, int k, int pre = -1) {
    int tot = f[p];
    for (auto i : graph[p])
        if (i.first != pre) {
            int ret = calc(i.first, k, p);
            if (ret >= k) ans.push_back(i.second);
            tot += ret;
        }
    return tot;
}

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].emplace_back(y, i), graph[y].emplace_back(x, i);
    dfs(1);
    while (m--) {
        int s;
        cin >> s;
        for (int i = 1; i <= s; i++) cin >> pnt[i];
        sort(pnt + 1, pnt + s + 1, [&](int x, int y) { return dfni[x] < dfni[y]; });
        auto in = [&](int x, int y) { return dfni[x] <= dfni[y] && dfni[y] <= dfno[x]; };
        int top = pnt[1];
        for (int i = 2; i <= s; i++) {
            int t = LCA(pnt[i], pnt[i - 1]);
            if (in(t, top)) f[top]++, f[top = t]--;
            f[pnt[i]]++, f[t]--;
        }
    }
    calc(1, k);
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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