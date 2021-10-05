/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My solution: https://macesuted.cn/article/cf1559d2/
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

#define maxn 100005

typedef pair<int, int> pii;

int fa[2][maxn];

int getfa(int t, int p) { return fa[t][p] == p ? p : fa[t][p] = getfa(t, fa[t][p]); }
inline void merge(int t, int x, int y) { return fa[t][getfa(t, x)] = getfa(t, y), void(); }

int main() {
    int n = read<int>(), m1 = read<int>(), m2 = read<int>();
    for (register int i = 1; i <= n; i++) fa[0][i] = fa[1][i] = i;
    for (register int i = 1; i <= m1; i++) merge(0, read<int>(), read<int>());
    for (register int i = 1; i <= m2; i++) merge(1, read<int>(), read<int>());
    static vector<pii> cache;
    for (register int i = 2; i <= n; i++)
        if (getfa(0, i) != getfa(0, 1) && getfa(1, i) != getfa(1, 1))
            merge(0, 1, i), merge(1, 1, i), cache.push_back((pii){1, i});
    static queue<int> que[2];
    for (register int i = 1; i <= n; i++) {
        if (getfa(0, i) == getfa(0, 1) && getfa(1, i) != getfa(1, 1)) que[0].push(i);
        if (getfa(0, i) != getfa(0, 1) && getfa(1, i) == getfa(1, 1)) que[1].push(i);
    }
    while (!que[0].empty() && !que[1].empty()) {
        while (!que[0].empty() && !(getfa(0, que[0].front()) == getfa(0, 1) && getfa(1, que[0].front()) != getfa(1, 1)))
            que[0].pop();
        while (!que[1].empty() && !(getfa(0, que[1].front()) != getfa(0, 1) && getfa(1, que[1].front()) == getfa(1, 1)))
            que[1].pop();
        if (que[0].empty() || que[1].empty()) break;
        merge(0, que[0].front(), que[1].front());
        merge(1, que[0].front(), que[1].front());
        cache.push_back((pii){que[0].front(), que[1].front()});
    }
    write((int)cache.size()), putch('\n');
    for (vector<pii>::iterator i = cache.begin(); i != cache.end(); i++)
        write(i->first), putch(' '), write(i->second), putch('\n');
    return 0;
}