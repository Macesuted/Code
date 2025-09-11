/**
 * @file 7588.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

struct Node {
    int64_t a, b;
    int id;

    bool operator<(const Node& o) const {
        if ((a < b) != (o.a < o.b)) return a < b;
        if (a < b) return a == o.a ? id < o.id : a < o.a;
        return b == o.b ? id < o.id : b > o.b;
    }
};

Node a[maxn];
int fa[maxn], f[maxn];
vector<vector<int>> graph;

void dfs(int p, int pre = 0) {
    fa[p] = pre;
    for (auto q : graph[p])
        if (q != pre) dfs(q, p);
    return;
}

int getfa(int p) { return f[p] == p ? p : f[p] = getfa(f[p]); }

void solve(void) {
    int n;
    cin >> n;

    graph.clear(), graph.resize(n + 1);

    a[1] = {0, 0, 1};
    for (int i = 2; i <= n; i++) cin >> a[i].a >> a[i].b, a[i].id = i;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    dfs(1);

    for (int i = 1; i <= n; i++) f[i] = i;

    set<Node> ids;

    for (int i = 2; i <= n; i++) ids.insert(a[i]);

    while (!ids.empty()) {
        int p = ids.begin()->id;
        ids.erase(ids.begin());
        int q = f[p] = getfa(fa[p]);
        if (q != 1) ids.erase(a[q]);
        int64_t mnv = -a[q].a, sum = -a[q].a + a[q].b;
        mnv = min(mnv, sum - a[p].a), sum += -a[p].a + a[p].b;
        a[q] = {-mnv, sum - mnv, q};
        if (q != 1) ids.insert(a[q]);
    }

    cout << a[1].a << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
