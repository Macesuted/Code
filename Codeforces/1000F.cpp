/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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

#define maxn 500005

struct Ask {
    int l, r, id, bel;
    inline bool operator<(const Ask& oth) const {
        return (this->bel == oth.bel) ? ((this->bel & 1) ? this->r > oth.r : this->r < oth.r) : (this->l < oth.l);
    }
};

int a[maxn];
int cnt[maxn], pos[maxn], pool[maxn], tail = 0, ans[maxn];
Ask ask[maxn];

void add(int p) {
    if (cnt[a[p]] == 1) swap(pool[pos[pool[tail]] = pos[a[p]]], pool[tail]), tail--;
    cnt[a[p]]++;
    if (cnt[a[p]] == 1) pool[pos[a[p]] = ++tail] = a[p];
    return;
}
void del(int p) {
    if (cnt[a[p]] == 1) swap(pool[pos[pool[tail]] = pos[a[p]]], pool[tail]), tail--;
    cnt[a[p]]--;
    if (cnt[a[p]] == 1) pool[pos[a[p]] = ++tail] = a[p];
    return;
}

int main() {
    int n = read<int>(), sqrtn = sqrt(n);
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    int m = read<int>();
    for (register int i = 1; i <= m; i++)
        ask[i].l = read<int>(), ask[i].r = read<int>(), ask[i].id = i, ask[i].bel = ask[i].l / sqrtn;
    sort(ask + 1, ask + m + 1);
    for (register int i = 1, l = 1, r = 0; i <= m; i++) {
        while (l > ask[i].l) add(--l);
        while (r < ask[i].r) add(++r);
        while (l < ask[i].l) del(l++);
        while (r > ask[i].r) del(r--);
        ans[ask[i].id] = pool[tail];
    }
    for (register int i = 1; i <= m; i++) write(ans[i]), putch('\n');
    return 0;
}