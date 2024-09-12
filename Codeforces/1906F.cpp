/**
 * @file 1906F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 1000005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        int64_t sum, ansl, ansr, ans;
        Node(void) { sum = ansl = ansr = ans = 0; }
        Node(int64_t v) { sum = ans = ansl = ansr = v; }
        Node operator+(const Node& o) const {
            Node ans;
            ans.sum = this->sum + o.sum;
            ans.ansl = max(this->ansl, this->sum + o.ansl);
            ans.ansr = max(o.ansr, o.sum + this->ansr);
            ans.ans = max({this->ans, o.ans, this->ansr + o.ansl});
            return ans;
        }
    };

    Node tree[maxn << 2];
    int n;

    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = Node(tree[p].sum + v), void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int64_t query(int l, int r) { return query(1, 1, n, l, r).ans; }
};

SegmentTree SGT;
vector<pii> ops[maxn];
vector<tiii> ques[maxn];
int a[maxn];
int64_t ans[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, l, r, v; i <= m; i++) cin >> l >> r >> v, ops[l].emplace_back(i, v), ops[r + 1].emplace_back(i, -v);
    int q;
    cin >> q;
    for (int i = 1, p, l, r; i <= q; i++) cin >> p >> l >> r, ques[p].emplace_back(i, l, r);

    SGT.resize(m);
    for (int i = 1; i <= q; i++) {
        for (auto [p, v] : ops[i]) SGT.update(p, v);
        for (auto [id, l, r] : ques[i]) ans[id] = SGT.query(l, r);
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}