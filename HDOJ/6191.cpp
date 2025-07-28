/**
 * @file 6191.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

using pui = pair<uint32_t, int>;

class Trie {
   private:
    struct Node {
        int ch[2], sum;
        Node(void) { ch[0] = ch[1] = sum = 0; }
    } tree[9000000];
    int root, pcnt;

    int newNode(void) { return tree[pcnt] = Node(), pcnt++; }
    void pushUp(int p) {
        tree[p].sum = 0;
        if (tree[p].ch[0]) tree[p].sum += tree[tree[p].ch[0]].sum;
        if (tree[p].ch[1]) tree[p].sum += tree[tree[p].ch[1]].sum;
        return;
    }

    void update(int& p, int dep, uint32_t v, int delt) {
        if (!p) p = newNode();
        if (dep == -1) return tree[p].sum += delt, void();
        update(tree[p].ch[v >> dep & 1], dep - 1, v, delt);
        return pushUp(p);
    }

    uint32_t query(int p, int dep, uint32_t v) {
        if (dep == -1) return 0;
        int t = v >> dep & 1;
        if (tree[p].ch[t ^ 1] && tree[tree[p].ch[t ^ 1]].sum) return query(tree[p].ch[t ^ 1], dep - 1, v) | (1 << dep);
        return query(tree[p].ch[t], dep - 1, v);
    }

   public:
    void reset(void) { pcnt = 1, root = newNode(); }
    void update(uint32_t v, int delt) { return update(root, 31, v, delt); }
    uint32_t query(uint32_t v) { return query(1, 31, v); }
} trie;

uint32_t a[maxn], ans[maxn];
int siz[maxn], son[maxn];
vector<vector<int>> graph;
vector<vector<pui>> ques;

void dfs1(int p) {
    siz[p] = 1, son[p] = 0;
    for (auto q : graph[p]) {
        dfs1(q), siz[p] += siz[q];
        if (!son[p] || siz[q] > siz[son[p]]) son[p] = q;
    }
    return;
}
void dfs2(int p, int delt) {
    trie.update(a[p], delt);
    for (auto q : graph[p]) dfs2(q, delt);
    return;
}
void dfs3(int p) {
    for (auto q : graph[p])
        if (q != son[p]) dfs3(q), dfs2(q, -1);
    if (son[p]) dfs3(son[p]);
    trie.update(a[p], +1);
    for (auto q : graph[p])
        if (q != son[p]) dfs2(q, +1);
    for (auto [x, id] : ques[p]) ans[id] = trie.query(x);
    return;
}

void solve(void) {
    int n, q;
    while (cin >> n >> q) {
        for (int i = 1; i <= n; i++) cin >> a[i];

        graph.clear(), graph.resize(n + 1);
        for (int i = 2, x; i <= n; i++) cin >> x, graph[x].push_back(i);

        ques.clear(), ques.resize(n + 1);
        for (int i = 1, u, x; i <= q; i++) cin >> u >> x, ques[u].emplace_back(x, i);

        trie.reset();
        dfs1(1), dfs3(1);

        for (int i = 1; i <= q; i++) cout << ans[i] << endl;
    }
    return;
}

bool mem2;

int main() {
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