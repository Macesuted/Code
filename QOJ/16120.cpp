/**
 * @file 16120.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int vl[maxn], vr[maxn];

vector<int> graph[maxn];
int siz[maxn];
bool ban[maxn];

vector<int> tree[maxn];
unordered_map<int, int> dep[maxn];
priority_queue<int64_t, vector<int64_t>, greater<int64_t>> S[maxn], eS[maxn];
int fa[maxn];
int64_t ans[maxn];

void getSiz(int p, int pre = -1) {
    siz[p] = 1;
    for (auto q : graph[p])
        if (!ban[q] && q != pre) getSiz(q, p), siz[p] += siz[q];
    return;
}
int findRoot(int p, int tot, int pre = -1) {
    for (auto q : graph[p])
        if (!ban[q] && q != pre && siz[q] > tot - siz[q]) return findRoot(q, tot, p);
    return p;
}
int getRoot(int p) { return getSiz(p), findRoot(p, siz[p]); }

void dfs(unordered_map<int, int>& dep, int p, int pre = -1) {
    for (auto q : graph[p])
        if (!ban[q] && q != pre) dep[q] = dep[p] + 1, dfs(dep, q, p);
    return;
}

int build(int p) {
    p = getRoot(p);

    dep[p][p] = 0, dfs(dep[p], p);

    ban[p] = true;
    for (auto q : graph[p])
        if (!ban[q]) q = build(q), tree[p].push_back(q), fa[q] = p;

    return p;
}

void simpf(int q) {
    while (eS[q].size() && eS[q].top() == S[q].top()) {
        S[q].pop(), eS[q].pop();
    }
}

int64_t query(int p) {
    int64_t ret = INT64_MAX;
    for (int q = p; q; q = fa[q]) {
        simpf(q);
        if (!S[q].empty()) ret = min(ret, S[q].top() + dep[q][p] + 1);
    }
    return ret;
}
void insert(int p) {
    for (int q = p; q; q = fa[q]) S[q].emplace(ans[p] + dep[q][p]);
    return;
}
void erase(int p) {
    for (int q = p; q; q = fa[q]) eS[q].emplace(ans[p] + dep[q][p]);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) cin >> vl[i] >> vr[i];

    if ((vl[1] <= vl[n] && vl[n] <= vr[1]) || (vl[n] <= vl[1] && vl[1] <= vr[n])) vl[n] = vr[n] = vr[1];

    if (vl[1] > vr[n])
        for (int i = 1; i <= n; i++) tie(vl[i], vr[i]) = make_pair(-vr[i], -vl[i]);

    vector<int> vs;
    for (int i = 1; i <= n; i++) vs.push_back(vl[i]), vs.push_back(vr[i]);
    sort(vs.begin(), vs.end()), vs.resize(unique(vs.begin(), vs.end()) - vs.begin());

    for (int i = 1; i <= n; i++)
        vl[i] = lower_bound(vs.begin(), vs.end(), vl[i]) - vs.begin(),
        vr[i] = lower_bound(vs.begin(), vs.end(), vr[i]) - vs.begin();

    vector<vector<int>> ops(vs.size());
    for (int i = 1; i <= n; i++) {
        if (vr[i] < vr[1]) continue;
        if (vl[i] < vr[1]) vl[i] = vr[1];

        ops[vl[i]].push_back(+i), ops[vr[i]].push_back(-i);
    }

    build(1);

    for (int v = vr[1]; v <= vl[n]; v++) {
        for (auto x : ops[v]) {
            if (x < 0) continue;
            ans[x] = (x == 1 ? 0 : query(x));
            insert(x);
        }

        for (auto x : ops[v]) {
            if (x > 0) continue;
            x = -x;
            erase(x);
        }
    }

    cout << ans[n] - 1 << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
