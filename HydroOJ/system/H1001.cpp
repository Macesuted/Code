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

int cnt = 0;

class Trie {
   private:
    struct Node {
        Node *son[26];
        bool vis;
        Node(void) {
            for (register int i = 0; i < 26; i++) son[i] = NULL;

            vis = false;
        }
    };

    Node *root;

   public:
    Trie(void) { root = new Node(); }

    void insert(string str) {
        Node *p = root;

        for (string::iterator i = str.begin(); i != str.end(); i++) {
            register int c = *i - 'a';

            if (p->son[c] == NULL) p->son[c] = new Node();

            p = p->son[c];
        }

        if (!p->vis) ::cnt++, p->vis = true;

        return;
    }
};

Trie trie;

int main() {
    int n = read<int>();

    for (register int i = 1; i <= n; i++) trie.insert(getstr());

    write(cnt), putch('\n');
    return 0;
}