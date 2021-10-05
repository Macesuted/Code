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

#define maxn 100005
#define maxm 5005

int a[maxn], b[maxn];
int answer[maxm];

struct Ask {
    int bell, l, r, p, id;
    inline bool operator<(const Ask& oth) const {
        return (this->bell != oth.bell) ? this->bell < oth.bell : ((this->bell & 1) ? this->r > oth.r : this->r < oth.r);
    }
};

Ask ask[maxm];

int tree[maxn];
void add(int p, int val) {
    for (register int i = p; i < maxn; i += i & -i) tree[i] += val;
    return;
}
int sum(int p) {
    int sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

void insert(int p) {
    add(a[p], 1);
    return;
}
void erase(int p) {
    add(a[p], -1);
    return;
}

inline bool check(int lim, int p) { return sum(lim) >= p; }
int getAns(int p) {
    int l = 1, r = maxn;
    if (check(l, p)) return b[l];
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        check(mid, p) ? r = mid : l = mid;
    }
    return b[r];
}

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = b[i] = read<int>();
    sort(b + 1, b + n + 1);
    int btail = unique(b + 1, b + n + 1) - b - 1;
    for (register int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + btail + 1, a[i]) - b;
    int sqrtn = sqrt(n);
    for (register int i = 1; i <= m; i++)
        ask[i].l = read<int>(), ask[i].r = read<int>(), ask[i].p = read<int>(), ask[i].bell = ask[i].l / sqrtn, ask[i].id = i;
    sort(ask + 1, ask + m + 1);
    int l = 1, r = 0;
    for (register int i = 1; i <= m; i++) {
        while (l > ask[i].l) insert(--l);
        while (r < ask[i].r) insert(++r);
        while (l < ask[i].l) erase(l++);
        while (r > ask[i].r) erase(r--);
        answer[ask[i].id] = getAns(ask[i].p);
    }
    for (register int i = 1; i <= m; i++) write(answer[i]), putch('\n');
    return 0;
}