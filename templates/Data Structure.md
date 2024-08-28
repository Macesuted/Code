# Data Structure

## Fenwick Tree

```cpp
template <typename T>
class FenwickTree {
   private:
    vector<T> tree;

   public:
    void resize(size_t n) { tree.assign(n + 1, 0); }
    void add(int p, T val) {
        for (int i = p; i < (int)tree.size(); i += i & -i) tree[i] += val;
        return;
    }
    T sum(int p) {
        T sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
};
```

## ST List

```cpp
class STList {
   private:
    vector<vector<int>> list;
    vector<int> lg;
    int n;

   public:
    void resize(int _n) {
        n = _n;
        lg.resize(n + 1);
        lg[0] = lg[1] = 0;
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        list.resize(lg[n] + 1);
        for (int i = 0; i <= lg[n]; i++) list[i].resize(n + 1);
        return;
    }
    void build(int a[]) {
        for (int i = 1; i <= n; i++) list[0][i] = a[i];
        for (int j = 1; j <= lg[n]; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++) list[j][i] = max(list[j - 1][i], list[j - 1][i + (1 << (j - 1))]);
        return;
    }
    int query(int l, int r) {
        int t = lg[r - l + 1];
        return max(list[t][l], list[t][r - (1 << t) + 1]);
    }
};
```

## Segment Tree (Static)

```cpp
class SegmentTree {
   private:
    struct Node {
        int64_t sum, laz;
    };

    vector<Node> tree;
    int n;

    void pushDown(int p, int l, int r) {
        if (!tree[p].laz) return;
        int mid = (l + r) >> 1;
        tree[p << 1].sum += tree[p].laz * (mid - l + 1), tree[p << 1].laz += tree[p].laz;
        tree[p << 1 | 1].sum += tree[p].laz * (r - mid), tree[p << 1 | 1].laz += tree[p].laz;
        return;
    }
    void pushUp(int p) { return tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum, void(); }
    void build(int p, int l, int r, int a[]) {
        if (l == r) return tree[p].sum = a[l], void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return pushUp(p);
    }
    void update(int p, int l, int r, int qp, int64_t v) {
        if (l == r) return tree[p].sum += v, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int64_t v) {
        if (ql <= l && r <= qr) return tree[p].sum += v * (r - l + 1), tree[p].laz += v, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t query(int p, int l, int r, int qp) {
        if (l == r) return tree[p].sum;
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp);
    }
    int64_t query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].sum;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, tree.resize(n << 2 | 1); }
    void build(int a[]) { return build(1, 1, n, a); }
    void update(int p, int64_t v) { return update(1, 1, n, p, v); }
    void update(int l, int r, int64_t v) { return update(1, 1, n, l, r, v); }
    int64_t query(int p) { return query(1, 1, n, p); }
    int64_t query(int l, int r) { return query(1, 1, n, l, r); }
};
```

## Segment Tree (Dynamic)

```cpp
class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t sum, laz;
        Node(void) { l = r = nullptr, sum = laz = 0; }
    };

    Node *root;
    int n;

    void pushDown(Node *p, int l, int r) {
        if (!p->laz) return;
        if (!p->l) p->l = new Node();
        if (!p->r) p->r = new Node();
        int mid = (l + r) >> 1;
        p->l->sum += p->laz * (mid - l + 1), p->l->laz += p->laz;
        p->r->sum += p->laz * (r - mid), p->r->laz += p->laz;
        p->laz = 0;
        return;
    }
    void pushUp(Node *p) {
        p->sum = 0;
        if (p->l) p->sum += p->l->sum;
        if (p->r) p->sum += p->r->sum;
        return;
    }
    void update(Node *&p, int l, int r, int qp, int64_t v) {
        if (!p) p = new Node();
        if (l == r) return p->sum += v, p->laz += v, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp, v) : update(p->r, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void update(Node *&p, int l, int r, int ql, int qr, int64_t v) {
        if (!p) p = new Node();
        if (ql <= l && r <= qr) return p->sum += v * (r - l + 1), p->laz += v, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p->l, l, mid, ql, qr, v);
        if (qr > mid) update(p->r, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int64_t query(Node *p, int l, int r, int qp) {
        if (!p) return 0;
        if (l == r) return p->sum;
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p->l, l, mid, qp) : query(p->r, mid + 1, r, qp);
    }
    int64_t query(Node *p, int l, int r, int ql, int qr) {
        if (!p) return 0;
        if (ql <= l && r <= qr) return p->sum;
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return query(p->l, l, mid, ql, qr) + query(p->r, mid + 1, r, ql, qr);
    }

   public:
    SegmentTree(void) { root = new Node(); }
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int64_t v) { return update(root, 1, n, p, v); }
    void update(int l, int r, int64_t v) { return update(root, 1, n, l, r, v); }
    int64_t query(int p) { return query(root, 1, n, p); }
    int64_t query(int l, int r) { return query(root, 1, n, l, r); }
};
```

## Fhq Treap

```cpp
class FhqTreap {
   private:
    static mt19937 rnd;

    struct Node {
        Node *l, *r;
        int rnk, val, siz;
        Node(int val_) { l = r = nullptr, rnk = rnd(), val = val_, siz = 1; }
    };

    Node* root;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void pushUp(Node* p) { return p->siz = 1 + getSiz(p->l) + getSiz(p->r), void(); }
    void splitS(Node* p, Node*& t1, Node*& t2, int s) {
        if (!p) return t1 = t2 = nullptr, void();
        if (1 + getSiz(p->l) <= s)
            t1 = p, splitS(p->r, t1->r, t2, s - 1 - getSiz(p->l));
        else
            t2 = p, splitS(p->l, t1, t2->l, s);
        return pushUp(p);
    }
    void splitV(Node* p, Node*& t1, Node*& t2, int v) {
        if (!p) return t1 = t2 = nullptr, void();
        if (p->val < v)
            t1 = p, splitV(p->r, t1->r, t2, v);
        else
            t2 = p, splitV(p->l, t1, t2->l, v);
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
    FhqTreap(void) { rnd.seed(chrono::system_clock::now().time_since_epoch().count()), root = nullptr; }
    void insert(int x) {
        Node* tr = nullptr;
        splitV(root, root, tr, x);
        merge(root, root, new Node(x)), merge(root, root, tr);
        return;
    }
    void erase(int x) {
        Node *tr = nullptr, *tp = nullptr;
        splitV(root, root, tr, x), splitS(tr, tp, tr, 1);
        delete tp;
        merge(root, root, tr);
        return;
    }
    int queryRank(int x) {
        Node* tr = nullptr;
        splitV(root, root, tr, x);
        int ans = getSiz(root) + 1;
        merge(root, root, tr);
        return ans;
    }
    int getRank(int x) {
        Node *tr = nullptr, *tp = nullptr;
        splitS(root, root, tr, x - 1), splitS(tr, tp, tr, 1);
        int ans = tp->val;
        merge(root, root, tp), merge(root, root, tr);
        return ans;
    }
    int pre(int x) {
        Node *tr = nullptr, *tp = nullptr;
        splitV(root, root, tr, x), splitS(root, root, tp, getSiz(root) - 1);
        int ans = tp->val;
        merge(root, root, tp), merge(root, root, tr);
        return ans;
    }
    int suc(int x) {
        Node *tr = nullptr, *tp = nullptr;
        splitV(root, root, tr, x + 1), splitS(tr, tp, tr, 1);
        int ans = tp->val;
        merge(root, root, tp), merge(root, root, tr);
        return ans;
    }
};
```

## Leftist Heap (Persistent)

```cpp
class LeftistHeap {
   private:
    struct Node {
        Node *l, *r;
        int dist, val;
        Node(int v) { l = r = nullptr, dist = 0, val = v; }
    };

    Node *root;

    int getDist(Node *p) { return p ? p->dist : -1; }
    void merge(Node *&p, Node *t1, Node *t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->val > t2->val) swap(t1, t2);
        p = new Node(*t1), merge(p->r, t1->r, t2);
        if (getDist(p->l) < getDist(p->r)) swap(p->l, p->r);
        p->dist = getDist(p->r) + 1;
        return;
    }

   public:
    LeftistTree(void) { root = nullptr; }

    void push(int v) { return merge(root, root, new Node(v)); }
    void pop(void) {
        Node *p = root->l, *q = root->r;
        return merge(root, p, q);
    }
    void merge(LeftistTree *t) { return merge(root, root, t->root); }
    int top(void) { return root ? root->val : -1; }
};
```
