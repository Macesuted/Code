/**
 * @author Macesuted (macesuted@outlook.com)
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
#define maxVal 200005

struct Node {
    int x, y, z, cnt, ans;
    inline bool operator<(const Node& oth) const {
        return this->x != oth.x ? this->x < oth.x : (this->y != oth.y ? this->y < oth.y : this->z < oth.z);
    }
    inline bool operator==(const Node& oth) const {
        return this->x == oth.x && this->y == oth.y && this->z == oth.z;
    }
};

Node nodes[maxn];
int cnt[maxn];
int n, k;

int tree[maxVal];
void add(int p, int val) {
    for (register int i = p; i < maxVal; i += i & -i) tree[i] += val;
    return;
}
int sum(int p) {
    int sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

void work(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    work(l, mid), work(mid + 1, r);
    int p = l;
    for (register int i = mid + 1; i <= r; i++) {
        while (p <= mid && nodes[p].y <= nodes[i].y) add(nodes[p].z, nodes[p].cnt), p++;
        nodes[i].ans += sum(nodes[i].z);
    }
    for (register int i = l; i < p; i++) add(nodes[i].z, -nodes[i].cnt);
    int pl = l, pr = mid + 1;
    static Node cache[maxn];
    p = l;
    while (pl <= mid && pr <= r) cache[p++] = (nodes[pl].y <= nodes[pr].y) ? nodes[pl++] : nodes[pr++];
    while (pl <= mid) cache[p++] = nodes[pl++];
    while (pr <= r) cache[p++] = nodes[pr++];
    for (register int i = l; i <= r; i++) nodes[i] = cache[i];
    return;
}

int main() {
    n = read<int>(), k = read<int>();
    for (register int i = 1; i <= n; i++)
        nodes[i].x = read<int>(), nodes[i].y = read<int>(), nodes[i].z = read<int>(), nodes[i].cnt = 1;
    sort(nodes + 1, nodes + n + 1);
    int tn = n;
    n = 1;
    for (register int i = 2; i <= tn; i++)
        nodes[i] == nodes[n] ? (nodes[n].cnt++, void()) : swap(nodes[i], nodes[++n]);
    work(1, n);
    for (register int i = 1; i <= n; i++) cnt[nodes[i].ans + nodes[i].cnt - 1] += nodes[i].cnt;
    for (register int i = 0; i < tn; i++) write(cnt[i]), putch('\n');
    return 0;
}