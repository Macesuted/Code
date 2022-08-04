/**
 * @file 2113.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 40005
#define maxlgn 18

typedef tuple<int, int, int, int> tiiii;
typedef tuple<int, int, int, int, int> tiiiii;

class SegmentTree {
   private:
    struct Node {
        int val;
        bool cls;
    };

    Node tree[maxn << 2];
    int n;

    void clear(int p) { return tree[p].cls = true, tree[p].val = 0, void(); }
    void pushDown(int p) {
        if (tree[p].cls) clear(p << 1), clear(p << 1 | 1), tree[p].cls = false;
        tree[p << 1].val += tree[p].val, tree[p << 1 | 1].val += tree[p].val, tree[p].val = 0;
        return;
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return tree[p].val += v, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    int query(int p, int l, int r, int qp) {
        if (l == r) return tree[p].val;
        pushDown(p);
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void clear(void) { return clear(1); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    int query(int p) { return query(1, 1, n, p); }
} ST;

vector<int> graph[maxn];
int fa[maxn][maxlgn], dep[maxn], ans[maxn], dfni[maxn], dfno[maxn], n, m, q;
vector<tiiiii> node;

int dfnt = 0;
void dfs(int p, int pre = 0) {
    dfni[p] = ++dfnt;
    fa[p][0] = pre, dep[p] = dep[pre] + 1;
    for (int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : graph[p])
        if (i != pre) dfs(i, p);
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
int son(int x, int y) {
    for (int i = maxlgn - 1; ~i; i--)
        if (dep[fa[y][i]] > dep[x]) y = fa[y][i];
    return y;
}

void solve(vector<tiiiii>::iterator l, vector<tiiiii>::iterator r, vector<tiiii> ques) {
    if (l + 1 == r || ques.empty()) {
        for (auto i : ques) ans[get<3>(i)] = get<4>(*r);
        return;
    }
    auto mid = l + (r - l) / 2;
    vector<tiiii> lin;
    for (auto i = l + 1; i <= mid; i++)
        lin.emplace_back(get<0>(*i), get<2>(*i), get<3>(*i), +1),
            lin.emplace_back(get<1>(*i) + 1, get<2>(*i), get<3>(*i), -1);
    sort(lin.begin(), lin.end());
    ST.clear();
    vector<tiiii> ql, qr;
    for (auto i = ques.begin(), j = lin.begin(); i != ques.end(); i++) {
        while (j != lin.end() && get<0>(*i) >= get<0>(*j)) ST.update(get<1>(*j), get<2>(*j), get<3>(*j)), j++;
        int ret = ST.query(get<1>(*i));
        ret >= get<2>(*i) ? ql.push_back(*i) : (get<2>(*i) -= ret, qr.push_back(*i));
    }
    return solve(l, mid, ql), solve(mid, r, qr);
}

void solve(void) {
    cin >> n >> m >> q;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs(1);
    vector<tiiii> ques;
    ques.resize(q);
    for (int i = 1, x, y, c; i <= m; i++) {
        cin >> x >> y >> c;
        int t = LCA(x, y);
        if (t == y) swap(x, y);
        if (t == x) {
            int z = son(x, y);
            if (dfni[z] > 1) node.emplace_back(1, dfni[z] - 1, dfni[y], dfno[y], c);
            if (dfno[z] < n) node.emplace_back(dfni[y], dfno[y], dfno[z] + 1, n, c);
        } else {
            if (dfni[x] > dfni[y]) swap(x, y);
            node.emplace_back(dfni[x], dfno[x], dfni[y], dfno[y], c);
        }
    }
    sort(node.begin(), node.end(), [](const tiiiii& a, const tiiiii& b) { return get<4>(a) < get<4>(b); });
    for (int i = 0, x, y; i < q; i++) {
        cin >> x >> y >> get<2>(ques[i]);
        if (dfni[x] > dfni[y]) swap(x, y);
        get<0>(ques[i]) = dfni[x], get<1>(ques[i]) = dfni[y], get<3>(ques[i]) = i;
    }
    sort(ques.begin(), ques.end());
    ST.resize(n), solve(node.begin() - 1, node.end() - 1, ques);
    for (int i = 0; i < q; i++) cout << ans[i] << endl;
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
