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

#define maxn 2000005

struct Ask {
    int l, r, id;
    inline bool operator<(const Ask& oth) const { return this->l < oth.l; }
};

int a[maxn], cnt[maxn], nex[maxn], ans[maxn];
Ask b[maxn];

int tree[maxn];
void add(int p, int val) {
    // printf("#ADD %d %d\n", p, val);
    for (register int i = p; i < maxn; i += i & -i) tree[i] += val;
    return;
}
int sum(int p) {
    int sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

int main() {
    int n = read<int>(), c = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 1; i <= m; i++) b[i].l = read<int>(), b[i].r = read<int>(), b[i].id = i;
    sort(b + 1, b + m + 1);
    for (register int i = n; i; i--) nex[i] = cnt[a[i]], cnt[a[i]] = i;
    memset(cnt, 0, sizeof(cnt));
    for (register int i = 1; i <= n; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] == 2) add(i, 1);
    }
    for (register int i = 1, ql = 1; i <= m; i++) {
        // printf("$%d %d\n", b[i].l, b[i].r);
        while (ql < b[i].l) {
            if (nex[ql]) add(nex[ql], -1);
            if (nex[nex[ql]]) add(nex[nex[ql]], 1);
            ql++;
        }
        ans[b[i].id] = sum(b[i].r);
    }
    for (register int i = 1; i <= m; i++) write(ans[i]), putch('\n');
    return 0;
}