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
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
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

#define maxn 200005

int a[maxn];

inline long long calc(int len) { return 1LL * (1 + len) * len / 2; }

class FhqTreap {
   private:
    struct Node {
        int rank, size;
        long long sum;
        Node *l, *r;
        int tl, tr;
        Node(int _tl, int _tr) { l = r = NULL, size = 1, tl = _tl, tr = _tr, sum = calc(tr - tl + 1), rank = rand(); }
    };

    Node* root;

    void pushUp(Node* p) {
        p->size = 1, p->sum = calc(p->tr - p->tl + 1);
        if (p->l != NULL) p->size += p->l->size, p->sum += p->l->sum;
        if (p->r != NULL) p->size += p->r->size, p->sum += p->r->sum;
        return;
    }
    void splitl(Node* root, Node*& tree1, Node*& tree2, int lim) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        if (root->tl <= lim)
            tree1 = root, splitl(root->r, tree1->r, tree2, lim);
        else
            tree2 = root, splitl(root->l, tree1, tree2->l, lim);
        return pushUp(root);
    }
    void splitr(Node* root, Node*& tree1, Node*& tree2, int lim) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        if (root->tr <= lim)
            tree1 = root, splitr(root->r, tree1->r, tree2, lim);
        else
            tree2 = root, splitr(root->l, tree1, tree2->l, lim);
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

   public:
    FhqTreap(void) { root = NULL; }
    void pushBack(int l, int r) {
        Node* p = new Node(l, r);
        merge(root, root, p);
        return;
    }
    void update(int p) {
        Node *treeM = NULL, *treeR = NULL;
        splitr(root, root, treeM, p - 1), splitl(treeM, treeM, treeR, p);
        int l = treeM->tl, r = treeM->tr;
        if (p != l) {
            if (a[p - 1] > a[p]) {
                treeM->tl = p;
                Node* x = new Node(l, p - 1);
                merge(root, root, x);
            }
        } else if (root != NULL && a[p - 1] <= a[p]) {
            Node* p = NULL;
            splitr(root, root, p, l - 2);
            treeM->tl = p->tl;
            delete p;
        }
        if (p != r) {
            if (a[p] > a[p + 1]) {
                treeM->tr = p;
                Node* x = new Node(p + 1, r);
                merge(treeR, x, treeR);
            }
        } else if (treeR != NULL && a[p] <= a[p + 1]) {
            Node* p = NULL;
            splitl(treeR, p, treeR, r + 1);
            treeM->tr = p->tr;
            delete p;
        }
        pushUp(treeM);
        merge(root, root, treeM), merge(root, root, treeR);
        return;
    }
    long long query(int ql, int qr) {
        Node *treeM = NULL, *treeR = NULL;
        splitl(root, root, treeM, ql - 1), splitr(treeM, treeM, treeR, qr);
        long long answer = (treeM == NULL ? 0 : treeM->sum);
        {
            Node* p = NULL;
            splitr(root, root, p, ql - 1);
            if (p != NULL) answer += calc(min(qr, p->tr) - ql + 1), merge(root, root, p);
        }
        {
            Node* p = NULL;
            splitl(treeR, p, treeR, qr);
            if (p != NULL) answer += calc(qr - max(ql, p->tl) + 1), merge(treeR, p, treeR);
        }
        merge(root, root, treeM), merge(root, root, treeR);
        return answer;
    }
};

FhqTreap treap;

int main() {
    int n = read<int>(), q = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 1; i <= n; i++) {
        int l = i;
        while (i < n && a[i] <= a[i + 1]) i++;
        treap.pushBack(l, i);
    }
    while (q--)
        if (read<int>() == 1) {
            int p = read<int>();
            a[p] = read<int>();
            treap.update(p);
        } else {
            int l = read<int>(), r = read<int>();
            write(treap.query(l, r)), putch('\n');
        }
    return 0;
}