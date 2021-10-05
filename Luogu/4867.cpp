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

#define maxn 100005
#define maxm 1000005

struct Ask {
    int l, r, bel, id, vl, vr;
    inline bool operator<(const Ask& oth) const {
        return bel == oth.bel ? ((bel & 1) ? r > oth.r : r < oth.r) : bel < oth.bel;
    }
};

int a[maxn];
Ask ask[maxm];
int ans[maxm];

int tree[2][maxn];
void add(int id, int p, int val) {
    for (register int i = p; i < maxn; i += i & -i) tree[id][i] += val;
    return;
}
int sum(int id, int p) {
    int sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[id][i];
    return sum;
}

inline void add(int p) {
    if (sum(1, a[p]) - sum(1, a[p] - 1) == 0) add(0, a[p], 1);
    add(1, a[p], 1);
    return;
}
inline void del(int p) {
    add(1, a[p], -1);
    if (sum(1, a[p]) - sum(1, a[p] - 1) == 0) add(0, a[p], -1);
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    int sqrtn = sqrt(n);
    for (register int i = 1; i <= m; i++)
        ask[i].l = read<int>(), ask[i].r = read<int>(),
        ask[i].vl = read<int>(), ask[i].vr = read<int>(),
        ask[i].bel = ask[i].l / sqrtn, ask[i].id = i;
    sort(ask + 1, ask + m + 1);
    for (register int i = 1, l = 1, r = 0; i <= m; i++) {
        while (l > ask[i].l) add(--l);
        while (r < ask[i].r) add(++r);
        while (l < ask[i].l) del(l++);
        while (r > ask[i].r) del(r--);
        ans[ask[i].id] = sum(0, ask[i].vr) - sum(0, ask[i].vl - 1);
    }
    for (register int i = 1; i <= m; i++) write(ans[i]), putch('\n');
    return 0;
}