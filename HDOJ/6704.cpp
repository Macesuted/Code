/**
 * @file 6704.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::putch;
using IO::read;
using IO::write;

bool mem1;

#define maxn 100005
#define maxlgn 18

typedef tuple<int, int, int> tiii;

int ans[maxn];

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int cnt;
        Node(void) { l = r = nullptr, cnt = 0; }
    };
    Node *root;
    int n;

    void pushUp(Node *p) {
        if (!p->l) return p->cnt = p->r->cnt, void();
        if (!p->r) return p->cnt = p->l->cnt, void();
        p->cnt = p->l->cnt + p->r->cnt;
        return;
    }
    void insert(Node *&p, int l, int r, int qp) {
        if (!p) p = new Node();
        if (l == r) return p->cnt++, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp) : insert(p->r, mid + 1, r, qp);
        return pushUp(p);
    }
    int query(Node *p, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        // return (p->r && p->r->cnt >= k) ? query(p->r, mid + 1, r, k) : query(p->l, l, mid, k - (p->r ? p->r->cnt : 0));
        return (p->l && p->l->cnt >= k) ? query(p->l, l, mid, k) : query(p->r, mid + 1, r, k - (p->l ? p->l->cnt : 0));
    }
    void merge(Node *&p, Node *q, int l, int r) {
        if (!p) return p = q, void();
        if (!q) return;
        if (l == r) return p->cnt += q->cnt, void();
        int mid = (l + r) >> 1;
        merge(p->l, q->l, l, mid), merge(p->r, q->r, mid + 1, r);
        if (q) delete q;
        return pushUp(p);
    }
    void destroy(Node *p) {
        if (!p) return;
        destroy(p->l), destroy(p->r), delete p;
        return;
    }

   public:
    SegmentTree(void) { root = nullptr; }
    ~SegmentTree(void) { destroy(root); }
    void resize(int _n) { return n = _n, void(); }
    void insert(int v) { return insert(root, 1, n, v); }
    int query(int k) { return (root ? root->cnt : 0) < k ? -1 : query(root, 1, n, k); }
    void merge(SegmentTree *q) { return merge(root, q->root, 1, n); }
};

class SuffixAutomaton {
   private:
    struct Node {
        int son[26], fa, len;
        Node(void) { memset(son, 0, sizeof(son)), fa = len = 0; }
    };

    vector<Node> tree;
    vector<vector<int>> graph;
    vector<vector<tiii>> ques;
    vector<SegmentTree *> ST;
    size_t treet = 0;
    int root, last;

    int newNode(void) {
        if (++treet == tree.size()) tree.resize(tree.size() << 1);
        return treet;
    }

    void dfs(int p) {
        for (auto i : graph[p]) dfs(i), ST[p]->merge(ST[i]);
        for (auto [k, id, len] : ques[p]) {
            int t = ST[p]->query(k);
            if (t == -1)
                ans[id] = -1;
            else
                ans[id] = t - len + 1;
        }
        return;
    }

   public:
    SuffixAutomaton(void) { tree.resize(3000), root = last = newNode(); }
    void pushBack(char ch) {
        int np = newNode(), p = last, c = ch - 'a';
        tree[np].len = tree[last].len + 1;
        while (p && !tree[p].son[c]) tree[p].son[c] = np, p = tree[p].fa;
        if (!p)
            tree[np].fa = root;
        else {
            int q = tree[p].son[c];
            if (tree[p].len + 1 == tree[q].len)
                tree[np].fa = q;
            else {
                int nq = newNode();
                tree[nq] = tree[q], tree[nq].len = tree[p].len + 1;
                while (p && tree[p].son[c] == q) tree[p].son[c] = nq, p = tree[p].fa;
                tree[q].fa = tree[np].fa = nq;
            }
        }
        last = np;
        return;
    }
    void solve(string s, int q) {
        int n = s.size();

        vector<vector<int>> fa(treet + 1);
        ST.resize(treet + 1);
        for (int i = 1; i <= (int)treet; i++) {
            ST[i] = new SegmentTree(), ST[i]->resize(n);
            fa[i].resize(maxlgn, 0), fa[i][0] = tree[i].fa;
        }
        for (int t = 1; t < maxlgn; t++)
            for (int i = 1; i <= (int)treet; i++)
                if (fa[i][t - 1]) fa[i][t] = fa[fa[i][t - 1]][t - 1];

        vector<int> rec;
        rec.resize(s.size());
        int p = root;
        for (int i = 0; i < (int)s.size(); i++) {
            int c = s[i] - 'a';
            rec[i] = p = tree[p].son[c];
            ST[p]->insert(i + 1);
        }

        ques.resize(treet + 1);
        for (int i = 0, l, r, k; i < q; i++) {
            l = read(), r = read(), k = read();
            int len = r - l + 1;
            int p = rec[r - 1];
            for (int i = maxlgn - 1; ~i; i--)
                if (fa[p][i] && tree[fa[p][i]].len >= len) p = fa[p][i];
            ques[p].emplace_back(k, i, len);
        }

        graph.resize(treet + 1);
        for (int i = 1; i <= (int)treet; i++) graph[fa[i][0]].push_back(i);

        dfs(root);
        delete ST[root];

        return;
    }
};

void solve(void) {
    int n = read<int>(), q = read<int>();
    string s;
    char c = getch();
    while (c < 'a' || c > 'z') c = getch();
    while (c != '\n') s.push_back(c), c = getch();
    SuffixAutomaton SAM;
    for (char c : s) SAM.pushBack(c);
    SAM.solve(s, q);
    for (int i = 0; i < q; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}