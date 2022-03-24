/**
 * @file 12801.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-24
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

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        set<int> S;
        int maxVal;
        Node(void) { maxVal = numeric_limits<int>::max(); }
    };

    Node tree[maxn << 4];
    int n;

    void erase(int p, int v) {
        return (tree[p].S.count(v)) && (tree[p].S.erase(v), tree[p << 1].S.insert(v), tree[p << 1 | 1].S.insert(v),
                                        pushUp(p << 1), pushUp(p << 1 | 1), 1),
               void();
    }
    int getMin(int p) { return tree[p].S.empty() ? numeric_limits<int>::max() : *tree[p].S.begin(); }
    void pushUp(int p) { return tree[p].maxVal = min(max(tree[p << 1].maxVal, tree[p << 1 | 1].maxVal), getMin(p)), void(); }
    void insert(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return tree[p].S.erase(v), pushUp(p);
        erase(p, v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr, int lim = numeric_limits<int>::max()) {
        lim = min(lim, getMin(p));
        if (ql <= l && r <= qr) return min(lim, tree[p].maxVal);
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr, lim);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr, lim);
        return max(query(p << 1, l, mid, ql, mid, lim), query(p << 1 | 1, mid + 1, r, mid + 1, qr, lim));
    }

   public:
    SegmentTree(void) {
        n = 200000;
        for (int i = 0; i <= n; i++) tree[1].S.insert(i);
    }
    void insert(int l, int r, int v) { return insert(1, 0, n, l, r, v); }
    int query(int l, int r) { return query(1, 0, n, l, r); }
} ST;
class OldDriverTree {
   private:
    set<pii> S;

    void split(pii x, int p) { return S.erase(x), S.emplace(x.first, p), S.emplace(p + 1, x.second), void(); }
    set<pii>::iterator in(int x) {
        auto p = S.lower_bound(pii{x + 1, 0});
        if (p == S.begin() || (--p)->second < x) return S.end();
        return p;
    }

   public:
    OldDriverTree(void) { S.emplace(0, 200000); }
    void insert(int l, int r, int v) {
        auto p = in(l);
        if (p != S.end() && p->first < l) split(*p, l - 1);
        p = in(r);
        if (p != S.end() && p->second > r) split(*p, r);
        for (auto i = S.lower_bound(pii{l, 0}); i != S.end() && i->second <= r; i = S.erase(i))
            ST.insert(i->first, i->second, v);
        return;
    }
} ODT[maxn];

void solve(void) {
    int q = read<int>();
    long long S = 0;
    while (q--)
        if (read<int>() == 1) {
            long long x = read<long long>(), a = read<long long>(), b = read<long long>();
            x ^= S, a ^= S, b ^= S;
            if (a < 0 || b > 200000) return;
            ODT[x].insert(a, b, x);
        } else {
            long long l = read<long long>(), r = read<long long>();
            l ^= S, r ^= S;
            if (l < 0 || r > 200000) return;
            long long ret = ST.query(l, r);
            S += ret, write(ret), putch('\n');
        }
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("starlight.in", "r", stdin), freopen("starlight.out", "w", stdout);
#endif
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
