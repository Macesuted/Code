/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 * @brief
 *      My solution: https://www.macesuted.cn/article/lg5066/
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

#define maxn 3000005
#define INF 0x3f3f3f3f

class FhqTreap {
   private:
    struct Node {
        int rank;
        int col;             // 区间颜色
        int sum;             // 子树和
        int siz[2];          // 子树内 0/1 区间数量
        int tl, tr;          // 区间左右端点
        int deltaL, deltaR;  // 1 区间左右端点偏移量
        int minLen[2];       // 子树内最短 0/1 区间长度
        Node *l, *r;         // 平衡树左右孩子
        Node(void) {}
        Node(int _rank, int _col, int _tl, int _tr) {
            rank = _rank;
            col = _col;
            tl = _tl, tr = _tr;
            l = r = NULL;
            reset();
        }
        // 重新计算该点的单点信息
        void reset(void) {
            siz[col] = 1, siz[!col] = 0;
            sum = col * (tr - tl + 1);
            deltaL = deltaR = 0;
            minLen[col] = tr - tl + 1, minLen[!col] = INF;
            return;
        }
        Node operator+(const Node& b) const {
            Node a = *this;
            a.sum += b.sum;
            a.siz[0] += b.siz[0], a.siz[1] += b.siz[1];
            a.minLen[0] = min(a.minLen[0], b.minLen[0]), a.minLen[1] = min(a.minLen[1], b.minLen[1]);
            return a;
        }
    };

    Node pool[10000000];
    int tail = 0;

    Node* root;
    queue<Node*> needErase;  // 需要被删除的结点

    static const long long kMul = 0x9ddfea08eb382d69ULL;
    long long Seed = 1145141919810;
    inline long long fingerPrint(long long x) {
        return x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47, x *= kMul, x ^= x >> 47, x * kMul;
    }
    inline int frand(void) { return Seed += fingerPrint(Seed); }

    inline Node* newNode(int val, int l, int r) { return &(pool[tail++] = Node(frand(), val, l, r)); }

    inline void update(Node* p, int dl, int dr) {
        if (p == NULL) return;
        p->deltaL += dl, p->deltaR += dr;
        p->minLen[0] -= dl + dr, p->minLen[1] += dl + dr;
        p->sum += (dl + dr) * p->siz[1];
        if (p->col == 1)
            p->tl -= dl, p->tr += dr;
        else
            p->tl += dr, p->tr -= dl;
        return;
    }
    void findEmpty(Node* p) {
        if (p == NULL) return;
        if (p->minLen[0] && p->minLen[1]) return;
        pushDown(p);
        if (p->tl > p->tr) needErase.push(p);
        findEmpty(p->l), findEmpty(p->r);
        return;
    }
    void eraseEmpty(void) {
        while (!needErase.empty()) {
            Node* p = needErase.front();
            needErase.pop();
            Node *nodeL = NULL, *treeM = NULL, *nodeR = NULL, *treeR = NULL;
            split1(root, root, treeR, p->tl - 1), split1(treeR, treeM, treeR, p->tl);
            split2(root, root, nodeL, p->tl - 2);
            if (p == treeM)
                nodeR = (p->l == NULL) ? p->r : p->l;
            else
                nodeR = treeM, nodeR->l = nodeR->r = NULL;
            // delete p;
            if (nodeL != NULL && nodeR != NULL) nodeL->tr = nodeR->tr, nodeL->reset(), /* delete nodeR, */ nodeR = NULL;
            merge(root, root, nodeL), merge(root, root, nodeR), merge(root, root, treeR);
        }
        return;
    }
    // void destroy(Node* p) {
    //     if (p == NULL) return;
    //     if (p->l != NULL) destroy(p->l);
    //     if (p->r != NULL) destroy(p->r);
    //     delete p;
    //     return;
    // }
    void pushDown(Node* p) {
        if (!p->deltaL && !p->deltaR) return;
        if (p->l != NULL) update(p->l, p->deltaL, p->deltaR);
        if (p->r != NULL) update(p->r, p->deltaL, p->deltaR);
        p->deltaL = p->deltaR = 0;
        return;
    }
    inline void pushUp(Node* p) {
        p->reset();
        if (p->l != NULL) *p = *p + *(p->l);
        if (p->r != NULL) *p = *p + *(p->r);
        return;
    }

    // 将对应区间左端点 <= p 的部分划分到 tree1，左端点 > p 的部分划分到 tree2
    void split1(Node* root, Node*& tree1, Node*& tree2, int p) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        pushDown(root);
        if (root->tl <= p)
            tree1 = root, split1(root->r, tree1->r, tree2, p);
        else
            tree2 = root, split1(root->l, tree1, tree2->l, p);
        return pushUp(root);
    }
    // 将对应区间右端点 <= p 的部分划分到 tree1，右端点 > p 的部分划分到 tree2
    void split2(Node* root, Node*& tree1, Node*& tree2, int p) {
        if (root == NULL) return tree1 = tree2 = NULL, void();
        pushDown(root);
        if (root->tr <= p)
            tree1 = root, split2(root->r, tree1->r, tree2, p);
        else
            tree2 = root, split2(root->l, tree1, tree2->l, p);
        return pushUp(root);
    }
    void merge(Node*& root, Node* tree1, Node* tree2) {
        if (tree1 == NULL) return root = tree2, void();
        if (tree2 == NULL) return root = tree1, void();
        if (tree1->rank < tree2->rank)
            pushDown(root = tree1), merge(root->r, tree1->r, tree2);
        else
            pushDown(root = tree2), merge(root->l, tree1, tree2->l);
        return pushUp(root);
    }

    void print(Node* root) {
        if (root == NULL) return;
        pushDown(root);
        if (root->l != NULL) print(root->l);
        cerr << '[' << root->tl << '~' << root->tr << ':' << root->col << ']';
        if (root->r != NULL) print(root->r);
        return;
    }

   public:
    FhqTreap(void) { root = NULL; }
    void pushBack(int l, int r, int val) {
        Node* p = newNode(val, l, r);
        merge(root, root, p);
        return;
    }
    void opt1_2(int l, int r, int val) {
        Node *nodeL = NULL, *p = NULL, *nodeR = NULL, *treeR = NULL;
        split2(root, root, p, l - 1), split1(p, p, treeR, r);
        split1(p, nodeL, p, l - 1), split2(p, p, nodeR, r);
        if (nodeL != NULL) {
            if (nodeL->tr > r) nodeR = newNode(nodeL->col, r, nodeL->tr);
            nodeL->tr = l - 1, nodeL->reset();
        } else
            split2(root, root, nodeL, l - 2);
        if (nodeR != NULL)
            nodeR->tl = r + 1, nodeR->reset();
        else
            split1(treeR, nodeR, treeR, r + 1);
        // destroy(p);
        p = newNode(val, l, r);
        if (nodeL != NULL && p->col == nodeL->col) {
            p->tl = nodeL->tl, p->reset();
            // delete nodeL;
            nodeL = NULL;
        }
        if (nodeR != NULL && p->col == nodeR->col) {
            p->tr = nodeR->tr, p->reset();
            // delete nodeR;
            nodeR = NULL;
        }
        merge(root, root, nodeL), merge(root, root, p), merge(root, root, nodeR), merge(root, root, treeR);
        return;
    }
    void opt3(int l, int r) {
        r--;
        Node *treeM = NULL, *treeR = NULL, *node = NULL;
        split2(root, root, treeM, l - 1), split1(treeM, treeM, treeR, r);
        split1(treeM, node, treeM, l);
        if (node != NULL && node->col == 1)
            merge(root, root, node);
        else
            merge(treeM, node, treeM);
        node = NULL;
        split2(treeM, treeM, node, r - 1);
        if (node != NULL && node->col == 0) {
            if (node->tr > r)
                merge(treeR, node, treeR);
            else {
                merge(treeM, treeM, node);
                Node* nodeR = NULL;
                split1(treeR, nodeR, treeR, r + 1);
                merge(treeM, treeM, nodeR);
            }
        } else
            merge(treeM, treeM, node);
        if (treeM != NULL) update(treeM, 1, 0);
        merge(root, root, treeM), merge(root, root, treeR);
        findEmpty(root), eraseEmpty();
        return;
    }
    void opt4(int l, int r) {
        l++;
        Node *treeM = NULL, *treeR = NULL, *node = NULL;
        split2(root, root, treeM, l - 1), split1(treeM, treeM, treeR, r);
        split1(treeM, node, treeM, l);
        if (node != NULL && node->col == 0) {
            if (node->tl < l)
                merge(root, root, node);
            else {
                merge(treeM, node, treeM);
                Node* nodeL = NULL;
                split2(root, root, nodeL, l - 2);
                merge(treeM, nodeL, treeM);
            }
        } else
            merge(treeM, node, treeM);
        node = NULL;
        split2(treeM, treeM, node, r - 1);
        if (node != NULL && node->col == 1)
            merge(treeR, node, treeR);
        else
            merge(treeM, treeM, node);
        if (treeM != NULL) update(treeM, 0, 1);
        merge(root, root, treeM), merge(root, root, treeR);
        findEmpty(root), eraseEmpty();
        return;
    }
    void opt5(int l, int r) {
        r--;
        Node *treeM = NULL, *treeR = NULL, *node = NULL;
        split2(root, root, treeM, l - 1), split1(treeM, treeM, treeR, r);
        split1(treeM, node, treeM, l);
        if (node != NULL && node->col == 0)
            merge(root, root, node);
        else
            merge(treeM, node, treeM);
        node = NULL;
        split2(treeM, treeM, node, r - 1);
        if (node != NULL && node->col == 1) {
            if (node->tr > r)
                merge(treeR, node, treeR);
            else {
                merge(treeM, treeM, node);
                Node* nodeR = NULL;
                split1(treeR, nodeR, treeR, r + 1);
                merge(treeM, treeM, nodeR);
            }
        } else
            merge(treeM, treeM, node);
        if (treeM != NULL) update(treeM, 0, -1);
        merge(root, root, treeM), merge(root, root, treeR);
        findEmpty(root), eraseEmpty();
        return;
    }
    void opt6(int l, int r) {
        l++;
        Node *treeM = NULL, *treeR = NULL, *node = NULL;
        split2(root, root, treeM, l - 1), split1(treeM, treeM, treeR, r);
        split1(treeM, node, treeM, l);
        if (node != NULL && node->col == 1) {
            if (node->tl < l)
                merge(root, root, node);
            else {
                merge(treeM, node, treeM);
                Node* nodeL = NULL;
                split2(root, root, nodeL, l - 2);
                merge(treeM, nodeL, treeM);
            }
        } else
            merge(treeM, node, treeM);
        node = NULL;
        split2(treeM, treeM, node, r - 1);
        if (node != NULL && node->col == 0)
            merge(treeR, node, treeR);
        else
            merge(treeM, treeM, node);
        if (treeM != NULL) update(treeM, -1, 0);
        merge(root, root, treeM), merge(root, root, treeR);
        findEmpty(root), eraseEmpty();
        return;
    }
    int opt7(int l, int r) {
        Node *node = NULL, *p = NULL, *treeR = NULL;
        split2(root, root, p, l - 1), split1(p, p, treeR, r);
        int answer = 0;
        if (p != NULL) answer += p->sum;
        split1(p, node, p, l - 1);
        if (node != NULL) answer -= node->col * (l - node->tl);
        merge(p, node, p);
        node = NULL;
        split2(p, p, node, r);
        if (node != NULL) answer -= node->col * (node->tr - r);
        merge(p, p, node);
        merge(root, root, p), merge(root, root, treeR);
        return answer;
    }
    inline void print(void) { return print(root), cerr << endl, void(); }
};

FhqTreap treap;

int a[maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    int last = 1;
    for (register int i = 2; i <= n; i++)
        if (a[i] != a[i - 1]) treap.pushBack(last, i - 1, a[i - 1]), last = i;
    treap.pushBack(last, n, a[n]);
    last = 0;
    while (m--) {
        int opt = read<int>(), l = last ^ read<int>(), r = last ^ read<int>();
        if (opt == 1)
            treap.opt1_2(l, r, 0);
        else if (opt == 2)
            treap.opt1_2(l, r, 1);
        else if (opt == 3)
            treap.opt3(l, r);
        else if (opt == 4)
            treap.opt4(l, r);
        else if (opt == 5)
            treap.opt5(l, r);
        else if (opt == 6)
            treap.opt6(l, r);
        else
            write(last = treap.opt7(l, r)), putch('\n');
    }
    return 0;
}