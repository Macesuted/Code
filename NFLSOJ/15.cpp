/**
 * @file 15.cpp
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

typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int64_t ans, cnt;

        Node(void) { l = r = NULL, ans = cnt = 0; }
    };

    Node* root;
    int n;

    void recalc(Node* p, int v) { return p->ans = ((p->cnt & 1) ? v : 0), void(); }
    void pushUp(Node* p) {
        p->ans = p->cnt = 0;
        if (p->r) p->ans += p->r->ans, p->cnt += p->r->cnt;
        if (p->l) p->ans += (p->cnt & 1) ? -p->l->ans : p->l->ans, p->cnt += p->l->cnt;
        return;
    }
    void insert(Node*& p, int l, int r, int qp) {
        if (!p) p = new Node();
        if (l == r) return p->cnt++, recalc(p, l);
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp) : insert(p->r, mid + 1, r, qp);
        return pushUp(p);
    }
    void erase(Node*& p, int l, int r, int qp) {
        if (l == r) return (!--p->cnt) ? (delete p, p = NULL, void()) : recalc(p, l);
        int mid = (l + r) >> 1;
        qp <= mid ? erase(p->l, l, mid, qp) : erase(p->r, mid + 1, r, qp);
        return (!--p->cnt) ? (delete p, p = NULL, void()) : pushUp(p);
    }

   public:
    SegmentTree(void) { root = NULL, n = 1e9; }
    void insert(int p) { return insert(root, 0, n, p); }
    void erase(int p) { return erase(root, 0, n, p); }
    int query(void) { return root ? root->ans : 0; }
} ST;

int a[maxn], cnt = 0;
tiii ins[maxn];

void solve(void) {
    int n = read(), q = read(), o = read(), last = 0;
    for (int i = 1; i <= n; i++) ST.insert(0);
    while (q--) {
        if (read() == 1) {
            int u = read(), v = read(), w = read();
            u ^= o * last, v ^= o * last;
            ins[++cnt] = {u, v, w};
            if (u == v)
                ST.erase(a[u]), ST.insert(a[u] += w * 2);
            else
                ST.erase(a[u]), ST.erase(a[v]), ST.insert(a[u] += w), ST.insert(a[v] += w);
        } else {
            int k = read(), u, v, w;
            k ^= o * last, tie(u, v, w) = ins[k];
            if (u == v)
                ST.erase(a[u]), ST.insert(a[u] -= w * 2);
            else
                ST.erase(a[u]), ST.erase(a[v]), ST.insert(a[u] -= w), ST.insert(a[v] -= w);
        }
        write(last = ST.query() / 2), putch('\n');
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