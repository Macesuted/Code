/**
 * @file b.cpp
 * @author Macesuted Moe (i@macesuted.moe)
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 3S  Memory Limit: 512M
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
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
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

bool mem1;

#define maxm 500005
#define maxlgv 31

typedef pair<int, int> pii;

uint32_t calcAns(uint32_t p) { return (~p) ^ (p >> 1); }
uint32_t calcAns(uint32_t l, uint32_t r) { return calcAns(r) ^ calcAns(l - 1); }

vector<int> C;

class SegmentTree {
   private:
    struct Node {
        uint32_t ans, minAns;
        int minVal, lazy;
    } tree[maxm << 4];

    int n;

    void update(int p, int v) {
        if (tree[p].minVal) tree[p].ans ^= tree[p].minAns;
        tree[p].minVal += v, tree[p].lazy += v;
        if (tree[p].minVal) tree[p].ans ^= tree[p].minAns;
        return;
    }
    void pushDown(int p) {
        if (!tree[p].lazy) return;
        update(p << 1, tree[p].lazy), update(p << 1 | 1, tree[p].lazy), tree[p].lazy = 0;
        return;
    }
    void pushUp(int p) {
        tree[p].ans = tree[p << 1].ans ^ tree[p << 1 | 1].ans, tree[p].minAns = 0,
        tree[p].minVal = min(tree[p << 1].minVal, tree[p << 1 | 1].minVal);
        if (tree[p].minVal == tree[p << 1].minVal) tree[p].minAns ^= tree[p << 1].minAns;
        if (tree[p].minVal == tree[p << 1 | 1].minVal) tree[p].minAns ^= tree[p << 1 | 1].minAns;
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) return tree[p].minAns = calcAns(C[l], C[r + 1] - 1), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void update(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return update(p, v);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, v);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    uint32_t query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].ans;
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) ^ query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    uint32_t query(int l, int r) { return query(1, 1, n, l, r); }
} ST;

uint32_t calc(uint32_t a, uint32_t b, uint32_t lim) {
    uint32_t ans = 0, ap = a, bp = b;
    for (int i = maxlgv - 2; ~i; i--) ap ^= (ap >> (i + 1) & 1) << i, bp ^= (bp >> (i + 1) & 1) << i;
    for (uint32_t i = 1; i < lim; i <<= 1) ans |= ((a & i) & (bp & i)) ^ ((ap & i) & (b & i)) ^ ((a & i) & (b & i));
    ans |= (ap & lim) & (bp & lim);
    return ans;
}

map<int, vector<pii>> lines;

void solve(void) {
    int n = read<int>(), m = read<int>(), k = read<int>();
    uint32_t lim = 1;
    while ((lim << 1) <= uint32_t(k)) lim <<= 1;
    C.reserve(2 * m + 2);
    for (int i = 1; i <= m; i++) {
        int a = read<int>(), b = read<int>(), c = read<int>(), d = read<int>();
        C.push_back(b), C.push_back(d + 1);
        lines[a].emplace_back(b, d + 1), lines[c + 1].emplace_back(-b, -d - 1);
    }
    C.push_back(-1), C.push_back(1e9 + 1), sort(C.begin(), C.end()), C.resize(unique(C.begin(), C.end()) - C.begin());
    ST.resize(n = C.size() - 2), ST.build();
    uint32_t last = 0, ans = 0;
    int lastp = 1;
    for (const auto& i : lines) {
        ans ^= calc(last, calcAns(lastp, i.first - 1), lim);
        for (const auto& j : i.second)
            ST.update(lower_bound(C.begin(), C.end(), abs(j.first)) - C.begin(),
                      lower_bound(C.begin(), C.end(), abs(j.second)) - C.begin() - 1, j.first > 0 ? +1 : -1);
        last = ST.query(1, n), lastp = i.first;
    }
    return putstr(ans == 0 ? "Iris" : "b"), putch('\n');
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
