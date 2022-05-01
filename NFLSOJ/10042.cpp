/**
 * @file 10042.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-22
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

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int rnk, siz;
        pii v;
        Node(pii v_) { l = r = NULL, rnk = rand(), siz = 1, v = v_; }
    };

    Node* root;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void pushUp(Node* p) { return p->siz = 1 + getSiz(p->l) + getSiz(p->r), void(); }
    void split(Node* p, Node*& tree1, Node*& tree2, int s) {
        if (p == NULL) return tree1 = tree2 = NULL, void();
        if (1 + getSiz(p->l) <= s)
            tree1 = p, split(p->r, tree1->r, tree2, s - 1 - getSiz(p->l));
        else
            tree2 = p, split(p->l, tree1, tree2->l, s);
        return pushUp(p);
    }
    void merge(Node*& p, Node* tree1, Node* tree2) {
        if (!tree1) return p = tree2, void();
        if (!tree2) return p = tree1, void();
        if (tree1->rnk < tree2->rnk)
            p = tree1, merge(p->r, tree1->r, tree2);
        else
            p = tree2, merge(p->l, tree1, tree2->l);
        return pushUp(p);
    }
    pii merge(Node* p) {
        pii ans = p->v;
        if (p->l) ans.first = merge(p->l).first;
        if (p->r) ans.second = merge(p->r).second;
        delete p;
        return ans;
    }

   public:
    FhqTreap(void) { root = NULL; }
    void init(int n) {
        for (int i = 1; i <= n; i++) merge(root, root, new Node({i, i}));
        return;
    }
    pii merge(int l, int r) {
        Node *pl = NULL, *pr = NULL;
        split(root, pl, root, l), split(root, root, pr, r - l + 1);
        pii ans = merge(root);
        merge(root, pl, new Node(ans)), merge(root, root, pr);
        return ans;
    }
} FT;
class STList {
   private:
    int a[maxlgn][maxn], lg[maxn];

   public:
    void build(int n, int v[]) {
        for (int i = 1, x = 0; i <= n; i++) {
            while ((1 << (x + 1)) <= i) x++;
            lg[i] = x;
        }
        for (int i = 1; i <= n; i++) a[0][i] = v[i];
        for (int i = 1; i < maxlgn; i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++) a[i][j] = max(a[i - 1][j], a[i - 1][j + (1 << (i - 1))]);
        return;
    }
    int query(int l, int r) {
        int t = lg[r - l + 1];
        return max(a[t][l], a[t][r - (1 << t) + 1]);
    }
} STL;

int a[maxn], p[maxn], id[maxn], ans = 0, ansp = 1;
pii q[maxn];
vector<int> graph[maxn];

void dfs(int p, int cnt = 0) {
    int v = STL.query(q[p].first + 1, q[p].second);
    v <= a[1] ? cnt++ : cnt = 0;
    if (graph[p].empty() && cnt > ans) ans = cnt, ansp = q[p].first;
    for (auto i : graph[p]) dfs(i, cnt);
    return;
}

void solve(void) {
    int n, c;
    cin >> n >> c >> a[1];
    for (int i = 2; i <= n; i++) cin >> a[i];
    FT.init(n), STL.build(n, a);
    for (int i = 1, l, r; i <= c; i++) cin >> l >> r, q[i] = FT.merge(l, r);
    for (int i = 1; i <= n; i++) p[i] = i + 1;
    for (int i = 1; i <= c; i++) {
        for (int j = q[i].first; j <= q[i].second; j = p[j])
            if (id[j]) graph[i].push_back(id[j]);
        p[q[i].first] = q[i].second, id[q[i].first] = i;
    }
    dfs(c);
    cout << ansp - 1 << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tournament.in", "r", stdin), freopen("tournament.out", "w", stdout);
#endif
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