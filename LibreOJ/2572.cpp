/**
 * @file 2572.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
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

#define maxn 200005
#define blockLen 500
#define P 37
#define mod 19260817

long long H[maxn / blockLen + 5][blockLen + 5], delt[maxn / blockLen + 5], Pow[maxn], PowSum[maxn], sum[maxn / blockLen + 5];
int L[maxn / blockLen + 5], R[maxn / blockLen + 5], bel[maxn], a[maxn], n, blockCnt;

long long getHashInBlock(int l, int r) {
    return (H[bel[r]][r - L[bel[r]] + 1] + mod - H[bel[l]][l - L[bel[l]]] * Pow[r - l + 1] % mod + mod +
            delt[bel[l]] * PowSum[r - l] % mod) %
           mod;
}
long long getHash(int l, int r) {
    int bl = bel[l], br = bel[r];
    if (bl == br) return getHashInBlock(l, r);
    return (getHashInBlock(L[br], r) + (sum[br - 1] + mod - sum[bl] * Pow[R[br - 1] - R[bl]] % mod) * Pow[r - R[br - 1]] +
            getHashInBlock(l, R[bl]) * Pow[r - R[bl]]) %
           mod;
}
int getA(int p) { return a[p] + delt[bel[p]]; }
int LCP(int p1, int p2) {
    if (getA(p1) != getA(p2)) return 0;
    int l = 1, r = n - max(p1, p2) + 2;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        getHash(p1, p1 + mid - 1) == getHash(p2, p2 + mid - 1) ? l = mid : r = mid;
    }
    return l;
}

class SegmentTree {
   private:
    vector<int> tree[maxn << 2];

    vector<int> merge(const vector<int>& p1, const vector<int>& p2, int r) {
        vector<int> ans = p2;
        for (auto i : p1) {
            while (!ans.empty() && ans.back() != i) {
                int x = ans.back(), len = LCP(i, x);
                if (x + len - 1 >= r) {
                    if ((r - x + 1) * 2 > (r - i + 1)) ans.pop_back();
                    ans.push_back(i);
                } else if (getA(i + len) < getA(x + len))
                    ans.pop_back();
                else
                    break;
            }
            if (ans.empty()) ans.push_back(i);
        }
        return ans;
    }
    void build(int p, int l, int r) {
        if (l == r) return tree[p].emplace_back(l), void();
        int mid = (l + r) >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        return tree[p] = merge(tree[p << 1], tree[p << 1 | 1], r), void();
    }
    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return;
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr);
        return tree[p] = merge(tree[p << 1], tree[p << 1 | 1], r), void();
    }
    vector<int> query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p << 1, l, mid, ql, qr);
        if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
        return merge(query(p << 1, l, mid, ql, mid), query(p << 1 | 1, mid + 1, r, mid + 1, qr), qr);
    }

   public:
    void build(void) { return build(1, 1, n); }
    void update(int l, int r) { return update(1, 1, n, l, r); }
    int query(int l, int r) { return query(1, 1, n, l, r).front(); }
} ST;

void recalc(int p) {
    int l = L[p], r = R[p];
    if (!delt[p]) {
        for (int i = l; i <= r; i++) a[i] = a[i] + delt[p];
        delt[p] = 0;
    }
    H[p][0] = 0;
    for (int i = l; i <= r; i++) H[p][i - l + 1] = (H[p][i - l] * P + a[i] % mod + mod) % mod;
    return;
}
void recalcSum(void) {
    for (int i = 1; i <= blockCnt; i++)
        sum[i] = (sum[i - 1] * Pow[R[i] - L[i] + 1] + H[i][R[i] - L[i] + 1] + mod + delt[i] * PowSum[R[i] - L[i]] % mod) % mod;
    return;
}

void solve(void) {
    n = read<int>();
    int q = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    blockCnt = n / blockLen;
    for (int i = 1; i <= blockCnt; i++) L[i] = R[i - 1] + 1, R[i] = R[i - 1] + blockLen;
    if (R[blockCnt] < n) blockCnt++, L[blockCnt] = R[blockCnt - 1] + 1, R[blockCnt] = n;
    for (int i = 1; i <= blockCnt; i++) {
        recalc(i);
        for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
    }
    recalcSum();
    ST.build();
    while (q--) {
        int op = read<int>();
        if (op == 1) {
            int l = read<int>(), r = read<int>(), d = read<int>(), bl = bel[l], br = bel[r];
            if (bl == br) {
                for (int i = l; i <= r; i++) a[i] = a[i] + d;
                recalc(bl);
            } else {
                for (int i = l; i <= R[bl]; i++) a[i] = a[i] + d;
                recalc(bl);
                for (int i = bl + 1; i < br; i++) delt[i] = delt[i] + d;
                for (int i = L[br]; i <= r; i++) a[i] = a[i] + d;
                recalc(br);
            }
            recalcSum();
            ST.update(l, r);
        } else {
            int l = read<int>(), r = read<int>();
            write(ST.query(l, r)), putch('\n');
        }
    }
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    Pow[0] = PowSum[0] = 1;
    for (int i = 1; i < maxn; i++) PowSum[i] = (PowSum[i - 1] + (Pow[i] = Pow[i - 1] * P % mod)) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
