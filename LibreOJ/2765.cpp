/**
 * @file 2765.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-22
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

typedef pair<int, int> pii;

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
} FT;

class SegmentTree {
   private:
    int tree[maxn << 2], lazy[maxn << 2], n;

    void upd(int p, int v) { return tree[p] += v, lazy[p] += v, void(); }
    void pushDown(int p) { return upd(p << 1, lazy[p]), upd(p << 1 | 1, lazy[p]), lazy[p] = 0, void(); }
    void pushUp(int p) { return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void(); }
    void add(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return upd(p, v);
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
        if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void add(int l, int r, int v) { return add(1, 1, n, l, r, v); }
    int query(void) { return tree[1]; }
} ST;

int a[maxn], t[maxn], x[maxn], y[maxn];
bool vis[maxn];
vector<pii> ins[maxn], era[maxn];
vector<pii> px, py;

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = t[i] = read<int>();
    sort(t + 1, t + n + 1);
    int tn = unique(t + 1, t + n + 1) - t - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(t + 1, t + tn + 1, a[i]) - t;
    long long tot = 0;
    for (int i = n; i; i--) tot += FT.sum(a[i] - 1), FT.add(a[i], 1);
    int pm = +1;
    for (int i = 1; i < n; i++)
        if (a[i] == a[i + 1])
            pm = min(pm, 0);
        else if (a[i] > a[i + 1])
            pm = min(pm, -1);
    int ans = 0;
    for (int i = 1, pmax = 0; i <= n; i++)
        if (pmax < a[i]) pmax = a[i], x[px.size()] = a[i], px.emplace_back(i, a[i]), vis[i] = true;
    for (int i = n, pmin = n; i; i--)
        if (pmin > a[i]) pmin = a[i], py.emplace_back(i, a[i]), vis[i] = true;
    reverse(py.begin(), py.end());
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        ins[lower_bound(x, x + (int)px.size(), a[i]) - x].emplace_back(i, a[i]);
        ins[upper_bound(x, x + (int)px.size(), a[i]) - x].emplace_back(i, a[i] + 1);
        era[lower_bound(px.begin(), px.end(), pii{i, 0}) - px.begin()].emplace_back(i, a[i]);
        era[lower_bound(px.begin(), px.end(), pii{i, 0}) - px.begin()].emplace_back(i, a[i] + 1);
    }
    for (int i = 0; i < (int)py.size(); i++) y[i] = py[i].second;
    ST.resize(n);
    for (int i = 0; i < (int)px.size(); i++) {
        for (auto j : ins[i]) {
            int l = lower_bound(py.begin(), py.end(), pii{j.first, 0}) - py.begin(),
                r = lower_bound(y, y + (int)py.size(), j.second) - y - 1;
            if (l <= r) ST.add(l + 1, r + 1, +1);
        }
        for (auto j : era[i]) {
            int l = lower_bound(py.begin(), py.end(), pii{j.first, 0}) - py.begin(),
                r = lower_bound(y, y + (int)py.size(), j.second) - y - 1;
            if (l <= r) ST.add(l + 1, r + 1, -1);
        }
        ans = max(ans, ST.query());
    }
    write(tot - ans + pm), putch('\n');
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
