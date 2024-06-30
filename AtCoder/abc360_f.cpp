/**
 * @file abc360_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        pii val;
        int lazy;
        Node(int pl, int pr) { l = r = nullptr, val = {0, -pl}, lazy = 0; }
    };

    Node *root;

    void pushDown(Node *p, int l, int r) {
        int mid = (l + r) >> 1;
        if (!p->l) p->l = new Node(l, mid);
        if (!p->r) p->r = new Node(mid + 1, r);
        p->l->val.first += p->lazy, p->r->val.first += p->lazy, p->l->lazy += p->lazy, p->r->lazy += p->lazy;
        p->lazy = 0;
        return;
    }
    void pushUp(Node *p) { return p->val = max(p->l->val, p->r->val), void(); }
    void update(Node *p, int l, int r, int ql, int qr, int delt) {
        if (ql <= l && r <= qr) return p->lazy += delt, p->val.first += delt, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p->l, l, mid, ql, qr, delt);
        if (qr > mid) update(p->r, mid + 1, r, ql, qr, delt);
        return pushUp(p);
    }

   public:
    SegmentTree(void) { root = new Node(0, 1e9 + 1); }
    void update(int l, int r, int delt) { return update(root, 0, 1e9 + 1, l, r, delt); }
    pii query(void) { return root->val; }
} ST;

map<int, vector<tiii>> S;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, l, r; i <= n; i++) {
        cin >> l >> r;
        if (l + 1 == r) continue;
        ST.update(l + 1, r - 1, +1);
        S[l].emplace_back(l + 1, r - 1, -1);
        S[l + 1].emplace_back(r + 1, 1e9 + 1, +1);
        S[r].emplace_back(r + 1, 1e9 + 1, -1);
    }
    tiii ans;
    {
        pii ret = ST.query();
        ans = {ret.first, 0, ret.second};
    }
    for (auto [v, vec] : S) {
        for (auto [l, r, delt] : vec) ST.update(l, r, delt);
        pii ret = ST.query();
        ans = max(ans, tiii{ret.first, -v, ret.second});
    }
    cout << -get<1>(ans) << ' ' << -get<2>(ans) << endl;
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