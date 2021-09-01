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

#define maxn 200005

struct Node {
    int x, y, z, sign;
    inline bool operator<(const Node& oth) const {
        return this->x != oth.x ? this->x < oth.x : (this->y != oth.y ? this->y < oth.y : this->z < oth.z);
    }
    inline bool operator==(const Node& oth) const {
        return this->x == oth.x && this->y == oth.y && this->z == oth.z;
    }
};

Node nodes[maxn];
int cnt[maxn], pos[maxn];
long long answer[maxn];
int n, m;

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

void work(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    work(l, mid), work(mid + 1, r);
    int p = l, tot = 0;
    for (register int i = mid + 1; i <= r; i++) {
        while (p <= mid && nodes[p].y <= nodes[i].y) add(nodes[p].z, nodes[p].sign), tot += nodes[p].sign, p++;
        answer[nodes[i].x] += nodes[i].sign * (tot - sum(nodes[i].z));
    }
    for (register int i = l; i < p; i++) add(nodes[i].z, -nodes[i].sign);
    p = mid;
    for (register int i = r; i > mid; i--) {
        while (p >= l && nodes[p].y >= nodes[i].y) add(nodes[p].z, nodes[p].sign), p--;
        answer[nodes[i].x] += nodes[i].sign * sum(nodes[i].z - 1);
    }
    for (register int i = mid; i > p; i--) add(nodes[i].z, -nodes[i].sign);
    int pl = p = l, pr = mid + 1;
    static Node cache[maxn];
    while (pl <= mid && pr <= r) cache[p++] = (nodes[pl].y <= nodes[pr].y) ? nodes[pl++] : nodes[pr++];
    while (pl <= mid) cache[p++] = nodes[pl++];
    while (pr <= r) cache[p++] = nodes[pr++];
    for (register int i = l; i <= r; i++) nodes[i] = cache[i];
    return;
}

int main() {
    n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) nodes[i].x = 0, nodes[i].y = i, pos[nodes[i].z = read<int>()] = i, nodes[i].sign = 1;
    for (register int i = 1; i <= m; i++)
        nodes[++n].z = read<int>(), nodes[n].y = pos[nodes[n].z], nodes[n].x = i, nodes[n].sign = -1;
    work(1, n);
    for (register int i = 1; i < m; i++) answer[i] += answer[i - 1];
    for (register int i = 0; i < m; i++) write(answer[i]), putch('\n');
    return 0;
}