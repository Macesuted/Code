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

#define maxn 500005

typedef pair<int, int> pii;

int mod;

multiset<int> S, answers;

inline int Mod(int x) { return x >= mod ? x - mod : x; }

int getBest(int v, bool ignore) {
    if (v == -1) return -1;
    multiset<int>::iterator p = S.lower_bound(mod - v);
    if (p == S.begin()) return -1;
    if (*--p == v && !ignore) return p == S.begin() ? -1 : *--p;
    return *p;
}
void insert(int v) {
    int a = getBest(v, true), b = getBest(a, false), c = getBest(b, false);
    S.insert(v);
    if (a == -1 || b >= v) return;
    if (a == c) answers.erase(answers.find(Mod(a + b)));
    answers.insert(Mod(v + a));
    return;
}
void erase(int v) {
    S.erase(S.find(v));
    int a = getBest(v, true), b = getBest(a, false), c = getBest(b, false);
    if (a == -1 || b >= v) return;
    if (a == c) answers.insert(Mod(a + b));
    answers.erase(answers.find(Mod(v + a)));
    return;
}
inline int getAns(void) { return Mod(*--S.end() + *----S.end()); }

int main() {
    int n = read<int>(), lastans = 0;
    mod = read<int>();
    for (register int i = 1; i <= n; i++) {
        int opt = read<int>(), x = (read<int>() ^ lastans) % mod;
        ((opt == 1) ? insert : erase)(x);
        if ((int)S.size() < 2)
            putstr("EE"), lastans = 0;
        else
            write(lastans = max(getAns(), answers.empty() ? 0 : *answers.rbegin()));
        putch('\n');
    }
    return 0;
}