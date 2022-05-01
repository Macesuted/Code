/**
 * @file 104.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

class Splay {
   private:
    struct Node {
        Node *son[2], *fa;
        int siz, val, cnt;
        Node(int _val) { son[0] = son[1] = fa = NULL, siz = cnt = 1, val = _val; }
    };

    Node* root;

    bool isRigSon(Node* p) { return p == p->fa->son[1]; }
    bool inLefSon(Node* p, int v) { return v <= getSiz(p->son[0]); }
    bool inRigSon(Node* p, int v) { return v > getSiz(p->son[0]) + p->cnt; }
    int getSiz(Node* p) { return p == NULL ? 0 : p->siz; }
    void pushUp(Node* p) {
        p->siz = p->cnt;
        if (p->son[0] != NULL) p->siz += p->son[0]->siz;
        if (p->son[1] != NULL) p->siz += p->son[1]->siz;
        return;
    }
    void rotate(Node* p) {
        Node *fp = p->fa, *ffp = fp->fa;
        bool w = isRigSon(p);
        if (p->son[!w] != NULL) p->son[!w]->fa = fp;
        fp->son[w] = p->son[!w], p->son[!w] = fp, fp->fa = p, p->fa = ffp;
        if (ffp != NULL) ffp->son[fp == ffp->son[1]] = p;
        return pushUp(fp), pushUp(p);
    }
    void splay(Node* p, Node* end = NULL) {
        for (Node* fp = p->fa; fp != end; rotate(p), fp = p->fa)
            if (fp->fa != end) rotate(isRigSon(p) == isRigSon(fp) ? fp : p);
        if (end == NULL) root = p;
        return;
    }
    void splayV(int v, Node* end = NULL) {
        Node *p, *x = NULL;
        for (p = root; p != NULL && p->val != v; p = p->son[v > p->val])
            if (v < p->val) x = p;
        return splay(p == NULL ? x : p, end);
    }
    void splayS(int k) {
        Node* p = root;
        while (inLefSon(p, k) || inRigSon(p, k))
            if (inRigSon(p, k))
                k -= getSiz(p->son[0]) + p->cnt, p = p->son[1];
            else
                p = p->son[0];
        return splay(p);
    }

   public:
    Splay(void) {
        root = new Node(numeric_limits<int>::max()), (root->son[0] = new Node(numeric_limits<int>::min()))->fa = root;
    }
    void insert(int v) {
        splayV(v);
        if (root->val == v) return root->cnt++, root->siz++, void();
        Node* r = root;
        splayS(getSiz(root->son[0]));
        return (r->son[0] = new Node(v))->fa = r, pushUp(r), pushUp(root);
    }
    void erase(int v) {
        int lv = getPre(v), rv = getSuf(v);
        splayV(lv), splayV(rv, root);
        --root->son[1]->son[0]->siz;
        if (!--root->son[1]->son[0]->cnt) delete root->son[1]->son[0], root->son[1]->son[0] = NULL;
        return pushUp(root->son[1]), pushUp(root);
    }
    int getRank(int v) { return splayV(v), getSiz(root->son[0]); }
    int findKTh(int k) { return splayS(k + 1), root->val; }
    int getPre(int v) { return findKTh(getRank(v) - 1); }
    int getSuf(int v) { return findKTh(getRank(getPre(v + 1)) + root->cnt); }
} SP;

void solve(void) {
    int n = read<int>();
    while (n--) {
        int op = read<int>(), x = read<int>();
        if (op == 1)
            SP.insert(x);
        else if (op == 2)
            SP.erase(x);
        else if (op == 3)
            write(SP.getRank(x)), putch('\n');
        else if (op == 4)
            write(SP.findKTh(x)), putch('\n');
        else if (op == 5)
            write(SP.getPre(x)), putch('\n');
        else
            write(SP.getSuf(x)), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
