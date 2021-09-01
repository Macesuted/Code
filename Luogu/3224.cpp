/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s.push_back(c), c = getch();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (register int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    register T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
    register T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

class FhqTreap {
   private:
    struct Node {
        int id, val;
        int rank, siz;
        Node *l, *r;
        Node(int _id, int _val) { id = _id, val = _val, rank = rand(), l = r = NULL, siz = 1; }
    };

    Node* root;

    inline int getSiz(Node* p) { return p == NULL ? 0 : p->siz; }
    inline void pushUp(Node* p) {
        p->siz = 1 + getSiz(p->l) + getSiz(p->r);
        return;
    }
    void split1(Node* root, Node*& tree1, Node*& tree2, int siz) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        if (getSiz(root->l) + 1 <= siz)
            tree1 = root, split1(root->r, tree1->r, tree2, siz - getSiz(root->l) - 1);
        else
            tree2 = root, split1(root->l, tree1, tree2->l, siz);
        return pushUp(root);
    }
    void split2(Node* root, Node*& tree1, Node*& tree2, int val) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        if (root->val <= val)
            tree1 = root, split2(root->r, tree1->r, tree2, val);
        else
            tree2 = root, split2(root->l, tree1, tree2->l, val);
        return pushUp(root);
    }
    void merge(Node*& root, Node* tree1, Node* tree2) {
        if (tree1 == NULL) return root = tree2, void();
        if (tree2 == NULL) return root = tree1, void();
        if (tree1->rank < tree2->rank)
            root = tree1, merge(root->r, tree1->r, tree2);
        else
            root = tree2, merge(root->l, tree1, tree2->l);
        return pushUp(root);
    }
    void dfs(Node* p) {
        if (p == NULL) return;
        insert(p->id, p->val);
        if (p->l != NULL) dfs(p->l);
        if (p->r != NULL) dfs(p->r);
        return;
    }

   public:
    int findKth(int k) {
        Node *p = NULL, *treeR = NULL;
        split1(root, root, treeR, k - 1), split1(treeR, p, treeR, 1);
        int ret = (p == NULL ? -1 : p->id);
        merge(root, root, p), merge(root, root, treeR);
        return ret;
    }
    void insert(int id, int val) {
        Node *p = new Node(id, val), *treeR = NULL;
        split2(root, root, treeR, val);
        merge(root, root, p), merge(root, root, treeR);
        return;
    }
    void operator+=(const FhqTreap& oth) { return dfs(oth.root); }
};

#define maxn 100005

int fa[maxn], siz[maxn];
FhqTreap treap[maxn];
int val[maxn];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
void merge(int x, int y) {
    x = getfa(x), y = getfa(y);
    if (x == y) return;
    if (siz[x] < siz[y]) swap(x, y);
    fa[y] = x, treap[x] += treap[y], siz[x] += siz[y];
    return;
}

int main() {
    // freopen("P3224_1.in", "r", stdin), freopen("P3224_1.ans", "w", stdout);
    srand(time(NULL));
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) treap[i].insert(i, read<int>()), fa[i] = i, siz[i] = 1;
    while (m--) merge(read<int>(), read<int>());
    int q = read<int>();
    while (q--)
        if (getstr()[0] == 'Q') {
            int p = read<int>();
            write(treap[getfa(p)].findKth(read<int>())), putch('\n');
        } else
            merge(read<int>(), read<int>());
    return 0;
}