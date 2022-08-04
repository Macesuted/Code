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

#define maxn 100005
#define maxlgn 29

class Trie {
   private:
    struct Node {
        int minVal;
        Node* son[2];
    };

    Node heap[maxn * (maxlgn + 5)];
    int tail;

    Node* newNode(void) {
        heap[tail].minVal = 0x3f3f3f3f, heap[tail].son[0] = heap[tail].son[1] = NULL;
        return &heap[tail++];
    }

    Node* root;

   public:
    Trie(void) { tail = 0, root = newNode(); }
    void insert(int x, int v) {
        Node* p = root;
        for (register int i = maxlgn; ~i; i--) {
            int c = (x >> i & 1);
            if (p->son[c] == NULL) p->son[c] = newNode();
            p = p->son[c];
            p->minVal = min(p->minVal, v);
        }
        return;
    }
    int find(int x, int k) {
        Node* p = root;
        int ans = 0x3f3f3f3f, i;
        for (i = maxlgn; ~i; i--) {
            int c = (x >> i & 1), t = (k >> i & 1);
            if (!t && p->son[!c] != NULL) ans = min(ans, p->son[!c]->minVal);
            c ^= t;
            if (p->son[c] == NULL) break;
            p = p->son[c];
        }
        if (i == -1) ans = min(ans, p->minVal);
        return ans == 0x3f3f3f3f ? -1 : ans;
    }
    inline void destroy(void) { return tail = 0, root = newNode(), void(); }
};

Trie trie;

int a[maxn];

void work(void) {
    int n = read<int>(), k = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    int ans = -1, ansL = -1;
    for (register int i = n; i; i--) {
        a[i] ^= a[i + 1];
        trie.insert(a[i], i);
        int r = trie.find(a[i], k);
        if (r == -1) continue;
        if (ans == -1 || r - i <= ans) ans = r - i, ansL = i;
    }
    trie.destroy();
    if (ans == -1)
        putstr("-1\n");
    else
        write(ansL), putch(' '), write(ansL + ans - 1), putch('\n');
    return;
}

int main() {
    int _ = read<int>();
    while (_--) work();
    return 0;
}