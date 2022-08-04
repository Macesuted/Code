/**
 * @file 101480C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-11
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

#define maxn 200005
#define maxv 1000005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    long long tree[maxv << 2], lazy[maxv << 2];
    bool cls[maxv << 2];

    void pushDown(int p, int l, int r) {
        if (cls[p]) {
            tree[p << 1] = tree[p << 1 | 1] = lazy[p << 1] = lazy[p << 1 | 1] = 0;
            cls[p << 1] = cls[p << 1 | 1] = true, cls[p] = false;
        }
        if (lazy[p]) {
            int mid = (l + r) >> 1;
            tree[p << 1] += (mid - l + 1) * lazy[p], tree[p << 1 | 1] += (r - mid) * lazy[p];
            lazy[p << 1] += lazy[p], lazy[p << 1 | 1] += lazy[p], lazy[p] = 0;
        }
        return;
    }
    void clear(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return cls[p] = true, lazy[p] = tree[p] = 0, void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) clear(p << 1, l, mid, ql, qr);
        if (qr > mid) clear(p << 1 | 1, mid + 1, r, ql, qr);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void add(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return lazy[p] += v, tree[p] += 1LL * v * (r - l + 1), void();
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    int query(int p, int l, int r, int qp) {
        if (l == r) return tree[p];
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        return qp <= mid ? query(p << 1, l, mid, qp) : query(p << 1 | 1, mid + 1, r, qp);
    }

   public:
    void clear(int l, int r) { return clear(1, 1, maxv - 1, l, r); }
    void add(int l, int r, int v) { return add(1, 1, maxv - 1, l, r, v); }
    int query(int p) { return query(1, 1, maxv - 1, p); }
} ST;

vector<tiii> in[maxv], out[maxv];
vector<pii> query[maxv];
vector<int> flower[maxv];
int sum[maxn], ans[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int r1 = read<int>() + 1, c1 = read<int>(), r2 = read<int>() + 1, c2 = read<int>();
        in[c2].emplace_back(r1, r2, i), out[c1].emplace_back(r1, r2, i);
    }
    for (int i = 1; i < maxv; i++)
        sort(out[i].begin(), out[i].end(), [](tiii a, tiii b) { return get<0>(a) > get<0>(b); });
    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        int r = read<int>() + 1, c = read<int>();
        flower[c].push_back(r);
    }
    int q = read<int>();
    for (int i = 1; i <= q; i++) {
        int r = read<int>() + 1, c = read<int>();
        query[c].emplace_back(r, i);
    }
    static set<int> S;
    S.clear(), S.insert(1);
    for (int i = maxv - 2; i; i--) {
        for (auto j : in[i]) ST.clear(get<0>(j), get<1>(j)), S.insert(get<0>(j)), S.insert(get<1>(j) + 1);
        for (auto j : out[i + 1])
            S.erase(get<0>(j)), S.erase(get<1>(j) + 1), ST.clear(get<0>(j), get<1>(j)),
                ST.add(*--S.upper_bound(get<1>(j)), get<1>(j), ST.query(get<1>(j) + 1)),
                ST.add(*--S.upper_bound(get<0>(j) - 1), get<0>(j) - 1, -sum[get<2>(j)]);
        for (auto j : flower[i]) ST.add(*--S.upper_bound(j), j, 1);
        for (auto j : query[i]) ans[j.second] = ST.query(j.first);
        for (auto j : in[i - 1]) sum[get<2>(j)] = ST.query(get<1>(j) + 1);
    }
    for (int i = 1; i <= q; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
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
