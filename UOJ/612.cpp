/**
 * @file 612.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-06
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

#define maxn 250005

typedef pair<long long, int> pli;
typedef tuple<int, int, long long> tiil;

class SegmentTree {
   private:
    struct Node {
        long long maxVal, sum, cnt;
        Node operator+(const Node& oth) const { return Node{max(maxVal + oth.sum, oth.maxVal), sum + oth.sum, cnt + oth.cnt}; }
    };

    Node tree[maxn << 2];
    int n;

    void update(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].maxVal = tree[p].cnt = max(0LL, tree[p].sum += v), void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Node getAns(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        if (qr <= mid) return getAns(p << 1, l, mid, ql, qr);
        if (ql > mid) return getAns(p << 1 | 1, mid + 1, r, ql, qr);
        return getAns(p << 1, l, mid, ql, qr) + getAns(p << 1 | 1, mid + 1, r, ql, qr);
    }
    int search(int p, int l, int r, long long cnt) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        return tree[p << 1].cnt >= cnt ? search(p << 1, l, mid, cnt) : search(p << 1 | 1, mid + 1, r, cnt - tree[p << 1].cnt);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, int v) { return update(1, 1, n, p, v); }
    Node getAns(int p) { return getAns(1, 1, n, 1, p); }
    int search(long long cnt) { return search(1, 1, n, cnt); }
} ST;

int ans[maxn], c[maxn];
vector<tiil> ops[maxn];

void solve(void) {
    int n = read<int>(), m = read<int>(), q = read<int>();
    for (int i = 1; i <= q; i++) {
        int op = read<int>();
        if (op == 1) {
            int l = read<int>(), r = read<int>(), C = read<int>(), k = read<int>();
            c[i] = C, ops[l].emplace_back(1, i, +k), ops[r + 1].emplace_back(1, i, -k);
        } else if (op == 2) {
            int l = read<int>(), r = read<int>(), k = read<int>();
            ops[l].emplace_back(2, i, -k), ops[r + 1].emplace_back(2, i, +k);
        } else {
            int a = read<int>();
            ops[a].emplace_back(3, i, read<long long>());
        }
    }
    for (int i = 1; i <= q; i++) ans[i] = -1;
    ST.resize(q);
    for (int i = 1; i <= n; i++)
        for (auto op : ops[i])
            if (get<0>(op) != 3)
                ST.update(get<1>(op), get<2>(op));
            else {
                auto ret = ST.getAns(get<1>(op));
                long long cnt = max(ret.sum, ret.maxVal);
                ans[get<1>(op)] = (cnt >= get<2>(op) ? c[ST.search(ret.cnt - cnt + get<2>(op))] : 0);
            }
    for (int i = 1; i <= q; i++)
        if (~ans[i]) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
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
