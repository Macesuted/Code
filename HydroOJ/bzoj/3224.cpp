/**
 * @file 3369.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
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

bool mem1;

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int size, rank;
        int val;
        Node(int _val) { l = r = NULL, size = 1, rank = rand(), val = _val; }
    };

    Node* root;

    inline int getSize(Node* p) { return p == NULL ? 0 : p->size; }
    inline void pushUp(Node* p) { return p->size = 1 + getSize(p->l) + getSize(p->r), void(); }
    void split1(Node* root, Node*& tree1, Node*& tree2, int val) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        if (root->val <= val)
            tree1 = root, split1(root->r, tree1->r, tree2, val);
        else
            tree2 = root, split1(root->l, tree1, tree2->l, val);
        return pushUp(root);
    }
    void split2(Node* root, Node*& tree1, Node*& tree2, int size) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        if (1 + getSize(root->l) <= size)
            tree1 = root, split2(root->r, tree1->r, tree2, size - getSize(root->l) - 1);
        else
            tree2 = root, split2(root->l, tree1, tree2->l, size);
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
    void insert(int v) {
        Node *treeR = NULL, *p = new Node(v);
        split1(root, root, treeR, v);
        merge(root, root, p), merge(root, root, treeR);
        return;
    }
    void erase(int v) {
        Node *treeR = NULL, *p = NULL;
        split1(root, root, treeR, v - 1), split2(treeR, p, treeR, 1);
        delete p;
        merge(root, root, treeR);
        return;
    }
    int getRank(int v) {
        Node* treeR = NULL;
        split1(root, root, treeR, v - 1);
        int ret = getSize(root) + 1;
        merge(root, root, treeR);
        return ret;
    }
    int findRank(int x) {
        Node *treeR = NULL, *p = NULL;
        split2(root, root, treeR, x - 1), split2(treeR, p, treeR, 1);
        int ret = p->val;
        merge(root, root, p), merge(root, root, treeR);
        return ret;
    }
    int getPre(int x) {
        Node *treeR = NULL, *p = NULL;
        split1(root, root, treeR, x - 1), split2(root, root, p, getSize(root) - 1);
        int ret = p->val;
        merge(root, root, p), merge(root, root, treeR);
        return ret;
    }
    int getAft(int x) {
        Node *treeR = NULL, *p = NULL;
        split1(root, root, treeR, x), split2(treeR, p, treeR, 1);
        int ret = p->val;
        merge(root, root, p), merge(root, root, treeR);
        return ret;
    }
};

FhqTreap treap;

void solve(void) {
    int n = read<int>();
    while (n--) {
        int opt = read<int>();
        if (opt == 1)
            treap.insert(read<int>());
        else if (opt == 2)
            treap.erase(read<int>());
        else if (opt == 3)
            write(treap.getRank(read<int>())), putch('\n');
        else if (opt == 4)
            write(treap.findRank(read<int>())), putch('\n');
        else if (opt == 5)
            write(treap.getPre(read<int>())), putch('\n');
        else
            write(treap.getAft(read<int>())), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}