/**
 * @file 2116.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-02
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

#define maxn 150005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t ori, sum, laz;
        int ver;
        Node(int ver_) { l = r = nullptr, ori = sum = laz = 0, ver = ver_; }
    };

    vector<Node *> roots;
    int n, ver;

    void checkVer(Node *&p) {
        if (p->ver != ver) p = new Node(*p), p->ver = ver;
        return;
    }
    void update(Node *&p, int64_t v) { return checkVer(p), p->sum += p->ori * v, p->laz += v, void(); }
    void pushDown(Node *&p) { return checkVer(p), update(p->l, p->laz), update(p->r, p->laz), p->laz = 0, void(); }
    void pushUp(Node *p) { return p->ori = p->l->ori + p->r->ori, p->sum = p->l->sum + p->r->sum, void(); }
    void build(Node *&p, int l, int r, int a[]) {
        p = new Node(0);
        if (l == r) return p->ori = a[l], void();
        int mid = (l + r) >> 1;
        build(p->l, l, mid, a), build(p->r, mid + 1, r, a);
        return pushUp(p);
    }
    void update(Node *&p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr) return update(p, v);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p->l, l, mid, ql, qr, v);
        if (qr > mid) update(p->r, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t query(Node *p, int l, int r, int ql, int qr, int64_t v = 0) const {
        if (ql <= l && r <= qr) return p->sum + v * p->ori;
        v += p->laz;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr, v);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr, v);
        return query(p->l, l, mid, ql, qr, v) + query(p->r, mid + 1, r, ql, qr, v);
    }

   public:
    SegmentTree(void) { roots.push_back(nullptr), ver = 0; }
    void resize(int _n) { return n = _n, void(); }
    void build(int a[]) { return build(roots.back(), 1, n, a); }
    void newVer(void) { return ver++, roots.push_back(roots.back()), void(); }
    void update(int l, int r, int64_t v) { return update(roots.back(), 1, n, l, r, v); }
    int64_t query(int v, int l, int r) const { return query(roots[v], 1, n, l, r); }
};

int dfni[maxn], dfno[maxn], top[maxn], fa[maxn], son[maxn], siz[maxn], v[maxn];
pii ord[maxn];
int64_t sum[maxn], dist[maxn];
SegmentTree ST;

vector<pii> graph[maxn];

void dfs1(int p, int pre = 0) {
    fa[p] = pre, siz[p] = 1;
    for (auto i : graph[p])
        if (i.first != pre) {
            dist[i.first] = dist[p] + i.second, dfs1(i.first, p), siz[p] += siz[i.first];
            if (!son[p] || siz[son[p]] < siz[i.first]) son[p] = i.first;
        }
    return;
}
int dfnt = 0;
void dfs2(int p, int _top) {
    top[p] = _top, dfni[p] = ++dfnt;
    if (son[p]) dfs2(son[p], _top);
    for (auto i : graph[p])
        if (i.first != fa[p] && i.first != son[p]) dfs2(i.first, i.first);
    for (auto i : graph[p])
        if (i.first != fa[p]) v[dfni[i.first]] = i.second;
    dfno[p] = dfnt;
    return;
}

void solve(void) {
    int n, q, A;
    cin >> n >> q >> A;
    for (int i = 1; i <= n; i++) cin >> ord[i].first, ord[i].second = i;
    for (int i = 1, x, y, d; i < n; i++) cin >> x >> y >> d, graph[x].emplace_back(y, d), graph[y].emplace_back(x, d);
    dfs1(1), dfs2(1, 1);
    ST.resize(n), ST.build(v), sort(ord + 1, ord + n + 1);
    for (int i = 1; i <= n; i++) {
        int x = ord[i].second;
        sum[i] = sum[i - 1] + dist[x], ST.newVer();
        while (x) ST.update(dfni[top[x]], dfni[x], 1), x = fa[top[x]];
    }
    int64_t last = 0;
    while (q--) {
        int x, a, b;
        cin >> x >> a >> b;
        int l = (a + last) % A, r = (b + last) % A;
        if (l > r) swap(l, r);
        auto calc = [&](int v, int p) {
            int64_t tot = sum[v] + dist[p] * v;
            while (p) tot -= 2 * ST.query(v, dfni[top[p]], dfni[p]), p = fa[top[p]];
            return tot;
        };
        l = lower_bound(ord + 1, ord + n + 1, pii{l, 0}) - ord,
        r = lower_bound(ord + 1, ord + n + 1, pii{r + 1, 0}) - ord - 1;
        cout << (last = calc(r, x) - calc(l - 1, x)) << endl;
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