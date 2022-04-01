/**
 * @file 3062.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-01
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
    __int128 fx = x;
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

#define maxn 500005
#define maxv 1000005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        int64_t cnt, sum;
        Node operator+(const Node& o) const { return Node{cnt + o.cnt, sum + o.sum}; }
    };

    Node tree[maxv << 2];
    int n;

    void pushUp(int p) { return tree[p] = tree[p << 1] + tree[p << 1 | 1], void(); }
    void add(int p, int l, int r, int qp, int64_t v) {
        if (l == r) return tree[p].cnt += v, tree[p].sum += v * l, void();
        int mid = (l + r) >> 1;
        qp <= mid ? add(p << 1, l, mid, qp, v) : add(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int64_t query(int p, int l, int r, int64_t cnt) {
        if (l == r) return l * min(tree[p].cnt, cnt);
        int mid = (l + r) >> 1;
        if (tree[p << 1 | 1].cnt < cnt) return tree[p << 1 | 1].sum + query(p << 1, l, mid, cnt - tree[p << 1 | 1].cnt);
        return query(p << 1 | 1, mid + 1, r, cnt);
    }

   public:
    SegmentTree(void) { n = 1000000; }
    void add(int p, int64_t v) { return add(1, 1, n, p, v); }
    int64_t query(int64_t cnt) { return query(1, 1, n, cnt); }
} ST;

pii a[maxn];
tiii b[maxn];

void solve(void) {
    int n = read(), m = read();
    int64_t P = read(), ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++) a[i].first = read(), a[i].second = read();
    for (int i = 1; i <= m; i++) get<0>(b[i]) = read(), get<1>(b[i]) = read(), get<2>(b[i]) = read();
    a[n + 1].first = get<0>(b[m + 1]) = numeric_limits<int>::max();
    sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
    for (int i = 0, j = 0; i < n || j < m;) {
        int x = min(a[i + 1].first, get<0>(b[j + 1]));
        while (i < n && a[i + 1].first <= x) cnt += a[++i].second;
        while (j < m && get<0>(b[j + 1]) <= x) j++, ST.add(get<2>(b[j]), get<1>(b[j]));
        ans = max(ans, ST.query(cnt) - x * P);
    }
    write(ans), putch('\n');
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
