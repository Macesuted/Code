/**
 * @file 212.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 300005

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

vector<int> graph[maxn];
vector<pii> upd, ques;
int siz[maxn], son[maxn], dep[maxn], fa[maxn], top[maxn], dfni[maxn], dfno[maxn], ans[maxn];

void dfs1(int p, int pre = 0) {
    fa[p] = pre, siz[p] = 1, dep[p] = dep[pre] + 1;
    for (auto i : graph[p]) {
        if (i == pre) continue;
        dfs1(i, p), siz[p] += siz[i];
        if (siz[i] > siz[son[p]]) son[p] = i;
    }
    return;
}
int dfnt = 0;
void dfs2(int p, int _top) {
    top[p] = _top, dfni[p] = ++dfnt;
    if (son[p]) dfs2(son[p], _top);
    for (auto i : graph[p])
        if (i != fa[p] && i != son[p]) dfs2(i, i);
    dfno[p] = dfnt;
    return;
}
void dfs3(int p) {
    for (auto i : graph[p])
        if (i != fa[p]) dfs3(i), ques.emplace_back(i, -p), ques.emplace_back(i, i);
    return;
}
void dfs4(int p) {
    for (auto i : graph[p])
        if (i != fa[p]) ans[i] += ans[p], dfs4(i);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i * i < n; i++)
        for (int j = i + 1; i * j < n; j++) upd.emplace_back(i, j);
    sort(upd.begin(), upd.end(), [](pii a, pii b) { return a.first * a.second < b.first * b.second; });
    dfs1(1), dfs2(1, 1), dfs3(1);
    sort(ques.begin(), ques.end(), [](pii a, pii b) { return abs(a.second) < abs(b.second); });
    for (int v = 1, i = 0, j = 0; v <= n; v++) {
        while (j != (int)ques.size() && abs(ques[j].second) == v)
            ans[ques[j].first] +=
                ques[j].second / abs(ques[j].second) * (FT.sum(dfno[ques[j].first]) - FT.sum(dfni[ques[j].first] - 1)),
                j++;
        while (i != (int)upd.size() && upd[i].first * upd[i].second == v) {
            int x = upd[i].first, y = upd[i].second;
            FT.add(dfni[x], +1), FT.add(dfni[y], +1);
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap(x, y);
                x = fa[top[x]];
            }
            if (dep[x] < dep[y]) swap(x, y);
            FT.add(dfni[y], -2);
            ans[1] += (upd[i].first * upd[i].second < y);
            i++;
        }
    }
    dfs4(1);
    int64_t tot = int64_t(n + 1) * n / 2;
    for (int i = 1; i <= n; i++) cout << tot - ans[i] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("path.in", "r", stdin), freopen("path.out", "w", stdout);
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