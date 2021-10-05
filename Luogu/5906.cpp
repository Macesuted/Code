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
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 200005

int a[maxn], b[maxn];

struct Ask {
    int l, r, bell, id;
    inline bool operator<(const Ask& oth) const { return this->bell != oth.bell ? this->bell < oth.bell : this->r < oth.r; }
};

Ask ask[maxn];
int answer[maxn];

int minPos[maxn], maxPos[maxn], ans;
int pack[2][maxn];

void clear(void) {
    memset(minPos, 0x3f, sizeof(minPos)), memset(maxPos, 0, sizeof(maxPos));
    ans = 0;
    return;
}
void add(int p) {
    minPos[a[p]] = min(minPos[a[p]], p), maxPos[a[p]] = max(maxPos[a[p]], p);
    ans = max(ans, maxPos[a[p]] - minPos[a[p]]);
    return;
}

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = b[i] = read<int>();
    sort(b + 1, b + n + 1);
    int btail = unique(b + 1, b + n + 1) - b - 1;
    for (register int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + btail + 1, a[i]) - b;
    int q = read<int>(), block = sqrt(n);
    for (register int i = 1; i <= q; i++)
        ask[i].l = read<int>(), ask[i].r = read<int>(), ask[i].bell = ask[i].l / block, ask[i].id = i;
    sort(ask + 1, ask + q + 1);
    for (register int i = 1, l = -1, r = 0; i <= q; i++) {
        int pl = (ask[i].l / block + 1) * block;
        if (pl != l) l = pl, r = pl - 1, clear();
        while (r < ask[i].r) add(++r);
        for (register int j = min(pl - 1, ask[i].r); j >= ask[i].l; j--) pack[0][a[j]] = minPos[a[j]], pack[1][a[j]] = maxPos[a[j]];
        int tatAns = ans;
        for (register int j = min(pl - 1, ask[i].r); j >= ask[i].l; j--) add(j);
        answer[ask[i].id] = ans;
        ans = tatAns;
        for (register int j = min(pl - 1, ask[i].r); j >= ask[i].l; j--) minPos[a[j]] = pack[0][a[j]], maxPos[a[j]] = pack[1][a[j]];
    }
    for (register int i = 1; i <= q; i++) write(answer[i]), putch('\n');
    return 0;
}