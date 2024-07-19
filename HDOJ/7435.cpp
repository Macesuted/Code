/**
 * @file 7435.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 500005

vector<int> graph[maxn];
int a[maxn];

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        uint64_t val1, val2, cnt;
        Node(void) { l = r = nullptr, val1 = val2 = cnt = 0; }
    };
    Node *root;

    void pushUp(Node *p) {
        if (!p->l) return p->val1 = p->r->val1, p->val2 = p->r->val2, p->cnt = p->r->cnt, void();
        if (!p->r) return p->val1 = p->l->val1, p->val2 = p->l->val2, p->cnt = p->l->cnt, void();
        p->val1 = p->l->val1 + p->r->val1, p->val2 = p->l->val2 + p->r->val2, p->cnt = p->l->cnt + p->r->cnt;
        return;
    }
    void insert(Node *&p, int l, int r, int qp) {
        if (!p) p = new Node();
        if (l == r) return p->val1 += (uint64_t)qp, p->val2 += (uint64_t)qp * (uint64_t)qp, p->cnt++, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp) : insert(p->r, mid + 1, r, qp);
        return pushUp(p);
    }
    uint64_t merge(Node *&p, Node *q, int l, int r) {
        if (!p) return p = q, 0;
        if (!q) return 0;
        if (l == r) return p->val1 += q->val1, p->val2 += q->val2, p->cnt += q->cnt, 0;
        uint64_t ans = 0;
        if (p->l && q->r) {
            ans += q->r->val2 * p->l->cnt - q->r->val1 * p->l->val1;
        }
        if (p->r && q->l) {
            ans += p->r->val2 * q->l->cnt - p->r->val1 * q->l->val1;
        }
        int mid = (l + r) >> 1;
        ans += merge(p->l, q->l, l, mid) + merge(p->r, q->r, mid + 1, r);
        if (q) delete q;
        return pushUp(p), ans;
    }

   public:
    SegmentTree(void) { root = nullptr; }
    void insert(int v) { return insert(root, 1, 1e6, v); }
    uint64_t merge(SegmentTree *q) { return merge(root, q->root, 1, 1e6); }
};

SegmentTree *ST[maxn];
uint64_t ans = 0;

uint64_t dfs(int p, int pre = -1) {
    uint64_t sum = 0;
    ST[p] = new SegmentTree();
    ST[p]->insert(a[p]);
    for (auto i : graph[p])
        if (i != pre) sum += dfs(i, p), sum += ST[p]->merge(ST[i]);
    ans ^= sum << 1;
    return sum;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) cin >> a[i];
    dfs(1);
    cout << ans << endl;
    return 0;
}