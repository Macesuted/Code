/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
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
inline void write(const T &t) {
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

template <typename T>
class List {
   private:
    struct Node {
        Node *left, *right;
        T val;
        Node(void) { left = right = NULL, val = 0; }
        Node(T v) { left = right = NULL, val = v; }
    };
    Node *head, *tail;

   public:
    struct iterator {
        Node *p;
        iterator(void) { p = NULL; }
        iterator(Node *pointer) { p = pointer; }
        inline iterator &operator++(int type) {
            if (p->right == NULL || p->right->right == NULL) throw "[ERROR] List::iterator::operator++";
            p = p->right;
            return *this;
        }
        inline iterator &operator--(int type) {
            if (p->left == NULL) throw "[ERROR] List::iterator::operator--";
            p = p->left;
            return *this;
        }
        inline T &operator*(void) { return p->val; }
    };

    inline iterator begin(void) { return (iterator){head}; }
    inline iterator end(void) { return (iterator){tail}; }

    List(void) { head = tail = new Node; }
    ~List(void) {
        while (tail != head) tail = tail->left, delete tail->right;
        delete head;
    }
    int len(void) {
        int cnt = 1;
        Node *p = head;
        while (p != tail) p = p->right, cnt++;
        return cnt;
    }
    void push_back(T val) {
        tail->val = val;
        tail->right = new Node;
        tail->right->left = tail;
        tail = tail->right;
        return;
    }
    void move(iterator l, iterator r, iterator p) {
        Node *lp = l.p, *rp = r.p, *pp = p.p;
        lp->left->right = rp->right, rp->right->left = lp->left;
        Node *pr = pp->right;
        pp->right = lp, lp->left = pp, rp->right = pr, pr->left = rp;
        return;
    }
};

List<int> li;

int main() {
    int n = read<int>(), k = read<int>();
    for (register int i = 0; i <= n; i++) li.push_back(i);
    while (k--) {
        int l = read<int>(), r = read<int>(), p = read<int>();
        List<int>::iterator lp = li.begin(), rp = li.begin(), pp = li.begin();
        if (p >= l) p += r - l + 1;
        while (l--) lp++;
        while (r--) rp++;
        while (p--) pp++;
        li.move(lp, rp, pp);
    }
    List<int>::iterator i = li.begin();
    for (register int cnt = 0; cnt < 10; cnt++) i++, write(*i), putch('\n');
    return 0;
}