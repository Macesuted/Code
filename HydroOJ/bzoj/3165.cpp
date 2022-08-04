/**
 * @file 3165.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-28
 *
 * @copyright Copyright (c) 2021
 *
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

bool mem1;

#define maxn 100005
#define maxv 40005

typedef pair<double, double> pdd;
typedef pair<double, int> pdi;

class LiChaoTree {
   private:
    struct Node {
        pdd val;
        int id;
        Node(void) { val = pdd{0, -1e15}, id = 0; }
        Node(pdd _val, int _id) : val(_val), id(_id) {}
    };
    Node tree[maxv << 3];
    int n;

    inline double getVal(pdd v, int x) { return x * v.first + v.second; }
    void insert(int p, int l, int r, int ql, int qr, pdd v, int id) {
        int mid = (l + r) >> 1;
        if (ql <= l && r <= qr) {
            bool lef = (getVal(tree[p].val, l) < getVal(v, l)), rig = (getVal(tree[p].val, r) < getVal(v, r));
            if (getVal(tree[p].val, mid) < getVal(v, mid)) {
                if (lef && !rig) insert(p << 1 | 1, mid + 1, r, l, r, tree[p].val, tree[p].id);
                if (!lef && rig) insert(p << 1, l, mid, l, r, tree[p].val, tree[p].id);
                tree[p] = {v, id};
            } else {
                if (lef && !rig) insert(p << 1, l, mid, ql, qr, v, id);
                if (!lef && rig) insert(p << 1 | 1, mid + 1, r, ql, qr, v, id);
            }
            return;
        }
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v, id);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v, id);
        return;
    }
    pdi query(int p, int l, int r, int qp) {
        pdi ans = {getVal(tree[p].val, qp), -tree[p].id};
        if (l == r) return ans;
        int mid = (l + r) >> 1;
        return max(ans, qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp));
    }

   public:
    inline void insert(int l, int r, pdd v, int id) { return insert(1, 1, maxv - 1, l, r, v, id); }
    inline int query(int p) { return -query(1, 1, maxv - 1, p).second; }
};

LiChaoTree SGT;

#define mod1 39989
#define mod2 1000000000

#define forceOnline(mod) ((read<int>() + lastans - 1 + mod) % mod + 1)

void solve(void) {
    int n = read<int>(), lastans = 0, cnt = 0;
    while (n--)
        if (read<int>() == 0)
            write(lastans = SGT.query(forceOnline(mod1))), putch('\n');
        else {
            int a0 = forceOnline(mod1), b0 = forceOnline(mod2), a1 = forceOnline(mod1), b1 = forceOnline(mod2);
            if (a0 > a1) swap(a0, a1), swap(b0, b1);
            double x = (b1 - b0) * 1. / (a1 - a0), y = b0 - a0 * x;
            if (a0 == a1) x = 0, y = max(b0, b1);
            SGT.insert(a0, a1, {x, y}, ++cnt);
        }
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}