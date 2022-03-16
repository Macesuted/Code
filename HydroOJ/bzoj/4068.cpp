/**
 * @file 4068.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-16
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

#define maxn 300005

typedef pair<int, int> pii;

class SegmentTree1 {
   private:
    struct Node {
        array<pii, 2> minVal;
        int lazy;
    };

    Node tree[maxn << 2];
    int n;

    pii rMin(pii a, pii b) { return a.first != b.first ? (a.first < b.first ? a : b) : (a.second < b.second ? b : a); }
    array<pii, 2> merge(const array<pii, 2>& a, const array<pii, 2>& b) { return {min(a[0], b[0]), rMin(a[1], b[1])}; }
    void update(int p, int v) { return tree[p].lazy += v, tree[p].minVal[0].first += v, tree[p].minVal[1].first += v, void(); }
    void pushDown(int p) { return update(p << 1, tree[p].lazy), update(p << 1 | 1, tree[p].lazy), tree[p].lazy = 0, void(); }
    void pushUp(int p) { return tree[p].minVal = merge(tree[p << 1].minVal, tree[p << 1 | 1].minVal), void(); }
    void build(int p, int l, int r) {
        if (l == r) return tree[p].minVal = {pii{l, l}, pii{l, l}}, void();
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
    array<pii, 2> query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].minVal;
        pushDown(p);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int l, int r, int v) { return update(1, 1, n, l, r, v); }
    array<pii, 2> query(int l, int r) { return query(1, 1, n, l, r); }
} ST1;

class SegmentTree2 {
   private:
    struct Node {
        array<multiset<int>, 2> S;
        array<pii, 2> val;
    };

    Node tree[maxn << 2];
    int n;

    array<pii, 2> merge(const array<pii, 2>& a, const array<pii, 2>& b) { return {min(a[0], b[0]), max(a[1], b[1])}; }
    void calc(int p, int id) {
        return tree[p].val = {pii{tree[p].S[0].empty() ? numeric_limits<int>::max() : *tree[p].S[0].begin(), id},
                              pii{tree[p].S[1].empty() ? numeric_limits<int>::min() : *tree[p].S[1].rbegin(), id}},
               void();
    }
    void pushUp(int p) { return tree[p].val = merge(tree[p << 1].val, tree[p << 1 | 1].val), void(); }
    void build(int p, int l, int r) {
        if (l == r) return calc(p, l);
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }
    void insert(int p, int l, int r, int qp, int v, int type) {
        if (l == r) return tree[p].S[type].insert(v), calc(p, l);
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p << 1, l, mid, qp, v, type) : insert(p << 1 | 1, mid + 1, r, qp, v, type);
        return pushUp(p);
    }
    void erase(int p, int l, int r, int qp, int v, int type) {
        if (l == r) return tree[p].S[type].erase(tree[p].S[type].find(v)), calc(p, l);
        int mid = (l + r) >> 1;
        qp <= mid ? erase(p << 1, l, mid, qp, v, type) : erase(p << 1 | 1, mid + 1, r, qp, v, type);
        return pushUp(p);
    }
    array<pii, 2> query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].val;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void insert(int p, int v, int type) { return insert(1, 1, n, p, v, type); }
    void erase(int p, int v, int type) { return erase(1, 1, n, p, v, type); }
    array<pii, 2> query(int l, int r) { return query(1, 1, n, l, r); }
} ST2;

multiset<pii> S;

int ans = 0, T;

void insert(int x, int y) {
    return ST1.update(x, T, -1), ST2.erase(x, y, 1), ST2.insert(x, y, 0), S.emplace(x, y), ans += y, void();
}
void erase(int x, int y) {
    return ST1.update(x, T, +1), ST2.erase(x, y, 0), ST2.insert(x, y, 1), S.erase(S.find({x, y})), ans -= y, void();
}

void solve(void) {
    T = read<int>();
    ST1.resize(T), ST1.build(), ST2.resize(T), ST2.build();
    for (int i = read<int>(); i; i--) {
        if (getstr() == "ADD") {
            int a = read<int>(), p = read<int>();
            ST2.insert(a, p, 1), insert(a, p);
            pii x = ST1.query(1, T)[0];
            if (x.first < 0) {
                pii y = ST2.query(1, x.second)[0];
                (p < y.first) ? erase(a, p) : erase(y.second, y.first);
            }
        } else {
            int a = read<int>(), p = read<int>();
            if (S.find({a, p}) == S.end())
                ST2.erase(a, p, 1);
            else {
                erase(a, p), ST2.erase(a, p, 1);
                pii x = ST1.query(1, T)[1];
                if (x.first > 0) x.second = 0;
                pii y = ST2.query(x.second + 1, T)[1];
                if (y.first != numeric_limits<int>::min()) insert(y.second, y.first);
            }
        }
        write(ans), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
