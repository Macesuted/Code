/**
 * @file 2062.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define maxv 1000005

typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        array<int, 2> sum;
        Node(void) { l = r = NULL, sum[0] = 1, sum[1] = 0; }
    };

    Node* root;

    array<int, 2> merge(const array<int, 2>& a, const array<int, 2>& b) { return {a[0] + b[0], a[1] + b[1]}; }
    void pushUp(Node* p) {
        if (!p) return;
        return p->sum = merge(p->l ? p->l->sum : array<int, 2>{0, 0}, p->r ? p->r->sum : array<int, 2>{0, 0}), void();
    }
    void insert(Node*& p, int l, int r, int v) {
        if (!p) p = new Node();
        if (l == r) return swap(p->sum[0], p->sum[1]);
        int mid = (l + r) >> 1;
        v <= mid ? insert(p->l, l, mid, v) : insert(p->r, mid + 1, r, v);
        return pushUp(p);
    }
    void merge(Node*& p, Node* o, int l, int r) {
        if (!p && !o) return;
        if (!p) return p = o, void();
        if (!o) return;
        if (l == r) return o->sum[1] && (swap(p->sum[0], p->sum[1]), 1), delete o;
        int mid = (l + r) >> 1;
        merge(p->l, o->l, l, mid), merge(p->r, o->r, mid + 1, r);
        return pushUp(p), delete o;
    }
    array<int, 2> query(Node* p, int l, int r, int qr) {
        if (!p) return {0, 0};
        if (r <= qr) return p->sum;
        int mid = (l + r) >> 1;
        return qr <= mid ? query(p->l, l, mid, qr)
                         : merge(p->l ? p->l->sum : array<int, 2>{0, 0}, query(p->r, mid + 1, r, qr));
    }

   public:
    SegmentTree(void) { root = NULL; }
    void insert(int v) { return insert(root, 1, maxv, v); }
    void merge(SegmentTree* o) { return merge(root, o->root, 1, maxv); }
    array<int, 2> query(int r) { return query(root, 1, maxv, r); }
};

int n, a[maxn], dfni[maxn], low[maxn];
vector<int> graph[maxn], tree[maxn << 1];
int ans[maxn];
SegmentTree* ST[maxn << 1];
vector<tiii> ques[maxn << 1];

stack<int> S;
int dfnt = 0;
void dfs1(int p) {
    dfni[p] = low[p] = ++dfnt, S.push(p);
    for (auto i : graph[p])
        if (!dfni[i]) {
            dfs1(i), low[p] = min(low[p], low[i]);
            if (low[i] >= dfni[p]) {
                tree[p].push_back(++n);
                while (S.top() != i) tree[n].push_back(S.top()), S.pop();
                tree[n].push_back(S.top()), S.pop();
            }
        } else
            low[p] = min(low[p], dfni[i]);
    return;
}
void dfs2(int p) {
    if (!ST[p]) ST[p] = new SegmentTree();
    for (auto i : tree[p]) dfs2(i), ST[p]->merge(ST[i]);
    for (auto i : ques[p]) ans[get<2>(i)] = ST[p]->query(get<0>(i))[get<1>(i)];
    return;
}

void solve(void) {
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], ST[i] = new SegmentTree(), ST[i]->insert(a[i]);
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1);
    int q;
    cin >> q;
    for (int i = 1, t, x, y; i <= q; i++) cin >> t >> x >> y, ques[x].emplace_back(y, t, i);
    dfs2(1);
    for (int i = 1; i <= q; i++) cout << ans[i] << endl;
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