/**
 * @file 4370.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-25
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

#define maxn 500005
#define mod 1000000007

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
long long inv(long long x) { return Pow(x, mod - 2); }

class SegmentTree {
   private:
    int tree[maxn << 2], n;

    void pushUp(int p) { return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void(); }
    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p] = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return max(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
} ST;
class FenwickTree {
   private:
    int tree[maxn];

   public:
    FenwickTree(void) {
        for (int i = 0; i < maxn; i++) tree[i] = 1;
    }
    void multi(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] = 1LL * tree[i] * v % mod;
        return;
    }
    int prod(int p) {
        int prod = 1;
        for (int i = p; i; i -= i & -i) prod = 1LL * prod * tree[i] % mod;
        return prod;
    }
} FT;

int n;
long long X[maxn], Y[maxn];
set<int> S;

int query(void) {
    long long mult = 1, ans = 0;
    vector<int> pos;
    for (auto i = S.rbegin(); i != S.rend() && mult < mod; i++) pos.push_back(*i), mult *= X[*i];
    if (pos.empty() || (mult < mod && pos.back() != 1)) pos.push_back(1);
    mult = 1;
    for (auto i = pos.rbegin(); i != pos.rend(); i++)
        (i != pos.rbegin()) && (mult *= X[*i]), ans = max(ans, mult * ST.query(*i, n));
    return ans % mod * FT.prod(pos.back()) % mod;
}

void solve(void) {
    n = read<int>();
    ST.resize(n);
    for (int i = 1; i <= n; i++) {
        FT.multi(i, X[i] = read<int>());
        if (X[i] > 1) S.insert(i);
    }
    for (int i = 1; i <= n; i++) ST.update(i, Y[i] = read<int>());
    write(query()), putch('\n');
    int q = read<int>();
    while (q--) {
        if (read<int>() == 1) {
            int p = read<int>() + 1, v = read<int>();
            FT.multi(p, v * inv(X[p]) % mod);
            if (X[p] > 1) S.erase(p);
            X[p] = v;
            if (X[p] > 1) S.insert(p);
        } else {
            int p = read<int>() + 1;
            ST.update(p, Y[p] = read<int>());
        }
        write(query()), putch('\n');
    }
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