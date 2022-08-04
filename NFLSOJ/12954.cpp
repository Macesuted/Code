/**
 * @file 12954.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache1[100], cache2[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il && (fill(), 1), *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 1), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache1[top++] = x % 10, x /= 10;
    while (top) putch(cache1[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    int64_t fx = x;
    x -= fx;
    for (int i = 0; i < dep; i++) cache2[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        cache2[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (cache2[i] == 10) cache2[i] = 0, cache2[i - 1]++;
        if (cache2[0] == 10) cache2[0] = 0, fx++;
    }
    write(fx), putch('.');
    for (int i = 0; i < dep; i++) putch(cache2[i] ^ 48);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
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
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxn 200005

class SegmentTree {
   private:
    struct Node {
        int cl, cr, len, ans, pre, suf;
        Node operator+(const Node& o) const {
            Node ans, l = *this, r = o;
            ans.cl = l.cl, ans.cr = r.cr, ans.len = l.len + r.len, ans.ans = l.ans + r.ans, ans.pre = l.pre,
            ans.suf = r.suf;
            if (l.suf == l.len) ans.pre = l.suf;
            if (r.pre == r.len) ans.suf = r.pre;
            if (l.cr != r.cl) {
                if (l.pre == l.len) swap(l.pre, l.suf);
                if (r.suf == r.len) swap(r.pre, r.suf);
                if ((l.suf & 1) && (r.pre & 1)) ans.ans++;
                if (l.suf == l.len)
                    ans.pre = l.len + r.pre, ans.suf = r.suf;
                else if (r.pre == r.len)
                    ans.pre = l.pre, ans.suf = l.suf + r.len;
            }
            ans.pre = max(ans.pre, l.pre), ans.suf = max(ans.suf, r.suf);
            return ans;
        }
    };

    Node tree[maxn << 3];
    int n;

    void build(int p, int l, int r) {
        if (l == r) return tree[p] = Node{+1, +1, 1, 1, 1, 0}, void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].cl = tree[p].cr = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void build(void) { return build(1, 1, n); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(int l, int r) { return query(1, 1, n, l, r).ans; }
} ST;

vector<int> a[maxn];

void solve(void) {
    int n = read(), m = read();
    ST.resize(2 * n), ST.build();
    for (int i = 1; i <= n; i++) a[read()].push_back(i);
    for (int i = 1; i <= m; i++) {
        if (a[i].empty()) {
            putstr("-1 ");
            continue;
        }
        int ans = 0, lst = a[i].back();
        for (auto j : a[i]) {
            if (lst + 1 < j + n) ans += ST.query(lst + 1, j + n - 1);
            lst = j + n;
        }
        for (auto j : a[i]) ST.update(j, -1), ST.update(j + n, -1);
        write(ans), putch(' ');
    }
    putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("small.in", "r", stdin), freopen("small.out", "w", stdout);
#endif
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
