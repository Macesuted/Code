/**
 * @file K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-21
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

#define maxn 200005

typedef pair<int64_t, int64_t> pll;

const int64_t base1 = 97, base2 = 79, mod1 = 1000000007, mod2 = 1000000009;

int64_t pow1[maxn], pow2[maxn];

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t val1, val2;
        Node(void) { l = r = nullptr, val1 = val2 = 0; }
    };

    Node *root;
    int n;

    void pushUp(Node *p, int l, int r) {
        int mid = (l + r) >> 1;
        p->val1 = p->val2 = 0;
        if (p->l)
            p->val1 = (p->val1 + p->l->val1 * pow1[r - mid]) % mod1, p->val2 = (p->val2 + p->l->val2 * pow2[r - mid]) % mod2;
        if (p->r) p->val1 = (p->val1 + p->r->val1) % mod1, p->val2 = (p->val2 + p->r->val2) % mod2;
        return;
    }
    void update(Node *&p, int l, int r, int qp, int v) {
        if (!p) p = new Node();
        if (l == r) return p->val1 += v, p->val2 += v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp, v) : update(p->r, mid + 1, r, qp, v);
        return pushUp(p, l, r);
    }
    pll query(Node *p, int l, int r, int ql, int qr) {
        if (!p) return {0, 0};
        if (ql <= l && r <= qr) return {p->val1 * pow1[qr - r] % mod1, p->val2 * pow2[qr - r] % mod2};
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        pll ans = {0, 0};
        {
            pll ret = query(p->l, l, mid, ql, qr);
            ans.first = (ans.first + ret.first) % mod1, ans.second = (ans.second + ret.second) % mod2;
        }
        {
            pll ret = query(p->r, mid + 1, r, ql, qr);
            ans.first = (ans.first + ret.first) % mod1, ans.second = (ans.second + ret.second) % mod2;
        }
        return ans;
    }
    void merge(Node *&p, Node *q, int l, int r) {
        if (!p) return p = q, void();
        if (!q) return;
        if (l == r) return p->val1 += q->val1, p->val2 += q->val2, delete q;
        int mid = (l + r) >> 1;
        merge(p->l, q->l, l, mid), merge(p->r, q->r, mid + 1, r);
        return delete q, pushUp(p, l, r);
    }

   public:
    SegmentTree(void) { root = nullptr; }
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(root, 1, n, p, v); }
    pll query(int l, int r) { return query(root, 1, n, l, r); }
    void merge(SegmentTree *o) { return merge(root, o->root, 1, n); }
};

SegmentTree *ST[30];

void solve(void) {
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i < maxn; i++) pow1[i] = pow1[i - 1] * base1 % mod1, pow2[i] = pow2[i - 1] * base2 % mod2;

    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    for (int i = 0; i < 26; i++) ST[i] = new SegmentTree(), ST[i]->resize(n);
    for (int i = 1; i <= n; i++) ST[s[i] - 'a']->update(i, +1);

    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            char c;
            cin >> i >> c;
            for (int t = 0; t < 26; t++)
                if (ST[t]->query(i, i).first) ST[t]->update(i, -1);
            ST[c - 'a']->update(i, +1);
        } else if (op == 2) {
            char c1, c2;
            cin >> c1 >> c2;
            ST[c2 - 'a']->merge(ST[c1 - 'a']);
            delete ST[c1 - 'a'], ST[c1 - 'a'] = new SegmentTree(), ST[c1 - 'a']->resize(n);
        } else {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            pll val1 = {0, 0}, val2 = {0, 0};
            for (int i = 0; i < 26; i++) {
                pll ret1 = ST[i]->query(l1, r1), ret2 = ST[i]->query(l2, r2);
                val1.first = (val1.first + ret1.first * (i + 1)) % mod1;
                val1.second = (val1.second + ret1.second * (i + 1)) % mod2;

                val2.first = (val2.first + ret2.first * (i + 1)) % mod1;
                val2.second = (val2.second + ret2.second * (i + 1)) % mod2;
            }
            cout << (val1 == val2 && (r1 - l1 == r2 - l2) ? "YES" : "NO") << endl;
        }
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