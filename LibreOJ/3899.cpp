/**
 * @file 3899.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-12
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

#define maxn 250005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        uint64_t ans, sumAB, sumA, sumB, vA, vB, xAB, xA, xB, x;
        Node(void) { ans = sumAB = sumA = sumB = vA = vB = xAB = xA = xB = x = 0; }
    };

    Node tree[maxn << 2];
    int n;

    void update(int p, int l, int r, uint64_t vA, uint64_t vB, uint64_t xAB, uint64_t xA, uint64_t xB, uint64_t x) {
        tree[p].ans += tree[p].sumAB * xAB + tree[p].sumA * xA + tree[p].sumB * xB + x * (r - l + 1);
        if (tree[p].vA)
            if (tree[p].vB)
                tree[p].x += tree[p].vA * tree[p].vB * xAB;
            else
                tree[p].xB += tree[p].vA * xAB;
        else if (tree[p].vB)
            tree[p].xA += tree[p].vB * xAB;
        else
            tree[p].xAB += xAB;
        if (tree[p].vA)
            tree[p].x += tree[p].vA * xA;
        else
            tree[p].xA += xA;
        if (tree[p].vB)
            tree[p].x += tree[p].vB * xB;
        else
            tree[p].xB += xB;
        tree[p].x += x;
        if (vA) tree[p].sumA = vA * (r - l + 1), tree[p].sumAB = vA * tree[p].sumB, tree[p].vA = vA;
        if (vB) tree[p].sumB = vB * (r - l + 1), tree[p].sumAB = vB * tree[p].sumA, tree[p].vB = vB;
        return;
    }
    void pushDown(int p, int l, int r) {
        int mid = (l + r) >> 1;
        update(p << 1, l, mid, tree[p].vA, tree[p].vB, tree[p].xAB, tree[p].xA, tree[p].xB, tree[p].x);
        update(p << 1 | 1, mid + 1, r, tree[p].vA, tree[p].vB, tree[p].xAB, tree[p].xA, tree[p].xB, tree[p].x);
        tree[p].vA = tree[p].vB = tree[p].xAB = tree[p].xA = tree[p].xB = tree[p].x = 0;
        return;
    }
    void pushUp(int p) {
        return tree[p].ans = tree[p << 1].ans + tree[p << 1 | 1].ans,
               tree[p].sumAB = tree[p << 1].sumAB + tree[p << 1 | 1].sumAB,
               tree[p].sumA = tree[p << 1].sumA + tree[p << 1 | 1].sumA,
               tree[p].sumB = tree[p << 1].sumB + tree[p << 1 | 1].sumB, void();
    }
    void update(int p, int l, int r, int ql, int qr, uint64_t vA, uint64_t vB, uint64_t xAB) {
        if (ql <= l && r <= qr) return update(p, l, r, vA, vB, xAB, 0, 0, 0);
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, vA, vB, xAB);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, vA, vB, xAB);
        return pushUp(p);
    }
    uint64_t query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].ans;
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int l, int r, uint64_t vA, uint64_t vB, uint64_t xAB) { return update(1, 1, n, l, r, vA, vB, xAB); }
    uint64_t query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

int a[maxn], b[maxn];
uint64_t ans[maxn];
vector<vector<pii>> ques;
stack<int> sA, sB;

void solve(void) {
    int T, n, q;
    cin >> T >> n, ques.resize(n + 1), ST.resize(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    cin >> q;
    for (int i = 1, l, r; i <= q; i++) cin >> l >> r, ques[r].emplace_back(l, i);
    a[0] = b[0] = INT_MAX, sA.push(0), sB.push(0);
    for (int i = 1; i <= n; i++) {
        while (a[sA.top()] < a[i]) sA.pop();
        while (b[sB.top()] < b[i]) sB.pop();
        ST.update(sA.top() + 1, i, a[i], 0, 0), ST.update(sB.top() + 1, i, 0, b[i], 0), ST.update(1, i, 0, 0, 1);
        sA.push(i), sB.push(i);
        for (auto j : ques[i]) ans[j.second] = ST.query(j.first, i);
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("match.in", "r", stdin), freopen("match.out", "w", stdout);
#endif
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