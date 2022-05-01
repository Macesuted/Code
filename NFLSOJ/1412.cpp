/**
 * @file 1412.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-10
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

#define maxn 100005

typedef pair<int, int> pii;

class SegmentTree {
   private:
    struct Node {
        struct Value {
            int sum, pre, suf;

            Value operator+(const Value& o) const { return Value{sum + o.sum, max(pre, sum + o.pre), max(suf + o.sum, o.suf)}; }
        };

        Node *l, *r;
        Value v;

        Node(void) { l = r = NULL; }
    };

    vector<Node*> roots;
    int n;

    void build(Node*& p, int l, int r) {
        if (p == NULL) p = new Node();
        if (l == r) return p->v.sum = p->v.pre = p->v.suf = 1, void();
        int mid = (l + r) >> 1;
        build(p->l, l, mid), build(p->r, mid + 1, r);
        return p->v = p->l->v + p->r->v, void();
    }
    void update(Node*& p, int l, int r, int qp) {
        Node v = *p;
        *(p = new Node()) = v;
        if (l == r) return p->v.sum = -1, p->v.pre = p->v.suf = 0, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp) : update(p->r, mid + 1, r, qp);
        return p->v = p->l->v + p->r->v, void();
    }
    Node::Value query(Node* p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return p->v;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return query(p->l, l, mid, ql, qr) + query(p->r, mid + 1, r, ql, qr);
    }

   public:
    SegmentTree(void) { roots.push_back(NULL); }
    void resize(int _n) { return build(roots.back(), 1, n = _n); }
    void update(int p) { return roots.push_back(roots.back()), update(roots.back(), 1, n, p); }
    Node::Value query(int v, int l, int r) { return query(roots[v], 1, n, l, r); }
} ST;

pii a[maxn];

bool check(int p, const array<int, 4>& x) {
    int sum = ST.query(p, x[1], x[2]).sum;
    if (x[0] < x[1]) sum += ST.query(p, x[0], x[1] - 1).suf;
    if (x[2] < x[3]) sum += ST.query(p, x[2] + 1, x[3]).pre;
    return sum >= 0;
}

void solve(void) {
    int n = read(), p = read();
    for (int i = 1; i <= n; i++) a[i] = {read(), i};
    sort(a + 1, a + n + 1), ST.resize(n);
    for (int i = 1; i <= n; i++) ST.update(a[i].second);
    int q = read(), last = 0;
    while (q--) {
        array<int, 4> x = {read(), read(), read(), read()};
        for (auto& i : x) i = (i + p * last) % n + 1;
        sort(x.begin(), x.end());
        int l = 1, r = n + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            check(mid - 1, x) ? l = mid : r = mid;
        }
        write(last = a[l].first), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("middle.in", "r", stdin), freopen("middle.out", "w", stdout);
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