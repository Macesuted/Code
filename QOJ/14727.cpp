/**
 * @file 14727.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005
#define maxlgn 22

class STList {
   private:
    int a[maxlgn][maxn], b[maxlgn][maxn], lg2[maxn];

   public:
    void build(int n, int v[]) {
        for (int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
        for (int i = 1; i <= n; i++) a[0][i] = b[0][i] = v[i];
        for (int t = 1; t < maxlgn; t++)
            for (int i = 1; i + (1 << t) - 1 <= n; i++)
                a[t][i] = min(a[t - 1][i], a[t - 1][i + (1 << (t - 1))]),
                b[t][i] = max(b[t - 1][i], b[t - 1][i + (1 << (t - 1))]);
        return;
    }
    int getMin(int l, int r) {
        int t = lg2[r - l + 1];
        return min(a[t][l], a[t][r - (1 << t) + 1]);
    }
    int getMax(int l, int r) {
        int t = lg2[r - l + 1];
        return max(b[t][l], b[t][r - (1 << t) + 1]);
    }
} STL;

class SegmentTree {
   private:
    struct Node;

    static vector<Node> pool;
    static size_t poolSiz;

    struct Nodex {
        uint32_t id;

        Nodex(void) = default;
        Nodex(const void *p) { this->id = p ? ((const Node *)p - &pool[0]) : 0; }

        Nodex operator=(const void *p) { return this->id = p ? ((const Node *)p - &pool[0]) : 0, *this; }
        Node *operator->(void) const { return this->id ? &pool[this->id] : nullptr; }
        operator Node *(void) const { return this->id ? &pool[this->id] : nullptr; }
    };

    struct Node {
        Nodex l, r;
        int val, ver;
        Node(int ver_ = 0) { l = r = nullptr, val = 0, ver = ver_; }

        void *operator new(size_t) {
            if (poolSiz == pool.size()) bad_alloc();
            return &pool[poolSiz++];
        }
    };

    vector<Nodex> roots;
    int n;

    void chkVer(Nodex &p, int ver) {
        if (!p) p = new Node(ver);
        if (p->ver != ver) p = new Node(*p), p->ver = ver;
        return;
    }
    void pushUp(Nodex p) {
        p->val = 0;
        if (p->l) p->val = max(p->val, p->l->val);
        if (p->r) p->val = max(p->val, p->r->val);
        return;
    }
    void update(Nodex &p, int l, int r, int qp, int v, int ver) {
        chkVer(p, ver);
        if (l == r) return p->val = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp, v, ver) : update(p->r, mid + 1, r, qp, v, ver);
        return pushUp(p);
    }
    int query(Nodex p, int l, int r, int ql, int qr, int ver) {
        if (!p) return 0;
        if (ql <= l && r <= qr) return p->val;
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = max(ans, query(p->l, l, mid, ql, qr, ver));
        if (qr > mid) ans = max(ans, query(p->r, mid + 1, r, ql, qr, ver));
        return ans;
    }

   public:
    SegmentTree(void) { roots.push_back(nullptr); }
    void resize(int _n) { return n = _n, pool.resize(n * 30), poolSiz = 1, void(); }
    void newVer(void) { return roots.push_back(roots.back()); }
    void update(int ver, int p, int v) { return update(roots[ver], 1, n, p, v, ver); }
    int query(int ver, int l, int r) { return query(roots[ver], 1, n, l, r, ver); }
};

vector<SegmentTree::Node> SegmentTree::pool;
size_t SegmentTree::poolSiz;

int a[maxn], f[maxn];
bool onl[maxn], onr[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    STL.build(n, a);

    SegmentTree SGT;
    SGT.resize(n);
    SGT.update(0, 1, 1);

    stack<int> Sl, Sr;
    for (int i = 1; i <= n; i++) {
        SGT.newVer();

        auto calcSpel = [&](int x, int y) -> int {
            int l = 0, r = x;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                ((STL.getMax(mid, x) > a[y]) ? l : r) = mid;
            }
            return l ? SGT.query(x, 1, l) + 1 : 0;
        };
        auto calcSper = [&](int x, int y) -> int {
            int l = 0, r = x;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                ((STL.getMin(mid, x) < a[y]) ? l : r) = mid;
            }
            return l ? SGT.query(x, 1, l) + 1 : 0;
        };

        while (!Sl.empty() && a[Sl.top()] > a[i]) {
            Sl.pop();
            if (!Sl.empty()) {
                int q = Sl.top();
                SGT.update(i, q + 1, f[q] + 1);
            }
        }
        if (!Sl.empty()) {
            int q = Sl.top();
            SGT.update(i, q + 1, calcSpel(q, i));
        }
        Sl.push(i);

        while (!Sr.empty() && a[Sr.top()] < a[i]) {
            Sr.pop();
            if (!Sr.empty()) {
                int q = Sr.top();
                SGT.update(i, q + 1, f[q] + 1);
            }
        }
        if (!Sr.empty()) {
            int q = Sr.top();
            SGT.update(i, q + 1, calcSper(q, i));
        }
        Sr.push(i);

        f[i] = SGT.query(i, 1, n);
    }

    cout << n - f[n] << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
