/**
 * @file 2219D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

mt19937 rnd(114514);

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int64_t sum;
        int val, cnt, siz, rnk;
        Node(int x) { l = r = nullptr, sum = val = x, cnt = siz = 1, rnk = rnd(); }
    };

    Node *root;

    int getSiz(Node *p) { return p ? p->siz : 0; }

    void pushUp(Node *p) {
        p->sum = p->val, p->cnt = p->siz = 1;
        if (p->l) p->sum += p->l->sum, p->cnt += p->l->cnt, p->siz += p->l->siz;
        if (p->r) p->sum += p->r->sum, p->cnt += p->r->cnt, p->siz += p->r->siz;
        return;
    }

    void split(Node *p, Node *&t1, Node *&t2, int v) {
        if (!p) return t1 = t2 = nullptr, void();
        if (p->val < v)
            t1 = p, split(p->r, t1->r, t2, v);
        else
            t2 = p, split(p->l, t1, t2->l, v);
        return pushUp(p);
    }

    void merge(Node *&p, Node *t1, Node *t2) {
        if (!t1 || !t2) return p = t1 ? t1 : t2, void();
        if (t1->rnk < t2->rnk)
            p = t1, merge(p->r, p->r, t2);
        else
            p = t2, merge(p->l, t1, p->l);
        return pushUp(p);
    }

    void destroy(Node *p) {
        if (!p) return;
        destroy(p->l), destroy(p->r);
        delete p;
        return;
    }

   public:
    FhqTreap(void) { root = nullptr; }
    ~FhqTreap(void) { destroy(root); }

    void insert(int x) {
        Node *tr = nullptr;
        split(root, root, tr, x);
        merge(root, root, new Node(x)), merge(root, root, tr);
        return;
    }

    pair<int, int64_t> query(int x) {
        Node *tr = nullptr;
        split(root, root, tr, x);

        int cnt = tr ? tr->cnt : 0;
        int64_t sum = tr ? tr->sum : 0;

        merge(root, root, tr);

        return {cnt, sum};
    }
};

int a[maxn], f[maxn], g[maxn];
int dfni[maxn], dfno[maxn], siz[maxn];
int64_t ans[maxn];
vector<vector<int>> graph;
set<int> S;

int dfnt;
void dfs1(int p, int pre = -1) {
    dfni[p] = ++dfnt, siz[p] = 1;

    S.erase(a[p]);
    f[p] = *S.begin(), g[p] = *++S.begin();

    if (~pre) graph[p].erase(find(graph[p].begin(), graph[p].end(), pre));

    for (auto q : graph[p]) dfs1(q, p), siz[p] += siz[q];

    sort(graph[p].begin(), graph[p].end(), [](int x, int y) { return siz[x] > siz[y]; });

    S.insert(a[p]);

    dfno[p] = dfnt;

    return;
}

pair<unordered_map<int, FhqTreap> *, vector<int> *> dfs2(int p) {
    int nf = *S.begin() == f[p] ? *++S.begin() : *S.begin();

    S.erase(a[p]);

    vector<pair<unordered_map<int, FhqTreap> *, vector<int> *>> FTs;

    for (auto q : graph[p]) FTs.push_back(dfs2(q));

    pair<unordered_map<int, FhqTreap> *, vector<int> *> FT =
        FTs.empty() ? make_pair(new unordered_map<int, FhqTreap>, new vector<int>) : FTs[0];

    auto insert = [&](int x) -> void {
        return (*FT.first)[-1].insert(f[x]), (*FT.first)[f[x]].insert(g[x]), FT.second->push_back(x);
    };

    for (size_t i = 1; i < FTs.size(); i++) {
        for (auto x : *FTs[i].second) insert(x);
        delete FTs[i].first, delete FTs[i].second;
    }

    auto [cnt, sum] = (*FT.first)[-1].query(a[p]);
    ans[p] = nf - f[p] - sum + cnt * (int64_t)a[p];
    if (a[p] > f[p]) {
        auto [acnt, asum] = (*FT.first)[f[p]].query(-1);
        ans[p] += asum - acnt * (int64_t)f[p];
        auto [cnt, sum] = (*FT.first)[f[p]].query(a[p]);
        ans[p] += -sum + cnt * (int64_t)a[p];
    }

    insert(p);

    S.insert(a[p]);

    return FT;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);

    S.clear();
    for (int i = 0; i <= n + 1; i++) S.insert(i);
    dfnt = 0, dfs1(1);

    S.clear();
    for (int i = 0; i <= n + 1; i++) S.insert(i);

    dfs2(1);

    int64_t sum = 0, answer = 0;
    for (int i = 1; i <= n; i++) sum += f[i], answer = max(answer, ans[i]);

    cout << sum + answer << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
