/**
 * @file 3821.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxn 100005
#define maxq 600005

typedef pair<int, int> pii;

int mod;

class SegmentTree {
   private:
    struct Node {
        int l, r, a, b;
        bool operator<(const Node& oth) const { return this->r < oth.r; }
    };
    vector<Node> tree[maxq << 2];
    int n, m;

    pii merge(pii x, pii y) { return {1LL * x.first * y.first % mod, (1LL * x.second * y.first + y.second) % mod}; }

    void pushUp(int p) {
        auto p1 = tree[p << 1].begin(), p2 = tree[p << 1 | 1].begin();
        for (int l = 1, r; l <= m; l = r + 1) {
            if (p1->r < l) p1++;
            if (p2->r < l) p2++;
            r = min(p1->r, p2->r);
            pii t = merge({p1->a, p1->b}, {p2->a, p2->b});
            tree[p].push_back(Node{l, r, t.first, t.second});
        }
        return;
    }
    void update(int p, int l, int r, int qp, int ql, int qr, int a, int b) {
        if (l == r) {
            if (1 < ql) tree[p].push_back(Node{1, ql - 1, 1, 0});
            tree[p].push_back(Node{ql, qr, a, b});
            if (qr < m) tree[p].push_back(Node{qr + 1, m, 1, 0});
            return;
        }
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, ql, qr, a, b) : update(p << 1 | 1, mid + 1, r, qp, ql, qr, a, b);
        if (qp == r) pushUp(p);
        return;
    }
    pii query(int p, int l, int r, int ql, int qr, int qp) {
        if (ql <= l && r <= qr) {
            auto x = lower_bound(tree[p].begin(), tree[p].end(), Node{qp, qp, 0, 0});
            return {x->a, x->b};
        }
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr, qp);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr, qp);
        return merge(query(p << 1, l, mid, ql, qr, qp), query(p << 1 | 1, mid + 1, r, ql, qr, qp));
    }

   public:
    void resize(int _n, int _m) { return n = _n, m = _m, void(); }
    void update(int p, int l, int r, int a, int b) { return update(1, 1, n, p, l, r, a, b); }
    pii query(int l, int r, int p) { return query(1, 1, n, l, r, p); }
} ST;

int a[maxn];

void solve(void) {
    int V = read<int>(), n = read<int>();
    mod = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>() % mod;
    int q = read<int>();
    ST.resize(q, n);
    for (int i = 1, v = 0, lastans = 0; i <= q; i++)
        if (read<int>() == 1) {
            int l = read<int>(), r = read<int>(), a = read<int>() % mod, b = read<int>() % mod;
            if (V & 1) l ^= lastans, r ^= lastans;
            ST.update(++v, l, r, a, b);
        } else {
            int l = read<int>(), r = read<int>(), p = read<int>();
            if (V & 1) l ^= lastans, r ^= lastans, p ^= lastans;
            pii ret = ST.query(l, r, p);
            write(lastans = (1LL * a[p] * ret.first + ret.second) % mod), putch('\n');
        }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}