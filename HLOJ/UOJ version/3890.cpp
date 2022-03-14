/**
 * @file c.cpp
 * @author Macesuted Moe (i@macesuted.moe)
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
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
string getstr(const string &suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char *p = Il;
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

#define maxn 200005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        int maxVal, ans, croAns;
        Node(int maxVal_ = -1) { maxVal = maxVal_, ans = croAns = numeric_limits<int>::max(); }
    };

    Node tree[maxn << 2];
    vector<tiii> nodes;
    int n;

    Node merge(int lef, Node rig, int lefl, int lefr) {
        Node ans;
        ans.maxVal = max(tree[lef].maxVal, rig.maxVal);
        ans.ans = min(getAns(lef, lefl, lefr, rig.maxVal).second, rig.ans);
        return ans;
    }
    void pushUp(int p, int l, int r) {
        int mid = (l + r) >> 1;
        tree[p].maxVal = max(tree[p << 1].maxVal, tree[p << 1 | 1].maxVal);
        tree[p].ans = min(tree[p].croAns = getAns(p << 1, l, mid, tree[p << 1 | 1].maxVal).second, tree[p << 1 | 1].ans);
        return;
    }
    void update(int p, int l, int r, int qp, int v, int ans) {
        if (l == r) return tree[p].maxVal = v, tree[p].ans = ans, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v, ans) : update(p << 1 | 1, mid + 1, r, qp, v, ans);
        return pushUp(p, l, r);
    }
    pii getAns(int p, int l, int r, int lim) {
        if (tree[p].maxVal < lim) return {-1, numeric_limits<int>::max()};
        if (l == r) return {tree[p].maxVal, tree[p].ans};
        int mid = (l + r) >> 1;
        if (tree[p << 1 | 1].maxVal < lim) return getAns(p << 1, l, mid, lim);
        pii ret = getAns(p << 1 | 1, mid + 1, r, lim);
        return {tree[p].maxVal, min(tree[p].croAns, ret.second)};
    }
    pii query(int p, int l, int r, int qr) {
        if (l == r) return {tree[p].maxVal, tree[p].ans};
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, qr);
        pii rig = query(p << 1 | 1, mid + 1, r, qr), lef = getAns(p << 1, l, mid, rig.first);
        return {max(lef.first, rig.first), min(lef.second, rig.second)};
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v, int ans) { return update(1, 1, n, p, v, ans); }
    int query(int r) { return query(1, 1, n, r).second; }
} ST;

int a[maxn], c[maxn];
pii q[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) q[i] = {a[i] = read<int>(), i + 1};
    for (int i = 1; i <= n; i++) c[i] = read<int>();
    sort(q + 1, q + n + 1);
    ST.resize(n + 1), ST.update(1, 0, 0);
    for (int i = 1; i <= n; i++) ST.update(q[i].second, q[i].first, ST.query(q[i].second - 1) + c[q[i].second - 1]);
    write(ST.query(n + 1)), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
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
