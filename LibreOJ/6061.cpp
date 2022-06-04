/**
 * @file 6061.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-04
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

#define maxn 100005
#define mod 1000000007

typedef tuple<int, int, int> tiii;

int id[maxn << 1];

class FhqTreap1 {
   private:
    struct Node {
        Node *l, *r;
        int siz, id, rnk;
        bool ali, era;
        Node(int id_) { l = r = nullptr, siz = 1, ali = true, era = false, rnk = rand(), id = id_; }
    };

    Node* root;
    int n, cnt;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void clear(Node* p) { return p && (p->era = true, p->ali = false, p->siz = 0), void(); }
    void pushDown(Node* p) { return p->era && (clear(p->l), clear(p->r), p->era = false), void(); }
    void pushUp(Node* p) { return p->siz = p->ali + getSiz(p->l) + getSiz(p->r), void(); }
    void split(Node* p, Node*& t1, Node*& t2, int siz) {
        if (!p) return t1 = t2 = nullptr, void();
        pushDown(p);
        if (p->ali + getSiz(p->l) <= siz)
            t1 = p, split(p->r, t1->r, t2, siz - p->ali - getSiz(p->l));
        else
            t2 = p, split(p->l, t1, t2->l, siz);
        return pushUp(p);
    }
    void merge(Node*& p, Node* t1, Node* t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->rnk < t2->rnk)
            pushDown(p = t1), merge(p->r, t1->r, t2);
        else
            pushDown(p = t2), merge(p->l, t1, t2->l);
        return pushUp(p);
    }
    void getId(Node* p) {
        if (!p) return;
        return getId(p->l), id[p->id] = ++cnt, getId(p->r), delete p;
    }

   public:
    FhqTreap1(void) { root = nullptr; }
    void build(int n_) {
        n = n_;
        for (int i = 1; i <= n; i++) merge(root, root, new Node(i));
        return;
    }
    void insert(int p) {
        Node* tr = nullptr;
        return split(root, root, tr, p), merge(root, root, new Node(++n)), merge(root, root, tr);
    }
    void erase(int p) {
        Node *tp = nullptr, *tr = nullptr;
        split(root, root, tp, p - 1), split(tp, tp, tr, 1), clear(tp);
        return merge(root, root, tp), merge(root, root, tr);
    }
    void getId(void) { return cnt = 0, getId(root); }
};

class FhqTreap2 {
   private:
    struct Node {
        Node *l, *r;
        int siz, rnk, id;
        Node(int id_) { l = r = nullptr, siz = 1, rnk = rand(), id = id_; }
    };

    Node* root;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void pushUp(Node* p) { return p->siz = 1 + getSiz(p->l) + getSiz(p->r), void(); }
    void split(Node* p, Node*& t1, Node*& t2, int siz) {
        if (!p) return t1 = t2 = nullptr, void();
        if (1 + getSiz(p->l) <= siz)
            t1 = p, split(p->r, t1->r, t2, siz - 1 - getSiz(p->l));
        else
            t2 = p, split(p->l, t1, t2->l, siz);
        return pushUp(p);
    }
    void merge(Node*& p, Node* t1, Node* t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->rnk < t2->rnk)
            p = t1, merge(p->r, t1->r, t2);
        else
            p = t2, merge(p->l, t1, t2->l);
        return pushUp(p);
    }

   public:
    FhqTreap2(void) { root = nullptr; }
    void insert(int p, int v) {
        Node* tr = nullptr;
        return split(root, root, tr, p), merge(root, root, new Node(v)), merge(root, root, tr);
    }
    void erase(int p) {
        Node *tp = nullptr, *tr = nullptr;
        split(root, root, tp, p - 1), split(tp, tp, tr, 1), delete tp;
        return merge(root, root, tr);
    }
    int getId(int p) {
        Node *tp = nullptr, *tr = nullptr;
        split(root, root, tp, p - 1), split(tp, tp, tr, 1);
        int ret = tp->id;
        return merge(root, root, tp), merge(root, root, tr), ret;
    }
};

class FenwickTree {
   private:
    struct Value {
        int64_t v1, v2, v3;
        int cnt;
        Value(void) { v1 = v2 = v3 = cnt = 0; }
        Value(int v) { v1 = v, v2 = v3 = 0, cnt = 1; }
        Value(int64_t v1_, int64_t v2_, int64_t v3_, int cnt_) { v1 = v1_, v2 = v2_, v3 = v3_, cnt = cnt_; }
        Value operator+(const Value& o) const {
            return Value{(v1 + o.v1) % mod, (v2 + v1 * o.v1 + o.v2) % mod, (v3 + v2 * o.v1 + v1 * o.v2 + o.v3) % mod,
                         cnt + o.cnt};
        }
    };

    class SegmentTree {
       private:
        struct Node {
            Node *l, *r;
            Value val;
            Node(void) { l = r = nullptr; }
        };

        Node* root;
        int n;

        void pushUp(Node* p) { return p->val = (p->l ? p->l->val : Value()) + (p->r ? p->r->val : Value()), void(); }
        void insert(Node*& p, int l, int r, int qp, int v) {
            if (!p) p = new Node();
            if (l == r) return p->val = Value(v), void();
            int mid = (l + r) >> 1;
            qp <= mid ? insert(p->l, l, mid, qp, v) : insert(p->r, mid + 1, r, qp, v);
            return pushUp(p);
        }
        void erase(Node*& p, int l, int r, int qp) {
            if (l == r) return delete p, p = nullptr, void();
            int mid = (l + r) >> 1;
            qp <= mid ? erase(p->l, l, mid, qp) : erase(p->r, mid + 1, r, qp);
            pushUp(p);
            if (!p->val.cnt) delete p, p = nullptr;
            return;
        }
        Value query(Node* p, int l, int r, int ql, int qr) {
            if (!p) return Value();
            if (ql <= l && r <= qr) return p->val;
            int mid = (l + r) >> 1;
            if (qr <= mid) return query(p->l, l, mid, ql, qr);
            if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
            return query(p->l, l, mid, ql, qr) + query(p->r, mid + 1, r, ql, qr);
        }

       public:
        SegmentTree(void) { root = nullptr; }
        void resize(int n_) { return n = n_, void(); }
        void insert(int p, int v) { return insert(root, 1, n, p, v); }
        void erase(int p) { return erase(root, 1, n, p); }
        Value query(int l, int r) { return query(root, 1, n, l, r); }
    };

    SegmentTree tree[maxn << 1];
    int n;

    Value query(int xl, int xr, int yr) {
        Value ans;
        for (int i = yr; i; i -= i & -i) ans = ans + tree[i].query(xl, xr);
        return ans;
    }

   public:
    void build(int n_) {
        n = n_;
        for (int i = 1; i <= n; i++) tree[i].resize(n);
        return;
    }
    void insert(int x, int y, int v) {
        for (int i = y + 1; i <= n; i += i & -i) tree[i].insert(x, v);
        return;
    }
    void erase(int x, int y) {
        for (int i = y + 1; i <= n; i += i & -i) tree[i].erase(x);
        return;
    }
    int64_t querySum(int xl, int xr, int yr) { return query(xl, xr, yr + 1).v3; }
    int64_t queryCnt(int xl, int xr, int yr) { return query(xl, xr, yr + 1).cnt; }
};

FhqTreap1 BT1;
FhqTreap2 BT2;
FenwickTree FT;
int a[maxn], v[maxn << 1];
tiii ques[maxn];
map<int, set<int>> pos;

int getLeft(int x) {
    auto p = pos[v[x]].find(x);
    return p == pos[v[x]].begin() ? 0 : *--p;
}
int getRight(int x) {
    auto p = pos[v[x]].find(x);
    return ++p == pos[v[x]].end() ? 0 : *p;
}
void insert(int x) {
    pos[v[x]].insert(x);
    int l = getLeft(x), r = getRight(x);
    FT.insert(x, l, v[x]);
    if (r) FT.erase(r, l), FT.insert(r, x, v[r]);
    return;
}
void erase(int x) {
    int l = getLeft(x), r = getRight(x);
    pos[v[x]].erase(x);
    FT.erase(x, l);
    if (r) FT.erase(r, x), FT.insert(r, l, v[r]);
    return;
}

void solve(void) {
    int n, q;
    cin >> n >> q;
    int tn = n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) {
        cin >> get<0>(ques[i]) >> get<1>(ques[i]);
        if (get<0>(ques[i]) != 3) cin >> get<2>(ques[i]);
    }
    BT1.build(n);
    for (int i = 1; i <= q; i++) {
        if (get<0>(ques[i]) == 3) BT1.erase(get<1>(ques[i]));
        if (get<0>(ques[i]) == 4) BT1.insert(get<1>(ques[i])), n++;
    }
    BT1.getId(), FT.build(n);
    for (int i = 1; i <= tn; i++) v[id[i]] = a[i], insert(id[i]), BT2.insert(i - 1, id[i]);
    for (int i = 1, t, x, y, c = tn; i <= q; i++) {
        tie(t, x, y) = ques[i];
        if (t == 1) x = BT2.getId(x), y = BT2.getId(y), cout << FT.querySum(x, y, x - 1) << endl;
        if (t == 2) x = BT2.getId(x), erase(x), v[x] = y, insert(x);
        if (t == 3) x = BT2.getId(x), erase(x), BT2.erase(get<1>(ques[i]));
        if (t == 4) v[x = id[++c]] = y, insert(x), BT2.insert(get<1>(ques[i]), x);
        if (t == 5) x = BT2.getId(x), y = BT2.getId(y), cout << FT.queryCnt(x, y, x - 1) << endl;
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